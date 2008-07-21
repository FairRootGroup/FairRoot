//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////
//  CbmParGenericSet
//
//  Base class for all generic-style parameter containers
//
//  The following functions must be implemented by the derived class:
//
//    void putParams(CbmParamList*)    Fills all persistent data members into
//                                     the list for write.
//
//    Bool_t getParams(CbmParamList*)  Fills all persistent data members from
//                                     the list after reading. The function
//                                     returns false, when a data member is
//                                     not in the list.
///////////////////////////////////////////////////////////////////////////


#include "CbmParGenericSet.h"

#include "CbmParamList.h"
#include "CbmParIo.h"
#include "CbmDetParIo.h"

#include <iostream>
//#include <iomanip>

using std::cout;

ClassImp(CbmParGenericSet)

Bool_t CbmParGenericSet::init(CbmParIo* inp) {
  // intitializes the container from an input
  CbmDetParIo* input=inp->getDetParIo("CbmGenericParIo");
  if (input) return (input->init(this));
  return kFALSE;
}

Int_t CbmParGenericSet::write(CbmParIo* output) {
  // writes the container to an output
  CbmDetParIo* out=output->getDetParIo("CbmGenericParIo");
  if (out)  return out->write(this);
  return -1;
}

void CbmParGenericSet::printParams() {
  // prints information about the container
  cout<<"---------------------------------------------"<<'\n';
  cout<<"-----  "<<GetName()<<"  -----"<<'\n';
  if (!paramContext.IsNull()) cout<<"--  Context/Purpose:  "<<paramContext<<'\n';
  if (!author.IsNull()) cout<<"--  Author:           "<<author<<'\n';
  if (!description.IsNull()) cout<<"--  Description:      "<<description<<'\n';
  cout<<"---------------------------------------------"<<'\n';
  CbmParamList* condList = new CbmParamList;
  putParams(condList);
  condList->print();
  delete condList;
} 
 
