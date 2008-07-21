#ifndef CBMGEOSET_H
#define CBMGEOSET_H


#include "CbmGeoTransform.h"

#include "TNamed.h"
//#include "TArrayI.h"
#include "TList.h"

#include <fstream>
//#include <iomanip>

class CbmGeoNode;
class CbmGeoShapes;
class CbmGeoMedia;
class CbmGeoBuilder;
class TArrayI;
//class TList;

/**
 * Base class for geometry of detector parts
 * @author Ilse koenig 
 */
class  CbmGeoSet : public TNamed {

protected:
 Int_t hadesGeo;

 class CbmGeoCopyNode : public TNamed {
    public:
      CbmGeoNode* pNode;
      CbmGeoCopyNode(const char* name,CbmGeoNode* node)
	   : pNode(node)
	  {
        SetName(name);
       
      }
      ~CbmGeoCopyNode() {}
	  private:
	     CbmGeoCopyNode(const CbmGeoCopyNode &L);
         CbmGeoCopyNode& operator= (const CbmGeoCopyNode&) {return *this;}

  };
  TList* volumes;         /** list of volumes */
  TList* masterNodes;     /** pointer to list of mother volumes from other detector parts*/
  Int_t maxSectors;       /** maximum number of sectors (-1 for detectors outside any sector)*/
  Int_t maxKeepinVolumes; /** maximum number of keepin volumes per sector*/
  Int_t maxModules;       /** maximum number of modules per sector*/
  TArrayI* modules;       /** Module's array.*/
  CbmGeoShapes* pShapes;  /** pointer to the class CbmGeoShapes*/
  TString geoFile;        /** name of geometry input file or Oracle*/
  TString author;         /** author of the media version*/
  TString description;    /** description of the version*/

  CbmGeoSet();
  void readInout(fstream&);
  void readTransform(fstream&,CbmGeoTransform&);
  Bool_t readVolumeParams(fstream&,CbmGeoMedia*,CbmGeoNode*,TList* l=0);
  Bool_t readKeepIn(fstream&,CbmGeoMedia*,TString&);
  Bool_t readModule(fstream&,CbmGeoMedia*,TString&,TString&,Bool_t a=kFALSE);
public :
  virtual ~CbmGeoSet();
  void setShapes(CbmGeoShapes* s) {pShapes=s;}
  void setMasterNodes(TList* m) {masterNodes=m;}
  void setGeomFile(const char* filename) {geoFile=filename;}
  const char* getGeomFile() { return geoFile.Data(); }
  Int_t getMaxSectors(void) {return maxSectors;}
  Int_t getMaxModules(void) {return maxModules;}
  Int_t getMaxKeepinVolumes(void) {return maxKeepinVolumes;}
  void setModules(Int_t,Int_t*);
  Int_t* getModules(void);
  Int_t getModule(Int_t,Int_t);
  CbmGeoNode* getVolume(const char* name) {return (CbmGeoNode*)volumes->FindObject(name);}
  CbmGeoNode* getMasterNode(const char* name) {return (CbmGeoNode*)masterNodes->FindObject(name);}
  TList* getListOfVolumes() {return volumes;}
  CbmGeoShapes* getShapes() {return pShapes;}
  void setAuthor(TString& s) {author=s;}
  void setDescription(TString& s) {description=s;}
  TString& getAuthor() {return author;}
  TString& getDescription() {return description;}
  virtual const char* getKeepinName(Int_t,Int_t) {return 0;}  
  virtual const char* getModuleName(Int_t) {return 0;}  
  virtual const char* getEleName(Int_t) {return 0;}  
  virtual Int_t getSecNumInMod(const TString&) {return -1;}
  virtual Int_t getModNumInMod(const TString&) {return 0;}
  virtual Bool_t read(fstream&,CbmGeoMedia*);
  virtual void addRefNodes() {}
  virtual void write(fstream&);
  virtual void print();
  virtual Bool_t create(CbmGeoBuilder*);
  void compare(CbmGeoSet&);
  ClassDef(CbmGeoSet,0) // 
  private:
    CbmGeoSet(const CbmGeoSet &L);
    CbmGeoSet& operator= (const CbmGeoSet&) {return *this;}
};


#endif  /* !CBMGEOSET_H */
