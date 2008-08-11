#ifndef CBMGEOIO_H
#define CBMGEOIO_H

#include "TObject.h"

class CbmGeoMedia;
class CbmGeoSet;
class CbmGeoInterface;

/**
 * Abstract base class for geometry I/O
 * @author Ilse Koenig 
 */
class CbmGeoIo : public TObject {
public:
  virtual Bool_t open(const char*,const Text_t* status="in")=0;
  virtual void close()=0;
  virtual void print()=0;
  virtual Bool_t isOpen()=0;
  virtual Bool_t isWritable()=0;
  virtual Bool_t read(CbmGeoMedia*)=0;
  virtual Bool_t read(CbmGeoSet*,CbmGeoMedia*)=0;
  virtual Bool_t write(CbmGeoMedia*)=0;
  virtual Bool_t write(CbmGeoSet*)=0;
  virtual Bool_t readGeomConfig(CbmGeoInterface*)=0; 
  virtual Bool_t setSimulRefRun(const char*)=0;
  virtual Bool_t setHistoryDate(const char*)=0;
private:
  ClassDef(CbmGeoIo,0) // 
};

#endif  /* !CBMGEOIO_H */
