#ifndef CBMPARIO_H
#define CBMPARIO_H

#include "TObject.h"
#include "TList.h"

class CbmDetParIo;
class CbmRtdbRun;

class CbmParIo : public TObject {
protected:
  TList* detParIoList;  // list of detector I/Os
  Bool_t autoWritable;  // flag indicating if automatic write is possible
public:
  CbmParIo();
  virtual ~CbmParIo();
  virtual CbmDetParIo* getDetParIo(Text_t*);
  virtual void setDetParIo(CbmDetParIo*);
  virtual void removeDetParIo(Text_t*);
  void setInputNumber(Int_t);
  virtual void close() {;}

  // creates input/output class for a special detector and stores pointer
  // used only for Oracle input/output
  // (code in  class OraIo)
  virtual void setDetParIo(Text_t*) {;}

  // prints information about input/output
  virtual void print() {;}

  // checks if the input/output is open
  virtual Bool_t check() { return kFALSE; }

  // reads versions of parameter containers for an event file
  virtual void readVersions(CbmRtdbRun*) {;}

  // sets global file pointer in ROOT if input/output is a ROOT-file
  // (code in CbmParRootFileIo)
  virtual void cd() {;}

  // set and get for flag autoWritable
  void setAutoWritable(Bool_t f=kTRUE) {autoWritable=f;}
  Bool_t isAutoWritable() {return autoWritable;}

  ClassDef(CbmParIo,0) // Base class for all parameter I/Os
};

#endif  /* !CBMPARIO_H */




