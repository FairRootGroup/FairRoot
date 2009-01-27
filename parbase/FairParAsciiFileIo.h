#ifndef FAIRPARASCIFILEIIO_H
#define FAIRPARASCIFILEIIO_H

#include "FairParIo.h"

//#include "TList.h"

#include <fstream>

class FairParAsciiFileIo : public FairParIo {
protected:
  fstream* file;      // pointer to a file
  TString  filename;  // name of the file
public:
  FairParAsciiFileIo();

  // default destructor closes an open file and deletes list of I/Os
  ~FairParAsciiFileIo();

  // opens file
  // if a file is already open, this file will be closed
  // activates detector I/Os
  Bool_t open(const Text_t* fname, const Text_t* status="in");

  // closes file
  void close();

  // returns kTRUE if file is open
  Bool_t check() {
    if (file) return (file->rdbuf()->is_open()==1);
    else return kFALSE;
  }
   
  // prints information about the file and the detector I/Os
  void print();

  // returns the filename
  const char* getFilename() {return filename.Data();}

  fstream* getFile();

  ClassDef(FairParAsciiFileIo,0) // Parameter I/O from ASCII files
};

#endif  /* !FAIRPARASCIIFILEIO_H */

