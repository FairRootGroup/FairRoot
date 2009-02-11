#ifndef FAIRBASEPARSET_H
#define FAIRBASEPARSET_H

#include "FairParGenericSet.h"

class FairPrimaryGenerator;
class TObjArray;

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
  
  TObjArray             *GetDetList(){return fDetList;}    
  TObjArray             *GetGeoNodes(){return fGeoNodes;}
  FairPrimaryGenerator   *GetPriGen(){return fPriGen; }
  

protected:

  TObjArray             *fDetList;  // Detectors used in the simulation
  TObjArray            *fGeoNodes; // List of FairGeoNodes for sensitive volumes
  FairPrimaryGenerator   *fPriGen;   //Generator used for simulation
  ClassDef(FairBaseParSet,1)
private:  
  FairBaseParSet(const FairBaseParSet &L);
  FairBaseParSet& operator= (const FairBaseParSet&) {return *this;}


  
};

#endif /* !FAIRBASEPARSET_H */
