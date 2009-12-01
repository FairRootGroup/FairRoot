#ifndef FAIRBASEPARSET_H
#define FAIRBASEPARSET_H

#include "FairParGenericSet.h"
#include "TGeoManager.h"
#include "TObjString.h"
class FairPrimaryGenerator;
class TObjArray;
class TList;

class FairBaseParSet : public FairParGenericSet {
public:
 
  FairBaseParSet(const char* name="FairBaseParSet",
             const char* title="Test class for parameter io",
             const char* context="BaseDefaultContext");
  ~FairBaseParSet(void);
  void clear(void);
  void putParams(FairParamList*);
  Bool_t getParams(FairParamList*);
  
  void SetDetList(TObjArray *array){fDetList=array;}
  void SetGeoNodes(TObjArray *array){fGeoNodes=array;}
  void SetGen(FairPrimaryGenerator *gen){fPriGen=gen;}
  void SetBeamMom(Double_t  BMom){fBeamMom = BMom;}
  void SetGeometry(TGeoManager *Geom){fGeom=Geom;}
  void SetContListStr(TObjArray *list){fContNameList= list;}
	  


  TObjArray             *GetDetList(){return fDetList;}    
  TObjArray             *GetGeoNodes(){return fGeoNodes;}
  FairPrimaryGenerator   *GetPriGen(){return fPriGen; }
  Double_t			    GetBeamMom(){return fBeamMom; }
  TGeoManager           *GetGeometry(){return fGeom;}
  TObjArray             *GetContList(){return fContNameList;}
  
protected:

  TObjArray              *fDetList;  // Detectors used in the simulation
  TObjArray              *fGeoNodes; // List of FairGeoNodes for sensitive volumes
  FairPrimaryGenerator   *fPriGen;   //Generator used for simulation
  Double_t 		          fBeamMom;  //Beam momentum
  TGeoManager            *fGeom; // Geometry
  TObjArray              *fContNameList; // List of parameter container names in the RUN
    
  ClassDef(FairBaseParSet,3)
private:  
  FairBaseParSet(const FairBaseParSet &L);
  FairBaseParSet& operator= (const FairBaseParSet&) {return *this;}


  
};

#endif /* !FAIRBASEPARSET_H */
