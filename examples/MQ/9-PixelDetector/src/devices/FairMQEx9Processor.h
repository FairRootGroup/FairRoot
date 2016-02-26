/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9PROCESSOR_H_
#define FAIRMQEXAMPLE9PROCESSOR_H_

#include <string>

#include "FairMQDevice.h"
#include "RootSerializer.h"
#include "TClonesArray.h"
#include "PixelFindHits.h"

class FairMQEx9Processor : public FairMQDevice
{
  public:
    enum
    {
        InputClassName = FairMQDevice::Last,
        Last
    };

    FairMQEx9Processor();
    virtual ~FairMQEx9Processor();

    void SetProperty(const int key, const std::string& value);
    std::string GetProperty(const int key, const std::string& default_ = "");
    void SetProperty(const int key, const int value);
    int GetProperty(const int key, const int default_ = 0);

  protected:

    virtual void Run();
    virtual void Init();



    TClonesArray* fOutput;
    std::string fTaskName;
    std::string fInputClassName;
    Int_t fDetID;
    Int_t fMCIndex;
    RootSerializer fSerializer;
    RootDeSerializer fDeSerializer;
    PixelFindHits* fHitFinder;
    
};

#endif /* FAIRMQEXAMPLE9PROCESSOR_H_ */