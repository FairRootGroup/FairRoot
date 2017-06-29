/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <fairmq/PluginManager.h>
#include <fairmq/Tools.h>
#include <boost/program_options.hpp>
#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

using namespace std;
using fair::mq::tools::ToString;
using fair::mq::tools::ToStrVector;
using fair::mq::Plugin;
namespace fs = boost::filesystem;
namespace po = boost::program_options;
namespace dll = boost::dll;
using boost::optional;

const std::string fair::mq::PluginManager::fgkLibPrefix = "FairMQPlugin_";

fair::mq::PluginManager::PluginManager()
: fSearchPaths{{"."}}
{
}

auto fair::mq::PluginManager::ValidateSearchPath(const fs::path& path) -> void
{
    if (path.empty()) throw BadSearchPath{"Specified path is empty."};
    // we ignore non-existing search paths
    if (fs::exists(path) && !fs::is_directory(path)) throw BadSearchPath{ToString(path, " is not a directory.")};
}

auto fair::mq::PluginManager::SetSearchPaths(const vector<fs::path>& searchPaths) -> void
{
    for_each(begin(searchPaths), end(searchPaths), ValidateSearchPath);
    fSearchPaths = searchPaths;
}

auto fair::mq::PluginManager::AppendSearchPath(const fs::path& path) -> void
{
    ValidateSearchPath(path);
    fSearchPaths.push_back(path);
}

auto fair::mq::PluginManager::PrependSearchPath(const fs::path& path) -> void
{
    ValidateSearchPath(path);
    fSearchPaths.insert(begin(fSearchPaths), path);
}

auto fair::mq::PluginManager::ProgramOptions() -> po::options_description
{
    auto plugin_options = po::options_description{"Plugin Manager"};
    plugin_options.add_options()
        ("plugin-search-path,S", po::value<vector<string>>()->multitoken(),
         "List of plugin search paths.\n\n"
         "* Override default search path, e.g.\n"
         "  -S /home/user/lib /lib\n"
         "* Append(>) or prepend(<) to default search path, e.g.\n"
         "  -S >/lib </home/user/lib\n"
         "* If you mix the overriding and appending/prepending syntaxes, the overriding paths act as default search path, e.g.\n"
         "  -S /usr/lib >/lib </home/user/lib /usr/local/lib results in /home/user/lib,/usr/local/lib,/usr/lib/,/lib")
        ("plugin,P", po::value<vector<string>>(),
         "List of plugin names to load in order, e.g. if the file is called 'libFairMQPlugin_example.so', just list 'example' or 'd:example' here. To load a prelinked plugin, list 'p:example' here.");
    return plugin_options;
}

auto fair::mq::PluginManager::MakeFromCommandLineOptions(const vector<string> args) -> shared_ptr<PluginManager>
{
    // Parse command line options
    auto options = ProgramOptions();
    auto vm = po::variables_map{};
    try
    {
        auto parsed = po::command_line_parser(args).options(options).allow_unregistered().run();
        po::store(parsed, vm);
        po::notify(vm);
    } catch (const po::error& e)
    {
        throw ProgramOptionsParseError{ToString("Error occured while parsing the 'Plugin Manager' program options: ", e.what())};
    }

    // Process plugin search paths
    auto append = vector<fs::path>{};
    auto prepend = vector<fs::path>{};
    auto searchPaths = vector<fs::path>{};
    if (vm.count("plugin-search-path"))
    {
        for (const auto& path : vm["plugin-search-path"].as<vector<string>>())
        {
            if      (path.substr(0, 1) == "<") { prepend.emplace_back(path.substr(1)); }
            else if (path.substr(0, 1) == ">") { append.emplace_back(path.substr(1)); }
            else                               { searchPaths.emplace_back(path); }
        }
    }

    // Create PluginManager with supplied options
    auto mgr = make_shared<PluginManager>();
    mgr->SetSearchPaths(searchPaths);
    for(const auto& path : prepend) { mgr->PrependSearchPath(path); }
    for(const auto& path : append)  { mgr->AppendSearchPath(path); }
    if (vm.count("plugin")) { mgr->LoadPlugins(vm["plugin"].as<vector<string>>()); }

    // Return the plugin manager and command line options, that have not been recognized.
    return mgr;
}

auto fair::mq::PluginManager::LoadPlugin(const string& pluginName) -> void
{
    if (pluginName.substr(0,2) == "p:")
    {
        // Mechanism A: prelinked dynamic
        LoadPluginPrelinkedDynamic(pluginName.substr(2));
    }
    else if (pluginName.substr(0,2) == "d:")
    {
        // Mechanism B: dynamic
        LoadPluginDynamic(pluginName.substr(2));
    }
    else
    {
        // Mechanism B: dynamic (default)
        LoadPluginDynamic(pluginName);
    }
}

auto fair::mq::PluginManager::LoadPluginPrelinkedDynamic(const string& pluginName) -> void
{
    // Load symbol
    if (fPluginFactories.find(pluginName) == fPluginFactories.end())
    {
        try
        {
            LoadSymbols(pluginName, dll::program_location());
        }
        catch (boost::system::system_error& e)
        {
            throw PluginLoadError(ToString("An error occurred while loading prelinked dynamic plugin ", pluginName, ": ", e.what()));
        }
    }
}

auto fair::mq::PluginManager::LoadPluginDynamic(const string& pluginName) -> void
{
    // Search plugin and load, if found
    if (fPluginFactories.find(pluginName) == fPluginFactories.end())
    {
        auto success = false;
        for(const auto& searchPath : SearchPaths())
        {
            try
            {
                LoadSymbols(
                    pluginName,
                    searchPath / ToString(LibPrefix(), pluginName),
                    dll::load_mode::append_decorations
                );

                fPluginOrder.push_back(pluginName);
                success = true;
                break;
            }
            catch (boost::system::system_error& e)
            {
                if(string{e.what()}.find("No such file or directory") == string::npos)
                {
                    throw PluginLoadError(ToString("An error occurred while loading dynamic plugin ", pluginName, ": ", e.what()));
                }
            }
        }
        if(!success) { throw PluginLoadError(ToString("The plugin ", pluginName, " could not be found in the plugin search paths.")); }
    }
}

auto fair::mq::PluginManager::InstantiatePlugin(const string& pluginName) -> void
{
    if (fPlugins.find(pluginName) == fPlugins.end())
    {
        fPlugins[pluginName] = fPluginFactories[pluginName](*fPluginServices);
    }
}

auto fair::mq::PluginManager::InstantiatePlugins() -> void
{
    for(const auto& pluginName : fPluginOrder)
    {
        try
        {
            InstantiatePlugin(pluginName);
        }
        catch (std::exception& e)
        {
            throw PluginInstantiationError(ToString("An error occurred while instantiating plugin ", pluginName, ": ", e.what()));
        }
    }
}
