#ifndef CBMGEOOLDASCIIIO_H
#define CBMGEOOLDASCIIIO_H

#include "CbmGeoIo.h"

#include "TString.h"

#include <fstream>

class CbmGeoNode;

/**
 * Class for geometry I/O from ASCII file in CBM format
 * @author Ilse koenig 
 */
class CbmGeoOldAsciiIo: public CbmGeoIo {
  TString  filename;
  TString  filedir;
  Bool_t   writable;
  fstream* file;
public:
  CbmGeoOldAsciiIo();
  ~CbmGeoOldAsciiIo();
  void setDirectory(const char* fDir) {filedir=fDir;}
  const char* getDirectory() {return filedir.Data();}
  const char* getFilename() {return filename.Data();}
  Bool_t open(const char*,const Text_t* status="in");
  Bool_t isOpen();
  Bool_t isWritable();
  void close();
  void print();
  Bool_t read(CbmGeoMedia*) {return kFALSE;}
  Bool_t read(CbmGeoSet*,CbmGeoMedia*);
  Bool_t write(CbmGeoMedia*) {return kFALSE;}
  Bool_t write(CbmGeoSet* set) {return kFALSE;}
  Bool_t readGeomConfig(CbmGeoInterface*) {return kFALSE;}
  Bool_t readDetectorSetup(CbmGeoInterface*) {return kFALSE;}
  Bool_t setSimulRefRun(const char*) {return kTRUE;}
  Bool_t setHistoryDate(const char*) {return kTRUE;}
private:
  Bool_t calculateShapePoints(Double_t*,CbmGeoNode*);
  CbmGeoOldAsciiIo(const CbmGeoOldAsciiIo &L);
  CbmGeoOldAsciiIo& operator= (const CbmGeoOldAsciiIo&) {return *this;}
  
  ClassDef(CbmGeoOldAsciiIo,0) //
};

#endif  /* !CBMGEOOLDASCIIIO_H */
