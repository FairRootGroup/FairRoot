/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9aFileSinkBin.h
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#ifndef FAIRMQEX9aFILESINKBIN_H_
#define FAIRMQEX9aFILESINKBIN_H_

#include <fstream>

#include "FairMQDevice.h"

class FairMQEx9aFileSinkBin : public FairMQDevice
{
  public:
    FairMQEx9aFileSinkBin();
    virtual ~FairMQEx9aFileSinkBin();

    void SetOutputFileName(std::string tempString) { fFileName = tempString; }
    std::string GetOutputFileName () { return fFileName;}

    void SetInputChannelName (std::string tstr) {fInputChannelName = tstr;}
    void SetAckChannelName(std::string tstr) {fAckChannelName = tstr;}

  protected:
    bool StoreData(FairMQParts&, int);
    virtual void Init();

 private:
    std::string     fInputChannelName;
    std::string     fAckChannelName;

    std::string fFileName;

    std::ofstream   fOutFile;

    FairMQEx9aFileSinkBin(const FairMQEx9aFileSinkBin&);
    FairMQEx9aFileSinkBin& operator=(const FairMQEx9aFileSinkBin&);
};

#endif /* FAIRMQEX9aFILESINKBIN_H_ */
