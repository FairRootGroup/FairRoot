/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
 /* 
 * File:   FairMQLmdSampler.h
 * Author: winckler
 *
 * Created on October 27, 2015, 2:07 PM
 */

#ifndef FAIRMQLMDSAMPLER_H
#define FAIRMQLMDSAMPLER_H

extern "C"
{
#include "f_evt.h"
#include "s_filhe_swap.h"
#include "s_bufhe_swap.h"
}

#include <boost/filesystem.hpp>

#include "FairMQDevice.h"
#include "FairMQMessage.h"

#include <string>
#include <vector>
#include <tuple>
#include <map>

namespace fs = boost::filesystem;

class FairMQLmdSampler : public FairMQDevice
{
    typedef fs::path path;

  public:
    FairMQLmdSampler();
    FairMQLmdSampler(const FairMQLmdSampler&) = delete;
    FairMQLmdSampler operator=(const FairMQLmdSampler&) = delete;

    virtual ~FairMQLmdSampler();

    void AddSubEvtKey(short type, short subType, short procid, short subCrate, short control, const std::string& channelName);
    void AddDir(const std::string& dir);
    void AddFile(const std::string& fileName);

  protected:
    void InitTask();
    void Run();
    int ReadEvent();
    bool OpenNextFile(const std::string& fileName);

    void Close();

  private:
    int fCurrentFile;
    int fNEvent;
    int fCurrentEvent;
    std::vector<std::string> fFileNames;
    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    int* fxEventData;
    s_ves10_1* fxSubEvent;
    s_filhe* fxInfoHeader;
    bool stop;
    int fMsgCounter;
    typedef std::tuple<short,short,short,short,short> SubEvtKey;
    std::map<SubEvtKey, std::string> fSubEventChanMap;
};

#endif  /* !FAIRMQLMDSAMPLER_H */
