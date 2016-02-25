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
void PixelDigiWriteToFile::Exec(Option_t* opt) {

  Reset();

  Int_t nofDigis = fDigis->GetEntriesFast();

  fOutputFile << "EVENT BEGIN" << std::endl;

  for ( Int_t iDigi = 0 ; iDigi < nofDigis ; iDigi++ ) {
    PixelDigi* currentDigi = (PixelDigi*)fDigis->At(iDigi);

    Int_t detId     = currentDigi->GetDetectorID();    
    Int_t feId      = currentDigi->GetFeID();
    Int_t col       = currentDigi->GetCol();
    Int_t row       = currentDigi->GetRow();
    Double_t charge = currentDigi->GetCharge();

    fOutputFile << detId << " " << feId << " " << col << " " << row << " " << charge << std::endl;
  }

  fOutputFile << "EVENT END" << std::endl;

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

  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  fDigis = (TClonesArray*) ioman->GetObject("PixelDigis");

  if ( !fDigis ) 
    LOG(WARNING) << "PixelDigiWriteToFile::Init() No input PixelDigis array!" << FairLogger::endl;

  LOG(INFO) << "-I- " << fName.Data() << "::Init(). Initialization succesfull." << FairLogger::endl;

  fOutputFile.open(fOutputFileName.Data(),std::fstream::out);

  fOutputFile << "RUNID " << ioman->GetRunId() << std::endl;


  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method ReInit   -----------------------------------------
InitStatus PixelDigiWriteToFile::ReInit() {

  return kSUCCESS;

}
// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void PixelDigiWriteToFile::Reset() {
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelDigiWriteToFile::Finish() {
  fOutputFile.close();
}
// -------------------------------------------------------------------------



ClassImp(PixelDigiWriteToFile)

