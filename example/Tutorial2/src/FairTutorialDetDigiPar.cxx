// -------------------------------------------------------------------------
// -----                FairTutorialDetDigiPar source file              -----
// -----                  Created 05/06/08  by F. Uhlig                -----
// -------------------------------------------------------------------------

#include "FairTutorialDetDigiPar.h"

#include "FairParamList.h"
#include "FairDetParIo.h"
#include "FairParIo.h"

#include "TString.h"
#include "TMath.h"

#include <iostream>

using std::cout;
using std::endl;

// -----   Standard constructor   ------------------------------------------
FairTutorialDetDigiPar::FairTutorialDetDigiPar(const char* name,
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
FairTutorialDetDigiPar::~FairTutorialDetDigiPar()
{
  clear();

}
// -------------------------------------------------------------------------


// -----   Public method clear   -------------------------------------------
void FairTutorialDetDigiPar::clear()
{
  status = kFALSE;
  resetInputVersions();
}
// -------------------------------------------------------------------------

// -----   Public method printParams ---------------------------------------
void FairTutorialDetDigiPar::printparams()
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

void FairTutorialDetDigiPar::putParams(FairParamList* l)
{
  //   print();
  cout << " I am in FairTutorialDetDigiPar::putParams " << endl;
  if (!l) { return; }
  l->add("FairTutorialDetDigiStations", ftutdetdigiparstation);
  l->add("FairTutorialDetDigiSectorsPerStation", ftutdetdigiparsector);
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
  l->add("FairTutorialDetDigiPar",*ftutdetdigipar);
}

//------------------------------------------------------

Bool_t FairTutorialDetDigiPar::getParams(FairParamList* l)
{
  //print();

  cout << " I am in FairTutorialDetDigiPar::getParams " << endl;

  if (!l) { return kFALSE; }
  if ( ! l->fill("FairTutorialDetDigiStations", &ftutdetdigiparstation) ) { return kFALSE; }
  ftutdetdigiparsector.Set(ftutdetdigiparstation);

  if ( ! l->fill("FairTutorialDetDigiSectorsPerStation", &ftutdetdigiparsector) ) { return kFALSE; }

  Int_t count_sectors = 0;
  for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
    count_sectors+=ftutdetdigiparsector[i];
  }
  cout << "Total number of sectors: " << count_sectors<<endl;

  Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
  cout << "Array Size: " << array_size << endl;
  ftutdetdigipar->Set(array_size);
  //Float_t zwischen[array_size];
  if (!(l->fill("FairTutorialDetDigiPar",ftutdetdigipar))) {
    cout << "--W-- Could not initialize FairTutorialDetDigiPar"<< endl;
    return kFALSE;
  }
  //ftutdetdigipar.Set(array_size, zwischen);
  return kTRUE;
}



ClassImp(FairTutorialDetDigiPar)
