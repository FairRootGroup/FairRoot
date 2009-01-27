//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004

///////////////////////////////////////////////////////////////////////////
//  FairParGenericSet
//
//  Base class for all generic-style parameter containers
//
//  The following functions must be implemented by the derived class:
//
//    void putParams(FairParamList*)    Fills all persistent data members into
//                                     the list for write.
//
//    Bool_t getParams(FairParamList*)  Fills all persistent data members from
//                                     the list after reading. The function
//                                     returns false, when a data member is
//                                     not in the list.
///////////////////////////////////////////////////////////////////////////


#include "FairParGenericSet.h"

#include "FairParamList.h"
#include "FairParIo.h"
#include "FairDetParIo.h"

#include <iostream>
//#include <iomanip>

using std::cout;

ClassImp(FairParGenericSet)

Bool_t FairParGenericSet::init(FairParIo* inp) {
  // intitializes the container from an input
  FairDetParIo* input=inp->getDetParIo("FairGenericParIo");
  if (input) return (input->init(this));
  return kFALSE;
}

Int_t FairParGenericSet::write(FairParIo* output) {
  // writes the container to an output
  FairDetParIo* out=output->getDetParIo("FairGenericParIo");
  if (out)  return out->write(this);
  return -1;
}

void FairParGenericSet::printParams() {
  // prints information about the container
  cout<<"---------------------------------------------"<<'\n';
  cout<<"-----  "<<GetName()<<"  -----"<<'\n';
  if (!paramContext.IsNull()) cout<<"--  Context/Purpose:  "<<paramContext<<'\n';
  if (!author.IsNull()) cout<<"--  Author:           "<<author<<'\n';
  if (!description.IsNull()) cout<<"--  Description:      "<<description<<'\n';
  cout<<"---------------------------------------------"<<'\n';
  FairParamList* condList = new FairParamList;
  putParams(condList);
  condList->print();
  delete condList;
} 
 
