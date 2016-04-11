/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9Sampler.h
 *
 * @since 2016-03-18
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9SAMPLERASCII_H_
#define FAIRMQEX9SAMPLERASCII_H_

#include <string>

#include "TClonesArray.h"

#include "PixelDigiSource.h"
#include "PixelEventHeader.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQEx9SamplerAscii : public FairMQDevice
{
  public:
    enum
    {
        InputFileName = FairMQDevice::Last,
        Last
    };

    FairMQEx9SamplerAscii();
    virtual ~FairMQEx9SamplerAscii();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }
    
    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

 protected:
    virtual void Run();
    virtual void InitTask();
    
 private: 
    FairRunAna*       fRunAna;
    PixelDigiSource*  fSource;
    TObject*          fInputObjects[100];
    int               fNObjects;
    int64_t           fMaxIndex;
    PixelEventHeader* fEventHeader;
    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;
};

#endif /* FAIRMQEX9SAMPLERASCII_H_ */
