/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9SamplerBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9SAMPLERBIN_H_
#define FAIRMQEX9SAMPLERBIN_H_

#include <string>
#include <thread>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQEx9SamplerBin : public FairMQDevice
{
  public:
    FairMQEx9SamplerBin();
    virtual ~FairMQEx9SamplerBin();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }

    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

    void ListenForAcks();

    void SetOutputChannelName(std::string tstr) {fOutputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

  protected:
    virtual bool ConditionalRun();
    virtual void PreRun();
    virtual void PostRun();
    virtual void InitTask();

  private:
    std::string     fOutputChannelName;
    std::string     fAckChannelName;

    FairRunAna*     fRunAna;
    FairFileSource* fSource;
    TObject*        fInputObjects[100];
    int             fNObjects;
    int64_t         fMaxIndex;

    int             fEventCounter;

    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;

    FairMQEx9SamplerBin(const FairMQEx9SamplerBin&);
    FairMQEx9SamplerBin& operator=(const FairMQEx9SamplerBin&);

    std::thread fAckListener;
};

#endif /* FAIRMQEX9SAMPLER_H_ */
