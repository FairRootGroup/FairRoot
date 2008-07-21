//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004

/////////////////////////////////////////////////////////////
//  CbmParIo
//
//  Base class for different parameter input/output sources:
//  Rootfiles, Asciifiles, Oracle
//  It contains a list of detector I/Os.
/////////////////////////////////////////////////////////////

#include "CbmParIo.h"

#include "CbmDetParIo.h"

ClassImp(CbmParIo)

CbmParIo::CbmParIo() {
  //default constructor creates an empty list of detector I/Os
  detParIoList=new TList();
  autoWritable=kTRUE;
}

CbmParIo::~CbmParIo() {
  // default destructor
  if(detParIoList){
    detParIoList->Delete();
    delete detParIoList;
    detParIoList=0;
  }
}

void CbmParIo::setDetParIo(CbmDetParIo* detParIo) {
  // stores pointer of the input/output class for a detector
  // used for I/O from ROOT file or Ascii file
  Text_t* detName=(char*)detParIo->GetName();
  if (!detParIoList->FindObject(detName)) detParIoList->Add(detParIo);
}

void CbmParIo::setInputNumber(Int_t num) {
  // sets in all detector I/Os the number of the input
  TIter next(detParIoList);
  CbmDetParIo* io;
  while ((io=(CbmDetParIo*)next())) {
    io->setInputNumber(num);
  }
} 

CbmDetParIo* CbmParIo::getDetParIo(Text_t* detName) {
  // returns pointer to input/output class for a detector
  return ((CbmDetParIo*)detParIoList->FindObject(detName));
}

void CbmParIo::removeDetParIo(Text_t* detName) {
  // removes input/output class for a detector
  TObject* p=detParIoList->FindObject(detName);
  if (p) {
    delete p;
    p=0;
  }
}
