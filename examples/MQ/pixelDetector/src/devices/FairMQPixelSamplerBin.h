/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelSamplerBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELSAMPLERBIN_H_
#define FAIRMQPIXELSAMPLERBIN_H_

#include <string>
#include <thread>

#include "TClonesArray.h"

#include "FairFileSource.h"
#include "FairRunAna.h"

#include "FairMQDevice.h"

class FairMQPixelSamplerBin : public FairMQDevice
{
  public:
    FairMQPixelSamplerBin();
    virtual ~FairMQPixelSamplerBin();

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

    FairMQPixelSamplerBin(const FairMQPixelSamplerBin&);
    FairMQPixelSamplerBin& operator=(const FairMQPixelSamplerBin&);

    std::thread fAckListener;
};

#endif /* FAIRMQPIXELSAMPLER_H_ */
