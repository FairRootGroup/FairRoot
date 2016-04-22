/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelDigiWriteToFile.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelDigiWriteToFile.h"

// Includes from base
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairLink.h"
#include "FairLogger.h"

// Includes from ROOT
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TGeoManager.h"

#include "PixelDigi.h"

#include <map>

using std::pair;
using std::map;



// -----   Default constructor   ------------------------------------------
PixelDigiWriteToFile::PixelDigiWriteToFile()
  : PixelDigiWriteToFile("Pixel DigiWriter", 0)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
PixelDigiWriteToFile::PixelDigiWriteToFile(Int_t iVerbose) 
  : PixelDigiWriteToFile("Pixel DigiWriter", iVerbose)
{
}
// -------------------------------------------------------------------------



// -----   Constructor with name   -----------------------------------------
PixelDigiWriteToFile::PixelDigiWriteToFile(const char* name, Int_t iVerbose) 
  : FairTask(name, iVerbose)
  , fDigis(NULL)
  , fOutputFileName("test.dat")
  , fOutputFiles()
  , fDivideLevel(0)
  , fRunId(0)
  , fMCEntryNo(0)
  , fPartNo(0)

{
  Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelDigiWriteToFile::~PixelDigiWriteToFile() { 
  Reset();
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void PixelDigiWriteToFile::Exec(Option_t* /*opt*/) {

  Reset();

  Int_t nofDigis = fDigis->GetEntriesFast();

  for ( Int_t ifile = 0 ; ifile < fNofOutputFiles ; ifile++ ) {
    fOutputFiles[ifile] << "EVENT BEGIN; RUNID = " << fRunId << "; MCENTRYNO = " << fMCEntryNo << "; PARTNO = " << ifile << ";" << std::endl;
  }
  
  for ( Int_t iDigi = 0 ; iDigi < nofDigis ; iDigi++ ) {
    PixelDigi* currentDigi = static_cast<PixelDigi*>(fDigis->At(iDigi));

    Int_t detId     = currentDigi->GetDetectorID();    
    Int_t feId      = currentDigi->GetFeID();
    Int_t col       = currentDigi->GetCol();
    Int_t row       = currentDigi->GetRow();
    Double_t charge = currentDigi->GetCharge();

    Int_t fileToSave = 0;
    if ( fDivideLevel == 1 ) {
      fileToSave = detId/256 - 1;
    }
    else if ( fDivideLevel == 2 ) {
      fileToSave = (detId/256 - 1)*4 + (detId%256 -1);
    }
    fOutputFiles[fileToSave] << detId << " " << feId << " " << col << " " << row << " " << charge << std::endl;
  }

  for ( Int_t ifile = 0 ; ifile < fNofOutputFiles ; ifile++ ) {
    fOutputFiles[ifile] << "EVENT END" << std::endl;
  }

  fMCEntryNo ++;
}
// -------------------------------------------------------------------------

// -----   Private method SetParContainers   -------------------------------
void PixelDigiWriteToFile::SetParContainers() {
}
// -------------------------------------------------------------------------

// -----   Private method Init   -------------------------------------------
InitStatus PixelDigiWriteToFile::Init() {

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) LOG(FATAL) << "No FairRootManager" << FairLogger::endl;
  fDigis = static_cast<TClonesArray*>(ioman->GetObject("PixelDigis"));

  if ( !fDigis ) 
    LOG(WARNING) << "PixelDigiWriteToFile::Init() No input PixelDigis array!" << FairLogger::endl;

  LOG(INFO) << "-I- " << fName.Data() << "::Init(). Initialization succesfull." << FairLogger::endl;

  fRunId = ioman->GetRunId();

  if      ( fDivideLevel == 0 ) {
    fNofOutputFiles =  1;
    fOutputFiles[0].open(fOutputFileName.Data(),std::fstream::out);
  }
  else {
    if ( fDivideLevel == 1 ) {
      fNofOutputFiles =  3; // 1 file per station (3 stations)
    }
    else if ( fDivideLevel == 2 ) {
      fNofOutputFiles = 12; // 1 file per sensor  (3 stations times 4 sensors)
    }
    else {
      LOG(FATAL) << "PixelDigiWriteToFile::Init(), fDivideLevel = " << fDivideLevel << " unknown, it has to be in the range <0,2>" << FairLogger::endl;
      return kFATAL;
    }
    for ( Int_t ifile = 0 ; ifile < fNofOutputFiles ; ifile++ ) {
      TString fileName = fOutputFileName;
      TString uniqFile = Form(".p%d.",ifile);
      fileName.Replace(fileName.Last('.'),1,uniqFile.Data());
      fOutputFiles[ifile].open(fileName.Data(),std::fstream::out);
    }
  }    
  
  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelDigiWriteToFile::ReInit() {
  FairRootManager* ioman = FairRootManager::Instance();

  if ( ! ioman ) Fatal("Init", "No FairRootManager");

  fRunId = ioman->GetRunId();
  fMCEntryNo = 0;
 
  return kSUCCESS;
}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelDigiWriteToFile::Reset() {
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelDigiWriteToFile::Finish() {
  for ( Int_t ifile = 0 ; ifile < fNofOutputFiles ; ifile++ ) {
    fOutputFiles[ifile].close();
  }
}
// -------------------------------------------------------------------------



ClassImp(PixelDigiWriteToFile)

