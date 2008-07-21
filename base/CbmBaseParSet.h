#ifndef CBMBASEPARSET_H
#define CBMBASEPARSET_H

#include "CbmParGenericSet.h"

class CbmPrimaryGenerator;
class TObjArray;

class CbmBaseParSet : public CbmParGenericSet {
public:
 
  CbmBaseParSet(const char* name="CbmBaseParSet",
             const char* title="Test class for parameter io",
             const char* context="BaseDefaultContext");
  ~CbmBaseParSet(void);
  void clear(void);
  void putParams(CbmParamList*);
  Bool_t getParams(CbmParamList*);
  
  void SetDetList(TObjArray *array){fDetList=array;}
  void SetGeoNodes(TObjArray *array){fGeoNodes=array;}

  void SetGen(CbmPrimaryGenerator *gen){fPriGen=gen;}
  
  TObjArray             *GetDetList(){return fDetList;}    
  TObjArray             *GetGeoNodes(){return fGeoNodes;}
  CbmPrimaryGenerator   *GetPriGen(){return fPriGen; }
  

protected:

  TObjArray             *fDetList;  // Detectors used in the simulation
  TObjArray            *fGeoNodes; // List of CbmGeoNodes for sensitive volumes
  CbmPrimaryGenerator   *fPriGen;   //Generator used for simulation
  ClassDef(CbmBaseParSet,1)
private:  
  CbmBaseParSet(const CbmBaseParSet &L);
  CbmBaseParSet& operator= (const CbmBaseParSet&) {return *this;}


  
};

#endif /* !CBMBASEPARSET_H */
