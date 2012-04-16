//*-- AUTHOR : Ilse Koenig
//*-- Created : 21/10/2004
//*-- Modified: 21/06/2005  Denis bertini

//////////////////////////////////////////////////////////////////////////////
// FairParRootFileIo
//
// Interface class for parameter I/O from/to ROOT file
// derived from interface base class FairParIo.
//
// It contains a pointer to the "connection class" of type FairParRootFile
// inherited from TFile.  FairParRootFile contains an object of type FairRtdbRun
// which holds the list of container versions for an event file.
//
// It contains also a list of detector interface classes all having the common
// base type FairDetParRootFileIo. Every detector has its own interface class.
//////////////////////////////////////////////////////////////////////////////


#include "FairParRootFileIo.h"

#include "FairDetParIo.h"
#include "FairRuntimeDb.h"
#include "FairRtdbRun.h"

//#include "TDirectory.h"
//#include "TROOT.h"

#include <TObjString.h>
#include <TFileMerger.h>

//#include <fstream>
//#include "stdio.h"
#include <iostream>
//#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;

ClassImp(FairParRootFile)
ClassImp(FairParRootFileIo)

//--------------------------------------------------------------------
FairParRootFile::FairParRootFile(const Text_t* fname, Option_t* option,
                                 const Text_t* ftitle, Int_t compress)
  :TNamed(fname,  ftitle),
   run(NULL),
   RootFile(new TFile(fname,option,ftitle,compress))
{
//              : TFile(fname,option,ftitle,compress) {
  // constructor opens a ROOT file
  //  RootFile=new TFile(fname,option,ftitle,compress);
  //run=0;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFile::FairParRootFile(TFile* f)
  :TNamed(f->GetName(), f->GetTitle()),
   run(NULL),
   RootFile(f)
{
//  :TFile(f->GetName(),"UPDATE"){
  // constructor opens a ROOT file
  //RootFile=new TFile(f->GetName(),"UPDATE");
  //  RootFile=f;
  //  run=0;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFile::~FairParRootFile()
{
  // destructor
  if (run) {
    delete run;
  }
  run=0;
  //TODO: What about the file? Should it be closed or not
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void FairParRootFile::readVersions(FairRtdbRun* currentRun)
{
  // finds the current run containing the parameter container versions
  // in the ROOT file
  if (run) {
    delete run;
  }
  run=(FairRtdbRun*)RootFile->Get(((char*)currentRun->GetName()));
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFileIo::FairParRootFileIo()
  :FairParIo(),
   file(NULL),
   fMerging(kFALSE)
{
  // constructor
  //  file=0;
  //  fMerging=kFALSE;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFileIo::FairParRootFileIo(Bool_t merged)
  :FairParIo(),
   file(NULL),
   fMerging(merged)
{
  // constructor
  //  file=0;
  //  fMerging=merged;

}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFileIo::~FairParRootFileIo()
{
  // destructor closes an open file
  close();
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Bool_t FairParRootFileIo::open(const Text_t* fname, Option_t* option,
                               const Text_t* ftitle, Int_t compress)
{
  // It opens a ROOT file (default option "READ"). An open file will be closed.
  // The detector I/Os for all detectors defined in the setup are activated.

  //DB, lock file for NFS in case of mulitple access
  //gDirectory->ReadKeys();
  close();
  if (fMerging ) {
    // used test merging
    fstream* f = new fstream(fname);
    if (f->good()) {
      // check if file already exists
      option = "UPDATE";
    } else {
      // if file doesn't exist recreate option is used
      option = "RECREATE";
    }
    f->close();
    delete f;
  }

  file=new FairParRootFile(fname,option,ftitle,compress);

  if (file && file->IsOpen()) {
    filename = fname;
    FairRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  cerr << "-E- Could not open input file " << fname << endl;
  Fatal("open","Could not open input file");
  return kFALSE;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Bool_t FairParRootFileIo::open(const TList* fnamelist, Option_t* option,
                               const Text_t* ftitle, Int_t compress)
{
  TObjString* string;
  TListIter myIter(fnamelist);
  TString newParFile = "";


  TFileMerger* merger = new TFileMerger();

  Int_t nofFiles = 0;
  while ((string = (TObjString*)myIter.Next())) {
    merger->AddFile(string->GetString().Data());

    if ( nofFiles == 0 ) {
      newParFile = string->GetString();
      TDatime currentDate;
      newParFile.Replace(newParFile.Last('/')+1,
                         newParFile.Length(),"");
      newParFile.Append(Form("allParams_%d_%d.root",
                             currentDate.GetDate(),
                             currentDate.GetTime()));
      merger->OutputFile(newParFile.Data());
    }
    nofFiles++;
  }
  merger->Merge();

  std::cout << "**** merged file = \"" << newParFile.Data() << "\"" << std::endl;

  return this->open(newParFile,option,ftitle,compress);
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
Bool_t FairParRootFileIo::open(TFile* f)
{
  // It opens a ROOT file (default option "READ"). An open file will be closed.
  // The detector I/Os for all detectors defined in the setup are activated.
//  close();
  file=new FairParRootFile(f);
  if (file && file->IsOpen()) {
    filename = file->GetName();
    FairRuntimeDb::instance()->activateParIo(this);
    return kTRUE;
  }
  return kFALSE;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void FairParRootFileIo::close()
{
  // closes an open ROOT file and deletes the detector I/Os
  if (file) {
    file->Close();
    delete file;
    file=0;
  }
  if (detParIoList) {
    detParIoList->Delete();
  }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void FairParRootFileIo::print()
{
  // prints the content of a open ROOT file and the list of detector I/Os
  if (file) {
    file->ls();
    TIter next(detParIoList);
    FairDetParIo* io;
    cout<<"Root file I/O "<<file->GetName()<<" is open\n";
    cout<<"detector I/Os: ";
    while ((io=(FairDetParIo*)next())) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  } else {
    cout<<"No ROOT file open\n";
  }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
FairParRootFile* FairParRootFileIo::getParRootFile()
{
  // returns a pointer to the current ROOT file
  return file;
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
void FairParRootFileIo::readVersions(FairRtdbRun* currentRun)
{
  // reads the parameter container versions for the current run from
  // the ROOT file
  if (file) {
    file->readVersions(currentRun);
  }
}
//--------------------------------------------------------------------

//--------------------------------------------------------------------
TList* FairParRootFileIo::getKeys()
{
  // returns the list of keys found in the ROOT file
  if (file) {
    return file->GetListOfKeys();
  }
  return 0;
}
//--------------------------------------------------------------------
