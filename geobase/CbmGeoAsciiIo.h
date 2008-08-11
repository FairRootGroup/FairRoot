#ifndef CBMGEOASCIIIO_H
#define CBMGEOASCIIIO_H

#include "CbmGeoIo.h"

#include "TString.h"

#include <fstream>
//#include <iomanip>

class CbmGeoSet;
class CbmGeoMedia;
class CbmGeoInterface;

/**
 * Class for geometry I/O from ASCII file
 * @author Ilse Koenig 
 */
class CbmGeoAsciiIo: public CbmGeoIo {
  TString  filename;
  TString  filedir;
  Bool_t   writable;
  fstream* file;
public:
  CbmGeoAsciiIo();
  virtual ~CbmGeoAsciiIo();
  void setDirectory(const char* fDir) {filedir=fDir;}
  const char* getDirectory() {return filedir.Data();}
  const char* getFilename() {return filename.Data();}
  Bool_t open(const char*,const Text_t* status="in");
  Bool_t isOpen();
  Bool_t isWritable();
  void close();
  void print();
  Bool_t read(CbmGeoMedia*);
  Bool_t read(CbmGeoSet*,CbmGeoMedia*);
  Bool_t write(CbmGeoMedia*);
  Bool_t write(CbmGeoSet* set);
  Bool_t readGeomConfig(CbmGeoInterface*);
  Bool_t readDetectorSetup(CbmGeoInterface*);
  Bool_t setSimulRefRun(const char*) {return kTRUE;}
  Bool_t setHistoryDate(const char*) {return kTRUE;}
private:
  CbmGeoAsciiIo(const CbmGeoAsciiIo &L);
  CbmGeoAsciiIo& operator= (const CbmGeoAsciiIo&) {return *this;}
  ClassDef(CbmGeoAsciiIo,0) // Class for geometry I/O from ASCII file
};

#endif  /* !CBMGEOASCIIIO_H */
