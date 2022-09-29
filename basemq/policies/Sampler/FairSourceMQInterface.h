/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRSOURCEMQINTERFACE_H
#define FAIRSOURCEMQINTERFACE_H

#include "BaseSourcePolicy.h"
#include "FairFileSource.h"
#include "FairRunAna.h"

#include <fairlogger/Logger.h>
#include <functional>
#include <type_traits>

template<typename T, typename U>
using enable_if_match = typename std::enable_if<std::is_same<T, U>::value, int>::type;

template<typename FairSourceType, typename DataType>
class FairSourceMQInterface : public BaseSourcePolicy<FairSourceMQInterface<FairSourceType, DataType>>
{
    typedef DataType* DataType_ptr;
    typedef FairSourceMQInterface<FairSourceType, DataType> this_type;

  public:
    FairSourceMQInterface()
        : BaseSourcePolicy<FairSourceMQInterface<FairSourceType, DataType>>()
        , fSource(nullptr)
        , fInput(nullptr)
        , fIndex(0)
        , fMaxIndex(-1)
        , fClassName("")
        , fBranchName("")
        , fSourceName("")
        , fRunAna(nullptr)
    {}

    FairSourceMQInterface(const FairSourceMQInterface&) = delete;
    FairSourceMQInterface operator=(const FairSourceMQInterface&) = delete;

    virtual ~FairSourceMQInterface()
    {
        delete fInput;
        fInput = nullptr;

        delete fSource;
        fSource = nullptr;

        delete fRunAna;
        fRunAna = nullptr;
    }

    int64_t GetNumberOfEvent() { return fMaxIndex; }

    void SetFileProperties(const std::string& filename, const std::string& branchname)
    {
        fSourceName = filename;
        fBranchName = branchname;
    }

    //______________________________________________________________________________
    // FairFileSource

    template<typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
    void InitSource()
    {
        fRunAna = new FairRunAna();
        fSource = new FairSourceType(fSourceName.c_str());
        fSource->Init();
        fSource->ActivateObject(reinterpret_cast<TObject**>(&fInput), fBranchName.c_str());
        //        fSource->ActivateObject(dynamic_cast<TObject*>(fData),fBranchName.c_str());
        fMaxIndex = fSource->CheckMaxEventNo();
    }

    template<typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
    void SetIndex(int64_t eventIdx)
    {
        fIndex = eventIdx;
    }

    template<typename T = FairSourceType, enable_if_match<T, FairFileSource> = 0>
    DataType_ptr GetOutData()
    {
        fSource->ReadEvent(fIndex);
        return fInput;
    }

    void GetOutData(DataType_ptr& data, int64_t evtIdx)
    {
        fSource->ReadEvent(evtIdx);
        data = fInput;
    }

    /*required for MQ*/
    void deserialize_impl(int64_t evtIdx) { fSource->ReadEvent(evtIdx); }

  protected:
    FairSourceType* fSource;
    DataType_ptr fInput;
    std::unique_ptr<DataType> fInput2;
    int64_t fIndex;
    int64_t fMaxIndex;
    std::string fClassName;
    std::string fBranchName;
    std::string fSourceName;
    FairRunAna* fRunAna;
};

#endif
