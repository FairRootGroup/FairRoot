/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSink.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXELFILESINK_H_
#define FAIRMQPIXELFILESINK_H_

#include <FairMQDevice.h>
#include <string>

class TFile;
class TObject;
class TTree;

class FairMQPixelFileSink : public FairMQDevice
{
  public:
    FairMQPixelFileSink();
    virtual ~FairMQPixelFileSink();

    void SetOutputFileName(const std::string& tempString) { fFileName = tempString; }
    std::string GetOutputFileName() { return fFileName; }

    void SetInputChannelName(const std::string& tstr) { fInputChannelName = tstr; }
    void SetAckChannelName(const std::string& tstr) { fAckChannelName = tstr; }

  protected:
    bool StoreData(FairMQParts&, int);
    void InitTask() override;
    void ResetTask() override;

  private:
    std::string fInputChannelName;
    std::string fAckChannelName;

    std::string fFileName;
    std::string fTreeName;

    std::string fFileOption;
    bool fFlowMode;
    bool fWrite;

    TFile* fOutFile;
    TTree* fTree;
    unsigned int fNObjects;
    TObject** fOutputObjects;

    FairMQPixelFileSink(const FairMQPixelFileSink&);
    FairMQPixelFileSink& operator=(const FairMQPixelFileSink&);
};

#endif /* FAIRMQPIXELFILESINK_H_ */
