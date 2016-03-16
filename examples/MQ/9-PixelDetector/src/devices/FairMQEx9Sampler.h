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
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9SAMPLER_H_
#define FAIRMQEX9SAMPLER_H_

#include <string>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQEx9Sampler : public FairMQDevice
{
  public:
    enum
    {
        InputFileName = FairMQDevice::Last,
        Last
    };

    FairMQEx9Sampler();
    virtual ~FairMQEx9Sampler();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }
    
    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

 protected:
    virtual void Run();
    virtual void InitTask();
    
 private: 
    FairRunAna*     fRunAna;
    FairFileSource* fSource;
    TObject*        fInputObjects[100];
    int             fNObjects;
    int64_t         fMaxIndex;
    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;
};

#endif /* FAIRMQEX9SAMPLER_H_ */
