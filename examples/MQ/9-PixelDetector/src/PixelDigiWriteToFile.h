/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelWriteToFile.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIWRITETOFILE_H
#define PIXELDIGIWRITETOFILE_H 1

#include "FairTask.h"

#include "PixelDigi.h"

class TString;

#include <list>
#include <map>
#include <fstream>

class PixelDigiWriteToFile : public FairTask
{

 public:

  /** Default constructor **/
  PixelDigiWriteToFile();


  /** Standard constructor **/
  PixelDigiWriteToFile(Int_t iVerbose);


  /** Constructor with name **/
  PixelDigiWriteToFile(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelDigiWriteToFile();


  /** Execution **/
  virtual void Exec(Option_t* opt);


  void SetOutputFileName(TString tstr) {fOutputFileName = tstr;};

 private:

  TClonesArray*     fDigis;        /** Input array of PixelDigi **/

  TString  fOutputFileName;
  std::ofstream fOutputFile;  

  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelDigiWriteToFile(const PixelDigiWriteToFile&);
  PixelDigiWriteToFile& operator=(const PixelDigiWriteToFile&);

  ClassDef(PixelDigiWriteToFile,1);

};

#endif


