/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairMQParser.cxx
 * Author: winckler
 * 
 * Created on May 14, 2015, 5:01 PM
 */

#include "FairMQParser.h"
#include "FairMQLogger.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

namespace FairMQParser
{

// TODO : add key-value map<string,string> parameter  for replacing/updating values from keys
// function that convert property tree (given the xml or json structure) to FairMQMap
FairMQMap ptreeToMQMap(const boost::property_tree::ptree& pt, const string& id, const string& rootNode, const string& formatFlag)
{
    // Create fair mq map
    FairMQMap channelMap;
    //Helper::PrintPropertyTree(pt);
    //Helper::PrintDeviceList(pt.get_child(rootNode), formatFlag);
    // Extract value from boost::property_tree
    Helper::DeviceParser(pt.get_child(rootNode), channelMap, id, formatFlag);

    if (channelMap.empty())
    {
        LOG(warn) << "---- No channel keys found for " << id;
        LOG(warn) << "---- Check the JSON inputs and/or command line inputs";
    }

    return channelMap;
}

FairMQMap JSON::UserParser(const string& filename, const string& deviceId, const string& rootNode)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(filename, pt);
    return ptreeToMQMap(pt, deviceId, rootNode);
}

FairMQMap JSON::UserParser(stringstream& input, const string& deviceId, const string& rootNode)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(input, pt);
    return ptreeToMQMap(pt, deviceId, rootNode);
}

FairMQMap XML::UserParser(const string& filename, const string& deviceId, const string& rootNode)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(filename, pt);
    return ptreeToMQMap(pt, deviceId, rootNode, "xml");
}

FairMQMap XML::UserParser(stringstream& input, const string& deviceId, const string& rootNode)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(input, pt);
    return ptreeToMQMap(pt, deviceId, rootNode, "xml");
}

