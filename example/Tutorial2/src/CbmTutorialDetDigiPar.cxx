// -------------------------------------------------------------------------
// -----                CbmTutorialDetDigiPar source file              -----
// -----                  Created 05/06/08  by F. Uhlig                -----
// -------------------------------------------------------------------------

#include "CbmTutorialDetDigiPar.h"

#include "CbmParamList.h"
#include "CbmDetParIo.h"
#include "CbmParIo.h"

#include "TString.h"
#include "TMath.h"

#include <iostream>

using std::cout;
using std::endl;

// -----   Standard constructor   ------------------------------------------
CbmTutorialDetDigiPar::CbmTutorialDetDigiPar(const char* name, 
					     const char* title,
					     const char* context)
  : CbmParGenericSet(name, title, context) {
  detName="TutorialDet";
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
CbmTutorialDetDigiPar::~CbmTutorialDetDigiPar() {
  clear();
}
// -------------------------------------------------------------------------


// -----   Public method clear   -------------------------------------------
void CbmTutorialDetDigiPar::clear() {
  status = kFALSE;
  resetInputVersions();
}
// -------------------------------------------------------------------------

// -----   Public method printParams ---------------------------------------
void CbmTutorialDetDigiPar::printparams() {
  
  cout <<"Print"<<endl;
  cout << "ftutdetdigiparstation: " << ftutdetdigiparstation << endl;
  Int_t size =  ftutdetdigiparsector.GetSize();
  cout <<"size: " << size << endl;
  for ( Int_t i=0; i< size; i++) {
    cout << i <<" :" << ftutdetdigiparsector.GetAt(i) << endl;
  }
  size =  ftutdetdigipar.GetSize();
  cout <<"size: " << size << endl;
  for ( Int_t i=0; i< size; i++) {
    cout << i <<" :" << ftutdetdigipar.GetAt(i) << endl;
  }
    
}
// -------------------------------------------------------------------------

void CbmTutorialDetDigiPar::putParams(CbmParamList* l) {
  //   print();
  cout << " I am in CbmTutorialDetDigiPar::putParams " << endl;
   if (!l) return;
   l->add("CbmTutorialDetDigiStations", ftutdetdigiparstation);
   l->add("CbmTutorialDetDigiSectorsPerStation", ftutdetdigiparsector);
   Int_t count_sectors = 0;
   for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
     count_sectors+=ftutdetdigiparsector[i];
   }
   Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
   cout << "Array Size: " << array_size << endl;
   Float_t zwischen[array_size];
   for ( Int_t i=0; i< array_size; i++) {
     zwischen[i] = ftutdetdigipar.GetAt(i);
   }
   l->addBinary("CbmTutorialDetDigiPar",zwischen,array_size);
}

//------------------------------------------------------

Bool_t CbmTutorialDetDigiPar::getParams(CbmParamList* l) {
  //print();
    cout << " I am in CbmTutorialDetDigiPar::getParams " << endl;

    if (!l) return kFALSE;
    if ( ! l->fill("CbmTutorialDetDigiStations", &ftutdetdigiparstation) ) return kFALSE;
    ftutdetdigiparsector.Set(ftutdetdigiparstation);

    if ( ! l->fill("CbmTutorialDetDigiSectorsPerStation", &ftutdetdigiparsector) ) return kFALSE;

    Int_t count_sectors = 0;
    for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
      count_sectors+=ftutdetdigiparsector[i];
    }
    cout << "Total number of sectors: " << count_sectors<<endl;

    Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
    cout << "Array Size: " << array_size << endl;

    Float_t zwischen[array_size];
    if (!(l->fillBinary("CbmTutorialDetDigiPar",zwischen,array_size))) {
      cout << "--W-- Could not initialize CbmTutorialDetDigiPar"<< endl;
      return kFALSE;
    }
    ftutdetdigipar.Set(array_size, zwischen);    
    return kTRUE;
}



ClassImp(CbmTutorialDetDigiPar)
