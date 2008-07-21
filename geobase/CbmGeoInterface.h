#ifndef CBMGEOINTERFACE_H
#define CBMGEOINTERFACE_H

#include "TObject.h"
#include "TString.h"
//#include "TObjArray.h"
//#include "TList.h"

class CbmGeoIo;
class CbmGeoSet;
class CbmGeoMedia;
class CbmGeoShapes;
class CbmGeoBuilder;
class TObjArray;
class TList;

enum EHGeoDetPart {
  kCbmGeoCave   =  0,
  kCbmGeoPipe   =  1,
  kCbmGeoTarget =  2,
  kCbmGeoMagnet =  3,
  kCbmGeoRich   =  4,
  kCbmGeoSts    =  5,
  kCbmGeoTrd    =  6,
  kCbmGeoTof    =  7,
  kCbmGeoEcal   =  8
};


/**
 * Class to manage geometry for simulations
 * @author Ilse koenig
 * @author M. Al-Turany 
 */
class CbmGeoInterface : public TObject { 
  CbmGeoIo*      fileInput;   /** ASCII file I/O */
  CbmGeoIo*      oraInput;    /** Oracle input */
  CbmGeoIo*      output;      /** Oracle output */
  Int_t         nSets;       /** number of geometry sets (detector parts) */
  Int_t         nActualSets; /** number of set in actual geometry */
  TObjArray*    sets;        /** array of geometry  sets */
  CbmGeoMedia*   media;       /** list of media */
  CbmGeoShapes*  shapes;      /** list of shapes */
  TList*        masterNodes; /** list of mother nodes used by several sets */
  TString       setupFile;   /** file with detector setups (subsets) */
  CbmGeoBuilder* geoBuilder;  /** actually used geometry builder */
public:
  CbmGeoInterface();
  ~CbmGeoInterface();
  void setOracleInput(CbmGeoIo* p) {oraInput=p;}
  void setOutput(CbmGeoIo* p) {output=p;}
  void setGeomBuilder(CbmGeoBuilder* p) {geoBuilder=p;}
  CbmGeoIo* getFileInput() { return fileInput; }
  CbmGeoIo* getOraInput() { return oraInput; }
  CbmGeoIo* getOutput() { return output; }
  CbmGeoShapes* getShapes() { return shapes; }
  CbmGeoMedia* getMedia() { return media; }
  TList* getMasterNodes() { return masterNodes; }
  void addInputFile(const char*);
  void addGeoModule(CbmGeoSet*);
  void setMediaFile(const char *file);
  CbmGeoSet* findSet(const char*);
  Bool_t readSet(CbmGeoSet*);
  Bool_t writeSet(CbmGeoSet*);
  Bool_t writeSet(CbmGeoSet*,const char*);
  Bool_t createSet(CbmGeoSet*);
  void deleteSet(CbmGeoSet* pSet);
  Bool_t readMedia();
  Bool_t writeMedia();
  Bool_t writeMedia(const char*);
  Bool_t readAll();
  Bool_t writeAll();
  Bool_t createAll(Bool_t withCleanup=kFALSE);
  Bool_t createGeometry(Bool_t withCleanup=kFALSE);
  Bool_t readGeomConfig(const char*);
  void addSetupFile(const char* f) {setupFile=f;}
  Bool_t readSetupFile();
  void print();
  void SetNoOfSets(Int_t n){nSets=n;} //
private:
  CbmGeoInterface(const CbmGeoInterface &L);
  CbmGeoInterface& operator= (const CbmGeoInterface&) {return *this;}

  CbmGeoIo* connectInput(const char*);
  Bool_t connectOutput(const char*);
 
  ClassDef(CbmGeoInterface,0) //
};

#endif /* !CBMGEOINTERFACE_H */
