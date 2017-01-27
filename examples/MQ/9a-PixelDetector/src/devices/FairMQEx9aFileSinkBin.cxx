/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9aFileSinkBin.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQEx9aFileSinkBin.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

#include "PixelPayload.h"
#include "PixelHit.h"

using namespace std;

FairMQEx9aFileSinkBin::FairMQEx9aFileSinkBin()
  : FairMQDevice()
  , fInputChannelName("data-in")
  , fAckChannelName("")
  , fFileName()
  , fOutFile(NULL)
{
}

void FairMQEx9aFileSinkBin::Init()
{
  fFileName          = fConfig->GetValue<std::string>             ("file-name");
  fInputChannelName  = fConfig->GetValue<std::string>             ("in-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");

  LOG(INFO) << "SHOULD CREATE THE FILE AND TREE";

  fOutFile.open(fFileName,std::fstream::out|std::fstream::binary);
  
  OnData(fInputChannelName, &FairMQEx9aFileSinkBin::StoreData);
}

bool FairMQEx9aFileSinkBin::StoreData(FairMQParts& parts, int /*index*/)
{
  if ( parts.Size() == 0 ) return true; // probably impossible, but still check
  
  // the first part should be the event header
  PixelPayload::EventHeader* payloadE = static_cast<PixelPayload::EventHeader*>(parts.At(0)->GetData());

  LOG(TRACE) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " << payloadE->fPartNo << ")";
  
  // the second part should be the array of PixelPayload::Hit
  PixelPayload::Hit* payloadH = static_cast<PixelPayload::Hit*>(parts.At(1)->GetData());
  int hitArraySize = parts.At(1)->GetSize();
  int nofHits      = hitArraySize / sizeof(PixelPayload::Hit);

  fOutFile.write((char*)&(payloadE->fRunId)    , sizeof(payloadE->fRunId));
  fOutFile.write((char*)&(payloadE->fMCEntryNo), sizeof(payloadE->fMCEntryNo));
  fOutFile.write((char*)&(payloadE->fPartNo)   , sizeof(payloadE->fPartNo));
  fOutFile.write((char*)&nofHits               , sizeof(nofHits));
  
  float posX, posY, posZ, dposX, dposY, dposZ;
  for ( int ihit = 0 ; ihit < nofHits ; ihit++ )
    {
      posX = (float)payloadH->posX;
      posY = (float)payloadH->posY;
      posZ = (float)payloadH->posZ;
      dposX = (float)payloadH->dposX;
      dposY = (float)payloadH->dposY;
      dposZ = (float)payloadH->dposZ;
      fOutFile.write( reinterpret_cast<char*>(&(payloadH->fDetectorID)), sizeof(payloadH->fDetectorID));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->posX))       , sizeof(payloadH->posX       ));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->posY))       , sizeof(payloadH->posY       ));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->posZ))       , sizeof(payloadH->posZ       ));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->dposX))      , sizeof(payloadH->dposX      ));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->dposY))      , sizeof(payloadH->dposY      ));
      // fOutFile.write( reinterpret_cast<char*>(&(payloadH->dposZ))      , sizeof(payloadH->dposZ      ));
      fOutFile.write( reinterpret_cast<char*>(&posX)       , sizeof(posX       ));
      fOutFile.write( reinterpret_cast<char*>(&posY)       , sizeof(posY       ));
      fOutFile.write( reinterpret_cast<char*>(&posZ)       , sizeof(posZ       ));
      fOutFile.write( reinterpret_cast<char*>(&dposX)      , sizeof(dposX      ));
      fOutFile.write( reinterpret_cast<char*>(&dposY)      , sizeof(dposY      ));
      fOutFile.write( reinterpret_cast<char*>(&dposZ)      , sizeof(dposZ      ));
    }
  
  if ( fAckChannelName != "" ) {
    unique_ptr<FairMQMessage> msg(NewMessage());
    Send(msg, fAckChannelName);
  }
  return true;
}

FairMQEx9aFileSinkBin::~FairMQEx9aFileSinkBin()
{ 
  fOutFile.close();
}
