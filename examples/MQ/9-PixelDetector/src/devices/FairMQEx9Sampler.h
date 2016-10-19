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

#include <boost/thread.hpp>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQEx9Sampler : public FairMQDevice
{
  public:
    FairMQEx9Sampler();
    virtual ~FairMQEx9Sampler();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }
    
    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

    void SetSource(FairSource* tempSource) {fSource = tempSource;}

    void ListenForAcks();

    void SetOutputChannelName(std::string tstr) {fOutputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

 protected:
    virtual bool OnRun();
    virtual void PreRun();
    virtual void PostRun();
    virtual void InitTask();
    
 private: 
    std::string     fOutputChannelName;
    std::string     fAckChannelName;

    FairRunAna*     fRunAna;
    FairSource*     fSource;
    TObject*        fInputObjects[100];
    int             fNObjects;
    int64_t         fMaxIndex;

    int             fEventCounter;

    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;

    FairMQEx9Sampler(const FairMQEx9Sampler&);
    FairMQEx9Sampler& operator=(const FairMQEx9Sampler&);

    boost::thread* fAckListener;
};

#endif /* FAIRMQEX9SAMPLER_H_ */
