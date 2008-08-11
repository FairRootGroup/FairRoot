#ifndef CBMPARROOTFILEIO_H
#define CBMPARROOTFILEIO_H

#include "CbmParIo.h"

#include "TNamed.h"
#include "TFile.h"
#include "TList.h"

class CbmRtdbRun;

class CbmParRootFile : public TNamed{
public:
  CbmRtdbRun* run;     //! pointer to current run in ROOT file
  CbmParRootFile(const Text_t* fname, Option_t* option="READ",
               const Text_t* ftitle="",Int_t compress=1);
  CbmParRootFile(TFile *f);	       
  ~CbmParRootFile();
  CbmRtdbRun* getRun() {return run;}
  void readVersions(CbmRtdbRun*);
  
  Bool_t IsOpen(){return RootFile->IsOpen();}
  void   cd() {RootFile->cd();}
  Bool_t IsWritable(){return RootFile->IsWritable();}

  TKey *GetKey(Text_t *t){ return RootFile->GetKey(t);}
  TList *GetListOfKeys(){ return RootFile->GetListOfKeys();} 
  void Close(){RootFile->Close();}
  
protected:
  TFile* RootFile;
  
  ClassDef(CbmParRootFile,0) // ROOT file for Parameter I/O 

};


class CbmParRootFileIo : public CbmParIo {
protected:
  CbmParRootFile* file;  // pointer to ROOT file
  Bool_t fMerging;
public:
   CbmParRootFileIo();
   CbmParRootFileIo(Bool_t merged);
  ~CbmParRootFileIo();
  Bool_t open(const Text_t* fname, Option_t* option="READ",
              const Text_t* ftitle="",Int_t compress=1);
  void close();
  void print();
  CbmParRootFile* getParRootFile();
  void readVersions(CbmRtdbRun*);
  TList* getKeys();
  Bool_t check() {
    // returns kTRUE if file is open
    if (file) return file->IsOpen();
    else return kFALSE;
  }
  void cd() {
    // sets the global ROOT file pointer gFile
    if (file) file->cd();
  }
  /**
  Open an existing root file for IO
  */
  Bool_t open(TFile *f);
  void setMerging( Bool_t io ) { fMerging=io;}
  ClassDef(CbmParRootFileIo,0) // Parameter I/O from ROOT files
};

#endif  /* !CBMPARROOTFILEIO_H */

