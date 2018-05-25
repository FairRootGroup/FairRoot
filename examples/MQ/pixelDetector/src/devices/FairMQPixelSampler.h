/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelSampler.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELSAMPLER_H_
#define FAIRMQPIXELSAMPLER_H_

#include <string>
#include <thread>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQPixelSampler : public FairMQDevice
{
  public:
    FairMQPixelSampler();
    virtual ~FairMQPixelSampler();

    void AddInputFileName  (std::string tempString) { fFileNames  .push_back(tempString); }
    void AddInputBranchName(std::string tempString) { fBranchNames.push_back(tempString); }
    
    void SetMaxIndex(int64_t tempInt) {fMaxIndex=tempInt;}

    void SetSource(FairSource* tempSource) {fSource = tempSource;}

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
    FairSource*     fSource;
    TObject*        fInputObjects[100];
    int             fNObjects;
    int64_t         fMaxIndex;

    int             fEventCounter;

    std::vector<std::string>     fBranchNames;
    std::vector<std::string>     fFileNames;

    FairMQPixelSampler(const FairMQPixelSampler&);
    FairMQPixelSampler& operator=(const FairMQPixelSampler&);

    std::thread fAckListener;
};

#endif /* FAIRMQPIXELSAMPLER_H_ */