namespace Helper
{

void PrintDeviceList(const boost::property_tree::ptree& tree, const string& formatFlag)
{
    string deviceIdKey;

    // do a first loop just to print the device-id in json input
    for (const auto& p : tree)
    {
        if (p.first == "devices")
        {
            for (const auto& q : p.second.get_child(""))
            {
                string key = q.second.get<string>("key", "");
                if (key != "")
                {
                    deviceIdKey = key;
                    LOG(debug) << "Found config for device key '" << deviceIdKey << "' in JSON input";
                }
                else
                {
                    deviceIdKey = q.second.get<string>("id");
                    LOG(debug) << "Found config for device id '" << deviceIdKey << "' in JSON input";
                }
            }
        }

        if (p.first == "device")
        {
            // get id attribute to choose the device
            if (formatFlag == "xml")
            {
                deviceIdKey = p.second.get<string>("<xmlattr>.id");
                LOG(debug) << "Found config for '" << deviceIdKey << "' in XML input";
            }

            if (formatFlag == "json")
            {
                string key = p.second.get<string>("key", "");
                if (key != "")
                {
                    deviceIdKey = key;
                    LOG(debug) << "Found config for device key '" << deviceIdKey << "' in JSON input";
                }
                else
                {
                    deviceIdKey = p.second.get<string>("id");
                    LOG(debug) << "Found config for device id '" << deviceIdKey << "' in JSON input";
                }
            }
        }
    }
}

void DeviceParser(const boost::property_tree::ptree& tree, FairMQMap& channelMap, const string& deviceId, const string& formatFlag)
{
    string deviceIdKey;

    LOG(debug) << "Looking for '" << deviceId << "' id/key in the provided config file...";

    // For each node in fairMQOptions
    for (const auto& p : tree)
    {
        if (p.first == "devices")
        {
            for (const auto& q : p.second)
            {
                // check if key is provided, otherwise use id
                string key = q.second.get<string>("key", "");

                if (key != "")
                {
                    deviceIdKey = key;
                    // LOG(debug) << "Found config for device key '" << deviceIdKey << "' in JSON input";
                }
                else
                {
                    deviceIdKey = q.second.get<string>("id");
                    // LOG(debug) << "Found config for device id '" << deviceIdKey << "' in JSON input";
                }

                // if not correct device id, do not fill MQMap
                if (deviceId != deviceIdKey)
                {
                    continue;
                }

                LOG(debug) << "Found with following channels:";

                ChannelParser(q.second, channelMap, formatFlag);
            }
        }

        if (p.first == "device")
        {
            if (formatFlag == "xml")
            {
                deviceIdKey = p.second.get<string>("<xmlattr>.id");
            }

            if (formatFlag == "json")
            {
                // check if key is provided, otherwise use id
                string key = p.second.get<string>("key", "");

                if (key != "")
                {
                    deviceIdKey = key;
                    // LOG(debug) << "Found config for device key '" << deviceIdKey << "' in JSON input";
                }
                else
                {
                    deviceIdKey = p.second.get<string>("id");
                    // LOG(debug) << "Found config for device id '" << deviceIdKey << "' in JSON input";
                }
            }

            // if not correct device id, do not fill MQMap
            if (deviceId != deviceIdKey)
            {
                continue;
            }

            LOG(debug) << "Found with following channels:";

            ChannelParser(p.second, channelMap, formatFlag);
        }
    }
}

void ChannelParser(const boost::property_tree::ptree& tree, FairMQMap& channelMap, const string& formatFlag)
{
    string channelKey;

    for (const auto& p : tree)
    {
        if (p.first == "channels")
        {
            for (const auto& q : p.second)
            {
                channelKey = q.second.get<string>("name");

                int numSockets = q.second.get<int>("numSockets", 0);

                // try to get common properties to use for all subChannels
                FairMQChannel commonChannel;
                commonChannel.UpdateType(q.second.get<string>("type", commonChannel.GetType()));
                commonChannel.UpdateMethod(q.second.get<string>("method", commonChannel.GetMethod()));
                commonChannel.UpdateAddress(q.second.get<string>("address", commonChannel.GetAddress()));
                commonChannel.UpdateTransport(q.second.get<string>("transport", commonChannel.GetTransport()));
                commonChannel.UpdateSndBufSize(q.second.get<int>("sndBufSize", commonChannel.GetSndBufSize()));
                commonChannel.UpdateRcvBufSize(q.second.get<int>("rcvBufSize", commonChannel.GetRcvBufSize()));
                commonChannel.UpdateSndKernelSize(q.second.get<int>("sndKernelSize", commonChannel.GetSndKernelSize()));
                commonChannel.UpdateRcvKernelSize(q.second.get<int>("rcvKernelSize", commonChannel.GetRcvKernelSize()));
                commonChannel.UpdateRateLogging(q.second.get<int>("rateLogging", commonChannel.GetRateLogging()));

                // temporary FairMQChannel container
                vector<FairMQChannel> channelList;

                if (numSockets > 0)
                {
                    LOG(debug) << "" << channelKey << ":";
                    LOG(debug) << "\tnumSockets of " << numSockets << " specified,";
                    LOG(debug) << "\tapplying common settings to each:";

                    LOG(debug) << "\ttype          = " << commonChannel.GetType();
                    LOG(debug) << "\tmethod        = " << commonChannel.GetMethod();
                    LOG(debug) << "\taddress       = " << commonChannel.GetAddress();
                    LOG(debug) << "\ttransport     = " << commonChannel.GetTransport();
                    LOG(debug) << "\tsndBufSize    = " << commonChannel.GetSndBufSize();
                    LOG(debug) << "\trcvBufSize    = " << commonChannel.GetRcvBufSize();
                    LOG(debug) << "\tsndKernelSize = " << commonChannel.GetSndKernelSize();
                    LOG(debug) << "\trcvKernelSize = " << commonChannel.GetRcvKernelSize();
                    LOG(debug) << "\trateLogging   = " << commonChannel.GetRateLogging();

                    for (int i = 0; i < numSockets; ++i)
                    {
                        FairMQChannel channel(commonChannel);
                        channelList.push_back(channel);
                    }
                }
                else
                {
                    SocketParser(q.second.get_child(""), channelList, channelKey, commonChannel);
                }

                channelMap.insert(make_pair(channelKey, move(channelList)));
            }
        }

        if (p.first == "channel")
        {
            // try to get common properties to use for all subChannels
            FairMQChannel commonChannel;
            int numSockets = 0;

            // get name attribute to form key
            if (formatFlag == "xml")
            {
                channelKey = p.second.get<string>("<xmlattr>.name");
            }

            if (formatFlag == "json")
            {
                channelKey = p.second.get<string>("name");

                numSockets = p.second.get<int>("numSockets", 0);

                // try to get common properties to use for all subChannels
                commonChannel.UpdateType(p.second.get<string>("type", commonChannel.GetType()));
                commonChannel.UpdateMethod(p.second.get<string>("method", commonChannel.GetMethod()));
                commonChannel.UpdateAddress(p.second.get<string>("address", commonChannel.GetAddress()));
                commonChannel.UpdateTransport(p.second.get<string>("transport", commonChannel.GetTransport()));
                commonChannel.UpdateSndBufSize(p.second.get<int>("sndBufSize", commonChannel.GetSndBufSize()));
                commonChannel.UpdateRcvBufSize(p.second.get<int>("rcvBufSize", commonChannel.GetRcvBufSize()));
                commonChannel.UpdateSndKernelSize(p.second.get<int>("sndKernelSize", commonChannel.GetSndKernelSize()));
                commonChannel.UpdateRcvKernelSize(p.second.get<int>("rcvKernelSize", commonChannel.GetRcvKernelSize()));
                commonChannel.UpdateRateLogging(p.second.get<int>("rateLogging", commonChannel.GetRateLogging()));
            }

            // temporary FairMQChannel container
            vector<FairMQChannel> channelList;

            if (numSockets > 0)
            {
                LOG(debug) << "" << channelKey << ":";
                LOG(debug) << "\tnumSockets of " << numSockets << " specified,";
                LOG(debug) << "\tapplying common settings to each:";

                LOG(debug) << "\ttype          = " << commonChannel.GetType();
                LOG(debug) << "\tmethod        = " << commonChannel.GetMethod();
                LOG(debug) << "\taddress       = " << commonChannel.GetAddress();
                LOG(debug) << "\ttransport     = " << commonChannel.GetTransport();
                LOG(debug) << "\tsndBufSize    = " << commonChannel.GetSndBufSize();
                LOG(debug) << "\trcvBufSize    = " << commonChannel.GetRcvBufSize();
                LOG(debug) << "\tsndKernelSize = " << commonChannel.GetSndKernelSize();
                LOG(debug) << "\trcvKernelSize = " << commonChannel.GetRcvKernelSize();
                LOG(debug) << "\trateLogging   = " << commonChannel.GetRateLogging();

                for (int i = 0; i < numSockets; ++i)
                {
                    FairMQChannel channel(commonChannel);
                    channelList.push_back(channel);
                }
            }
            else
            {
                SocketParser(p.second.get_child(""), channelList, channelKey, commonChannel);
            }

            channelMap.insert(make_pair(channelKey, move(channelList)));
        }
    }
}

void SocketParser(const boost::property_tree::ptree& tree, vector<FairMQChannel>& channelList, const string& channelName, const FairMQChannel& commonChannel)
{
    // for each socket in channel
    int socketCounter = 0;

    for (const auto& p : tree)
    {
        if (p.first == "sockets")
        {
            for (const auto& q : p.second)
            {
                // create new channel and apply setting from the common channel
                FairMQChannel channel(commonChannel);

                // if the socket field specifies or overrides something from the common channel, apply those settings
                channel.UpdateType(q.second.get<string>("type", channel.GetType()));
                channel.UpdateMethod(q.second.get<string>("method", channel.GetMethod()));
                channel.UpdateAddress(q.second.get<string>("address", channel.GetAddress()));
                channel.UpdateTransport(q.second.get<string>("transport", channel.GetTransport()));
                channel.UpdateSndBufSize(q.second.get<int>("sndBufSize", channel.GetSndBufSize()));
                channel.UpdateRcvBufSize(q.second.get<int>("rcvBufSize", channel.GetRcvBufSize()));
                channel.UpdateSndKernelSize(q.second.get<int>("sndKernelSize", channel.GetSndKernelSize()));
                channel.UpdateRcvKernelSize(q.second.get<int>("rcvKernelSize", channel.GetRcvKernelSize()));
                channel.UpdateRateLogging(q.second.get<int>("rateLogging", channel.GetRateLogging()));

                LOG(debug) << "" << channelName << "[" << socketCounter << "]:";
                LOG(debug) << "\ttype          = " << channel.GetType();
                LOG(debug) << "\tmethod        = " << channel.GetMethod();
                LOG(debug) << "\taddress       = " << channel.GetAddress();
                LOG(debug) << "\ttransport     = " << channel.GetTransport();
                LOG(debug) << "\tsndBufSize    = " << channel.GetSndBufSize();
                LOG(debug) << "\trcvBufSize    = " << channel.GetRcvBufSize();
                LOG(debug) << "\tsndKernelSize = " << channel.GetSndKernelSize();
                LOG(debug) << "\trcvKernelSize = " << channel.GetRcvKernelSize();
                LOG(debug) << "\trateLogging   = " << channel.GetRateLogging();

                channelList.push_back(channel);
                ++socketCounter;
            }
        }

        if (p.first == "socket")
        {
            // create new channel and apply setting from the common channel
            FairMQChannel channel(commonChannel);

            // if the socket field specifies or overrides something from the common channel, apply those settings
            channel.UpdateType(p.second.get<string>("type", channel.GetType()));
            channel.UpdateMethod(p.second.get<string>("method", channel.GetMethod()));
            channel.UpdateAddress(p.second.get<string>("address", channel.GetAddress()));
            channel.UpdateTransport(p.second.get<string>("transport", channel.GetTransport()));
            channel.UpdateSndBufSize(p.second.get<int>("sndBufSize", channel.GetSndBufSize()));
            channel.UpdateRcvBufSize(p.second.get<int>("rcvBufSize", channel.GetRcvBufSize()));
            channel.UpdateSndKernelSize(p.second.get<int>("sndKernelSize", channel.GetSndKernelSize()));
            channel.UpdateRcvKernelSize(p.second.get<int>("rcvKernelSize", channel.GetRcvKernelSize()));
            channel.UpdateRateLogging(p.second.get<int>("rateLogging", channel.GetRateLogging()));

            LOG(debug) << "" << channelName << "[" << socketCounter << "]:";
            LOG(debug) << "\ttype          = " << channel.GetType();
            LOG(debug) << "\tmethod        = " << channel.GetMethod();
            LOG(debug) << "\taddress       = " << channel.GetAddress();
            LOG(debug) << "\ttransport     = " << channel.GetTransport();
            LOG(debug) << "\tsndBufSize    = " << channel.GetSndBufSize();
            LOG(debug) << "\trcvBufSize    = " << channel.GetRcvBufSize();
            LOG(debug) << "\tsndKernelSize = " << channel.GetSndKernelSize();
            LOG(debug) << "\trcvKernelSize = " << channel.GetRcvKernelSize();
            LOG(debug) << "\trateLogging   = " << channel.GetRateLogging();

            channelList.push_back(channel);
            ++socketCounter;
        }
    } // end socket loop

    if (socketCounter)
    {
        LOG(debug) << "Found " << socketCounter << " socket(s) in channel.";
    }
    else
    {
        LOG(debug) << "" << channelName << ":";
        LOG(debug) << "\tNo sockets specified,";
        LOG(debug) << "\tapplying common settings to the channel:";

        FairMQChannel channel(commonChannel);

        LOG(debug) << "\ttype          = " << channel.GetType();
        LOG(debug) << "\tmethod        = " << channel.GetMethod();
        LOG(debug) << "\taddress       = " << channel.GetAddress();
        LOG(debug) << "\ttransport     = " << channel.GetTransport();
        LOG(debug) << "\tsndBufSize    = " << channel.GetSndBufSize();
        LOG(debug) << "\trcvBufSize    = " << channel.GetRcvBufSize();
        LOG(debug) << "\tsndKernelSize = " << channel.GetSndKernelSize();
        LOG(debug) << "\trcvKernelSize = " << channel.GetRcvKernelSize();
        LOG(debug) << "\trateLogging   = " << channel.GetRateLogging();

        channelList.push_back(channel);
    }
}

void PrintPropertyTree(const boost::property_tree::ptree& tree, int level)
{
  for (const auto& p : tree) {
    cout << setw(level+1) << level << ": " << p.first << " " << p.second.get_value<string>() << endl;
    PrintPropertyTree(p.second.get_child(""), level + 1);
  }
}

} // Helper namespace

} // FairMQParser namespace
