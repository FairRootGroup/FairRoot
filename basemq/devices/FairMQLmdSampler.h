/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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

#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
extern "C" {
#include "f_evt.h"
#include "s_bufhe_swap.h"
#include "s_filhe_swap.h"
}

#include <boost/filesystem.hpp>
#include <fairlogger/Logger.h>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class FairMQLmdSampler : public fair::mq::Device
{
  public:
    FairMQLmdSampler()
        : fCurrentFile(0)
        , fNEvent(0)
        , fCurrentEvent(0)
        , fFileNames()
        , fInputChannel()
        , fEvent(nullptr)
        , fBuffer(nullptr)
        , fEventData(nullptr)
        , fSubEvent(nullptr)
        , fInfoHeader(nullptr)
        , fStop(false)
        , fMsgCounter(0)
        , fSubEventChanMap()
        , fFilename()
        , fType(0)
        , fSubType(0)
        , fProcId(0)
        , fSubCrate(0)
        , fControl(0)
        , fChanName()
    {}

    FairMQLmdSampler(const FairMQLmdSampler&) = delete;
    FairMQLmdSampler operator=(const FairMQLmdSampler&) = delete;

    virtual ~FairMQLmdSampler() {}

    void AddSubEvtKey(short type,
                      short subType,
                      short procid,
                      short subCrate,
                      short control,
                      const std::string& channelName)
    {
        SubEvtKey key(type, subType, procid, subCrate, control);
        if (fSubEventChanMap.count(key)) {
            LOG(warn) << "FairMQLmdSampler : subevent header key '(" << type << "," << subType << "," << procid << ","
                      << subCrate << "," << control << ")' has already been defined with channel name '"
                      << fSubEventChanMap.at(key)
                      << "'. it will be overwritten with new channel name = " << channelName;
        }
        fSubEventChanMap[key] = channelName;
    }

    void AddDir(const std::string& dir)
    {
        boost::filesystem::path directory = dir;

        if (boost::filesystem::exists(directory)) {
            boost::filesystem::directory_iterator end_itr;

            for (boost::filesystem::directory_iterator itr(directory); itr != end_itr; ++itr) {
                if (boost::filesystem::is_regular_file(itr->path())) {
                    std::string currentFile = itr->path().string();
                    AddFile(currentFile);
                }
            }
        } else {
            LOG(warn) << "FairMQLmdSampler: directory '" << directory.string() << "' not found";
        }
    }
    void AddFile(const std::string& fileName)
    {
        boost::filesystem::path filepath = fileName;
        if (boost::filesystem::exists(filepath)) {
            fFileNames.push_back(fileName);
        } else {
            LOG(warn) << "FairMQLmdSampler: file '" << fileName << "' not found";
        }
    }

  protected:
    void InitTask()
    {
        fFilename = fConfig->GetValue<std::string>("input-file-name");
        fType = fConfig->GetValue<short>("lmd-type");
        fSubType = fConfig->GetValue<short>("lmd-sub-type");
        fProcId = fConfig->GetValue<short>("lmd-proc-id");
        fSubCrate = fConfig->GetValue<short>("lmd-sub-crate");
        fControl = fConfig->GetValue<short>("lmd-control");
        fChanName = fConfig->GetValue<std::string>("lmd-chan-name");

        AddFile(fFilename);
        // combination of sub-event header value = one special channel
        // this channel MUST be defined in the json file for the MQ configuration
        AddSubEvtKey(fType, fSubType, fProcId, fSubCrate, fControl, fChanName);

        if (fFileNames.empty()) {
            throw std::runtime_error(std::string("FairMQLmdSampler::InitTask: No files provided"));
        }

        std::string name = fFileNames.at(fCurrentFile);
        if (!OpenNextFile(name)) {
            throw std::runtime_error(std::string("FairMQLmdSampler::InitTask: cannot open file ") + name);
        }

        fCurrentFile += 1;
        // Init Counters
        fNEvent = 0;
        fCurrentEvent = 0;
    }
    void Run()
    {
        while (!NewStatePending())   //&& !fStop)
        {
            if (1 == ReadEvent()) {
                break;
            }
        }
        LOG(info) << "Sent " << fMsgCounter << " messages.";
    }

    int ReadEvent()
    {
        void* evtptr = &fEvent;
        void* buffptr = &fBuffer;

        // INTS4 f_evt_get_event(s_evt_channel*, INTS4**, INTS4**); // -> in f_evt.h
        /*-               GETEVT__SUCCESS=0 : success.                        */
        /*-               GETEVT__FRAGMENT=1: Event fragment found.           */
        /*-               GETEVT__NOMORE=3  : No more events.                 */
        /*-               GETEVT__RDERR=6   : read server or file error       */
        /*-               GETEVT__TIMEOUT=9 : when enabled by f_evt_timeout   */
        int status = f_evt_get_event(&fInputChannel, static_cast<INTS4**>(evtptr), static_cast<INTS4**>(buffptr));
        // int fuEventCounter = fEvent->l_count;
        // int fCurrentMbsEventNo = fuEventCounter;

        // LOG(debug) << "STATUS = " << status;
        if (GETEVT__SUCCESS != status)   // if f_evt_get_event not successfull close if nomore evt or look to another
                                         // file and start again
        {
            // LOG(debug) << "FairMQLmdSampler::ReadEvent()";

            CHARS* sErrorString = NULL;
            f_evt_error(status, sErrorString, 0);

            if (GETEVT__NOMORE == status) {
                Close();
            }

            // fCurrentFile incremented in InitTask once
            if (fCurrentFile >= static_cast<int>(fFileNames.size())) {
                fStop = true;
                return 1;
            }

            std::string name = fFileNames.at(fCurrentFile);
            if (!OpenNextFile(name)) {
                return 1;
            } else {
                fCurrentFile += 1;
                return ReadEvent();
            }
        }

        // Store Start Times
        // if (fCurrentEvent==0 )
        //      Unpack((int*)fBuffer, sizeof(s_bufhe), -4, -4, -4, -4, -4);
        // Decode event header
        // bool result = false;
        /*bool result = */
        // Unpack((int*)fEvent, sizeof(s_ve10_1), -2, -2, -2, -2, -2);

        int nrSubEvts = f_evt_get_subevent(fEvent, 0, NULL, NULL, NULL);
        int sebuflength;
        short setype;
        short sesubtype;
        short seprocid;
        short sesubcrate;
        short secontrol;

        // LOG(debug) << "FairMQLmdSampler::ReadEvent => Found " << nrSubEvts << " Sub-event ";
        // if (fCurrentEvent%10000==0)
        // cout << " -I- LMD_ANA:  evt# " <<  fCurrentEvent << "  n_subevt# " << nrSubEvts << " evt processed# " <<
        // fNEvent <<  " : " << fEvent->l_count << endl;

        for (int i = 1; i <= nrSubEvts; i++) {
            void* SubEvtptr = &fSubEvent;
            void* EvtDataptr = &fEventData;
            int nrlongwords;
            status = f_evt_get_subevent(
                fEvent, i, static_cast<int**>(SubEvtptr), static_cast<int**>(EvtDataptr), &nrlongwords);

            if (status) {
                return 1;
            }

            sebuflength = nrlongwords;
            setype = fSubEvent->i_type;
            sesubtype = fSubEvent->i_subtype;
            seprocid = fSubEvent->i_procid;
            sesubcrate = fSubEvent->h_subcrate;
            secontrol = fSubEvent->h_control;

            // cout << setype << "  " << sesubtype << "  " << seprocid << "  " << sesubcrate << "  " << secontrol <<
            // endl;

            // Data to send : fEventData
            SubEvtKey key(setype, sesubtype, seprocid, sesubcrate, secontrol);

            if (!fSubEventChanMap.count(key)) {
                // LOG(debug) << "FairMQLmdSampler::ReadEvent: sub-event key not registered";
            } else {
                // LOG(debug) << "array size = " << sebuflength;
                // LOG(debug) << "fEventData = " << *fEventData;

                std::string chanName = fSubEventChanMap.at(key);
                // LOG(debug) << "chanName = " << chanName;

                fair::mq::Parts parts;

                // send header
                // auto header(fTransportFactory->CreateMessage(fSubEvent, sizeof(fSubEvent),
                // free_buffer, nullptr)); fChannels.at(chanName).at(0).SendPart(header);

                int* arraySize = new int(sebuflength);

                parts.AddPart(NewMessage(
                    arraySize,
                    sizeof(int),
                    [](void* /*data*/, void* hint) { delete static_cast<int*>(hint); },
                    arraySize));
                parts.AddPart(NewMessage(
                    fEventData,
                    sebuflength,
                    [](void* /*data*/, void* /*hint*/) { /*LOG(debug) << "empty deleter";*/ },
                    nullptr));
                Send(parts, chanName);
                fMsgCounter++;
                /*
                if (Unpack(fEventData, sebuflength,
                          setype, sesubtype,
                          seprocid, sesubcrate, secontrol))
                {
                    result = true;
                }
                */
            }
        }

        // Increment evt counters.
        fNEvent++;
        fCurrentEvent++;

        /*if (! result)
        {
            return 2;
        }*/

        return 0;
    }
    bool OpenNextFile(const std::string& fileName)
    {
        int inputMode = GETEVT__FILE;
        void* headptr = &fInfoHeader;
        INTS4 status;

        LOG(info) << "File " << fileName << " will be opened.";

        status = f_evt_get_open(
            inputMode, const_cast<char*>(fileName.c_str()), &fInputChannel, static_cast<char**>(headptr), 1, 1);

        if (status) {
            LOG(error) << "File " << fileName << " opening failed.";
            return false;
        }

        LOG(info) << "File " << fileName << " opened.";

        // Decode File Header
        // bool result = Unpack((int*)fInfoHeader, sizeof(s_filhe), -4, -4, -4, -4, -4);

        return true;
    }

    void Close()
    {
        f_evt_get_close(&fInputChannel);
        // Unpack((Int_t*)fBuffer, sizeof(s_bufhe), -4, -4, -4, -4, -4);
        fCurrentEvent = 0;
    }

  private:
    int fCurrentFile;
    int fNEvent;
    int fCurrentEvent;
    std::vector<std::string> fFileNames;
    s_evt_channel fInputChannel;
    s_ve10_1* fEvent;
    s_bufhe* fBuffer;
    int* fEventData;
    s_ves10_1* fSubEvent;
    s_filhe* fInfoHeader;
    bool fStop;
    int fMsgCounter;
    typedef std::tuple<short, short, short, short, short> SubEvtKey;
    std::map<SubEvtKey, std::string> fSubEventChanMap;

    std::string fFilename;
    short fType;
    short fSubType;
    short fProcId;
    short fSubCrate;
    short fControl;
    std::string fChanName;
};

#endif /* !FAIRMQLMDSAMPLER_H */
