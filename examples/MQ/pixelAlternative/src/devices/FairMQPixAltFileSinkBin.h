/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixAltFileSinkBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQPIXALTFILESINKBIN_H_
#define FAIRMQPIXALTFILESINKBIN_H_

#include <FairMQDevice.h>  // for FairMQDevice
#include <fstream>         // for string, ofstream
#include <string>

class FairMQParts;

class FairMQPixAltFileSinkBin : public FairMQDevice
{
  public:
    FairMQPixAltFileSinkBin();
    virtual ~FairMQPixAltFileSinkBin();

    void SetOutputFileName(const std::string& tempString) { fFileName = tempString; }
    std::string GetOutputFileName() { return fFileName; }

    void SetInputChannelName(const std::string& tstr) { fInputChannelName = tstr; }
    void SetAckChannelName(const std::string& tstr) { fAckChannelName = tstr; }

  protected:
    bool StoreData(FairMQParts&, int);
    virtual void Init();

  private:
    std::string fInputChannelName;
    std::string fAckChannelName;

    std::string fFileName;

    std::ofstream fOutFile;

    FairMQPixAltFileSinkBin(const FairMQPixAltFileSinkBin&);
    FairMQPixAltFileSinkBin& operator=(const FairMQPixAltFileSinkBin&);
};

#endif /* FAIRMQPIXALTFILESINKBIN_H_ */
