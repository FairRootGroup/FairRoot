/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairProgOptions.h
 * Author: winckler
 *
 * Created on March 11, 2015, 5:38 PM
 */

#ifndef FAIRPROGOPTIONS_H
#define FAIRPROGOPTIONS_H

#include "FairMQLogger.h"
#include "FairProgOptionsHelper.h"

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <mutex>
#include <tuple>

/*
 * FairProgOptions abstract base class
 * parse command line, configuration file options.
 *
 * The user defines in the derived class the option descriptions and
 * the pure virtual ParseAll() method
 *
 * class MyOptions : public FairProgOptions
 * {
 *      public :
 *      MyOptions() : FairProgOptions()
 *      {
 *          fCmdlineOptions.add(fGenericDesc);
 *          fVisibleOptions.add(fCmdlineOptions);
 *      }
 *      virtual ~MyOptions() {}
 *      virtual void ParseAll(const int argc, char** argv, bool allowUnregistered = false)
 *      {
 *          if (ParseCmdLine(argc, argv, fCmdlineOptions, fVarMap, allowUnregistered))
 *          {
 *              exit(EXIT_FAILURE);
 *          }
 *
 *          PrintOptions();
 *      }
 * }
 */

namespace po = boost::program_options;
namespace fs = boost::filesystem;

class FairProgOptions
{
  public:
    FairProgOptions();
    virtual ~FairProgOptions();

    auto GetPropertyKeys() const -> std::vector<std::string>
    {
        std::lock_guard<std::mutex> lock{fConfigMutex};

        std::vector<std::string> result;

        for (const auto& it : fVarMap)
        {
            result.push_back(it.first.c_str());
        }

        return result;
    }

    //  add options_description
    int AddToCmdLineOptions(const po::options_description optDesc, bool visible = true);
    po::options_description& GetCmdLineOptions();

    // get value corresponding to the key
    template<typename T>
    T GetValue(const std::string& key) const
    {
        std::unique_lock<std::mutex> lock(fConfigMutex);

        T val = T();
        try
        {
            if (fVarMap.count(key))
            {
                val = fVarMap[key].as<T>();
            }
            else
            {
                LOG(error) << "Config has no key: " << key;
            }
        }
        catch (std::exception& e)
        {
            LOG(error) << "Exception thrown for the key '" << key << "'";
            LOG(error) << e.what();
        }

        return val;
    }

    // Given a key, convert the variable value to string
    std::string GetStringValue(const std::string& key)
    {
        std::unique_lock<std::mutex> lock(fConfigMutex);

        std::string valueStr;
        try
        {
            if (fVarMap.count(key))
            {
                valueStr = FairMQ::ConvertVariableValue<FairMQ::ToString>().Run(fVarMap.at(key));
            }
        }
        catch (std::exception& e)
        {
            LOG(error) << "Exception thrown for the key '" << key << "'";
            LOG(error) << e.what();
        }

        return valueStr;
    }

    int Count(const std::string& key) const
    {
        std::unique_lock<std::mutex> lock(fConfigMutex);

        return fVarMap.count(key);
    }

    //restrict conversion to fundamental types
    template<typename T>
    T ConvertTo(const std::string& strValue)
    {
        if (std::is_arithmetic<T>::value)
        {
            std::istringstream iss(strValue);
            T val;
            iss >> val;
            return val;
        }
        else
        {
            LOG(error) << "the provided string " << strValue << " cannot be converted in the requested type. The target types must be arithmetic types";
        }
    }

    const po::variables_map& GetVarMap() const { return fVarMap; }

    // boost prog options parsers
    int ParseCmdLine(const int argc, char const* const* argv, const po::options_description& desc, po::variables_map& varmap, bool allowUnregistered = false);
    int ParseCmdLine(const int argc, char const* const* argv, const po::options_description& desc, bool allowUnregistered = false);

    virtual int ParseAll(const int argc, char const* const* argv, bool allowUnregistered = false) = 0;// TODO change return type to bool and propagate to executable

    virtual int PrintOptions();
    virtual int PrintOptionsRaw();

  protected:
    // options container
    po::variables_map fVarMap;

    // basic description categories
    po::options_description fGeneralDesc;

    po::options_description fCmdLineOptions;

    // Description which is printed in help command line
    po::options_description fVisibleOptions;

    mutable std::mutex fConfigMutex;

    virtual int ImmediateOptions() = 0;

    // UpdateVarMap() and replace() --> helper functions to modify the value of variable map after calling po::store
    template<typename T>
    void UpdateVarMap(const std::string& key, const T& val)
    {
        replace(fVarMap, key, val);
    }

    template<typename T>
    void replace(std::map<std::string, po::variable_value>& vm, const std::string& key, const T& val)
    {
        vm[key].value() = boost::any(val);
    }

  private:
    // Methods below are helper functions used in the PrintOptions method
    using VarValInfo_t = std::tuple<std::string, std::string, std::string, std::string>;
    using MapVarValInfo_t = std::map<std::string, VarValInfo_t>;

    VarValInfo_t GetVariableValueInfo(const po::variable_value& varValue);

    static void Max(int& val, const int& comp)
    {
        if (comp > val)
        {
            val = comp;
        }
    }
};

#endif /* FAIRPROGOPTIONS_H */
