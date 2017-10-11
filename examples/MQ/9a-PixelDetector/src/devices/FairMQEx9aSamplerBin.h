/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9aSamplerBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9aSAMPLERBIN_H_
#define FAIRMQEX9aSAMPLERBIN_H_

#include <string>
#include <thread>
#include <fstream>

#include "TBranch.h"
#include "TChain.h"

#include "FairMQDevice.h"

#include "PixelPayload.h"

class FairMQEx9aSamplerBin : public FairMQDevice
{
  public:
    FairMQEx9aSamplerBin();
    virtual ~FairMQEx9aSamplerBin();

    void AddInputFileName  (std::string tempString) { fFileNames.push_back(tempString); }

    void SetMaxIndex(int64_t tempInt) { fMaxIndex = tempInt; }

    void ListenForAcks();

    void SetOutputChannelName(std::string tstr) { fOutputChannelName = tstr; }
    void SetAckChannelName(std::string tstr) { fAckChannelName = tstr; }

    void SetAggregateFactor(int nal) { fAggregateLevel = nal; }

  protected:
    virtual bool ConditionalRun();
    virtual void PreRun();
    virtual void PostRun();
    virtual void InitTask();

    bool ReadBinFile();
    bool ReadRootFile();

  private:
    std::string     fOutputChannelName;
    std::string     fAckChannelName;

    std::vector<std::string>     fFileNames;
    std::ifstream   fInputFile;
    int             fCurrentFile;

    TChain                          *fInputChain;
    PixelPayload::EventHeader       *fEventHeader;
    TBranch                         *fDigiBranch;
    std::vector<PixelPayload::Digi> *fDigiArray;

    int             fAggregateLevel;

    int64_t         fMaxIndex;

    int             fEventCounter;
    int             fNofRecAcks;

    bool            fReadingRootFiles;

    FairMQEx9aSamplerBin(const FairMQEx9aSamplerBin&);
    FairMQEx9aSamplerBin& operator=(const FairMQEx9aSamplerBin&);

    std::thread* fAckListener;
};

#endif /* FAIRMQEX9aSAMPLER_H_ */
