#ifndef CBMGEOOLDASCIIIO_H
#define CBMGEOOLDASCIIIO_H

#include "FairGeoIo.h"

#include "TString.h"

#include <fstream>

class FairGeoNode;

/**
 * Class for geometry I/O from ASCII file in CBM format
 * @author Ilse koenig 
 */
class FairGeoOldAsciiIo: public FairGeoIo {
  TString  filename;
  TString  filedir;
  Bool_t   writable;
  fstream* file;
public:
  FairGeoOldAsciiIo();
  ~FairGeoOldAsciiIo();
  void setDirectory(const char* fDir) {filedir=fDir;}
  const char* getDirectory() {return filedir.Data();}
  const char* getFilename() {return filename.Data();}
  Bool_t open(const char*,const Text_t* status="in");
  Bool_t isOpen();
  Bool_t isWritable();
  void close();
  void print();
  Bool_t read(FairGeoMedia*) {return kFALSE;}
  Bool_t read(FairGeoSet*,FairGeoMedia*);
  Bool_t write(FairGeoMedia*) {return kFALSE;}
  Bool_t write(FairGeoSet* set) {return kFALSE;}
  Bool_t readGeomConfig(FairGeoInterface*) {return kFALSE;}
  Bool_t readDetectorSetup(FairGeoInterface*) {return kFALSE;}
  Bool_t setSimulRefRun(const char*) {return kTRUE;}
  Bool_t setHistoryDate(const char*) {return kTRUE;}
private:
  Bool_t calculateShapePoints(Double_t*,FairGeoNode*);
  FairGeoOldAsciiIo(const FairGeoOldAsciiIo &L);
  FairGeoOldAsciiIo& operator= (const FairGeoOldAsciiIo&) {return *this;}
  
  ClassDef(FairGeoOldAsciiIo,0) //
};

#endif  /* !CBMGEOOLDASCIIIO_H */
