/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairTutorialDet2DigiPar source file              -----
// -----                  Created 05/06/08  by F. Uhlig                -----
// -------------------------------------------------------------------------

#include "FairTutorialDet2DigiPar.h"

#include "FairParamList.h"
#include "FairDetParIo.h"
#include "FairParIo.h"

#include "TString.h"
#include "TMath.h"

#include <iostream>

using std::cout;
using std::endl;

// -----   Standard constructor   ------------------------------------------
FairTutorialDet2DigiPar::FairTutorialDet2DigiPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name, title, context),
    ftutdetdigipar(new TArrayF(10)),
    ftutdetdigiparsector(),
    ftutdetdigiparstation(-1)
{
  detName="TutorialDet";
  //  ftutdetdigipar= new TArrayF(10);
  //ftutdetdigipar= new TArrayF(10);
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairTutorialDet2DigiPar::~FairTutorialDet2DigiPar()
{
  clear();

}
// -------------------------------------------------------------------------


// -----   Public method clear   -------------------------------------------
void FairTutorialDet2DigiPar::clear()
{
  status = kFALSE;
  resetInputVersions();
}
// -------------------------------------------------------------------------

// -----   Public method printParams ---------------------------------------
void FairTutorialDet2DigiPar::printparams()
{

  cout <<"Print"<<endl;
  cout << "ftutdetdigiparstation: " << ftutdetdigiparstation << endl;
  Int_t size =  ftutdetdigiparsector.GetSize();
  cout <<"size: " << size << endl;
  for ( Int_t i=0; i< size; i++) {
    cout << i <<" :" << ftutdetdigiparsector.GetAt(i) << endl;
  }
  size =  ftutdetdigipar->GetSize();
  cout <<"size: " << size << endl;
  for ( Int_t i=0; i< size; i++) {
    cout << i <<" :" << ftutdetdigipar->GetAt(i) << endl;
  }

}
// -------------------------------------------------------------------------

void FairTutorialDet2DigiPar::putParams(FairParamList* l)
{
  //   print();
  cout << " I am in FairTutorialDet2DigiPar::putParams " << endl;
  if (!l) { return; }
  l->add("FairTutorialDet2DigiStations", ftutdetdigiparstation);
  l->add("FairTutorialDet2DigiSectorsPerStation", ftutdetdigiparsector);
  Int_t count_sectors = 0;
  for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
    count_sectors+=ftutdetdigiparsector[i];
  }
  Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
  cout << "Array Size: " << array_size << endl;
  /*   Float_t zwischen[array_size];
     for ( Int_t i=0; i< array_size; i++) {
       zwischen[i] = ftutdetdigipar.GetAt(i);
     }
   */
  ftutdetdigipar->Set(array_size);
  l->add("FairTutorialDet2DigiPar",*ftutdetdigipar);
}

//------------------------------------------------------

Bool_t FairTutorialDet2DigiPar::getParams(FairParamList* l)
{
  //print();

  cout << " I am in FairTutorialDet2DigiPar::getParams " << endl;

  if (!l) { return kFALSE; }
  if ( ! l->fill("FairTutorialDet2DigiStations", &ftutdetdigiparstation) ) { return kFALSE; }
  ftutdetdigiparsector.Set(ftutdetdigiparstation);

  if ( ! l->fill("FairTutorialDet2DigiSectorsPerStation", &ftutdetdigiparsector) ) { return kFALSE; }

  Int_t count_sectors = 0;
  for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
    count_sectors+=ftutdetdigiparsector[i];
  }
  cout << "Total number of sectors: " << count_sectors<<endl;

  Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
  cout << "Array Size: " << array_size << endl;
  ftutdetdigipar->Set(array_size);
  //Float_t zwischen[array_size];
  if (!(l->fill("FairTutorialDet2DigiPar",ftutdetdigipar))) {
    cout << "--W-- Could not initialize FairTutorialDet2DigiPar"<< endl;
    return kFALSE;
  }
  //ftutdetdigipar.Set(array_size, zwischen);
  return kTRUE;
}



ClassImp(FairTutorialDet2DigiPar)
