#ifndef CBMGEONODE_H
#define CBMGEONODE_H

#include "CbmGeoVolume.h"
#include "CbmGeoBasicShape.h"
//#include "CbmGeoMedium.h"
#include "CbmGeoTransform.h"

//#include "TArrayD.h"
//#include "TObjArray.h"
#include "TGeoVolume.h"

//#include <fstream>
//#include <iomanip>

class CbmGeoMedium;
class CbmGeoVector;
class TArrayD;
class TObjArray;
//class TGeoVolume;

enum ECbmGeoNodeType {
  kCbmGeoElement = 0,
  kCbmGeoKeepin  = 1,
  kCbmGeoModule  = 2,
  kCbmGeoTopNode = 3,
  kCbmGeoRefNode = 4 };


/**
 * basic geometry parameters of a volume
 * @author Ilse koenig 
 */
class CbmGeoNode : public CbmGeoVolume {
private:
  CbmGeoNode(const CbmGeoNode &L);
  CbmGeoNode& operator= (const CbmGeoNode&) {return *this;}
protected:
  Bool_t active;                /** in/out flag for creation */
  CbmGeoTransform center;        /** position of the GEANT/ROOT center */
  ECbmGeoNodeType volumeType;    /** type of volume */
  Bool_t created;               /** Flag set kTRUE after creation of volume */
  CbmGeoNode* copyNode;         /** pointer to the reference volume for a copy */
  TGeoVolume* rootVolume;       /** pointer to the ROOT node */
  CbmGeoBasicShape*  pShape;       /** pointer to the shape */
  CbmGeoNode* pMother;        //!    /** pointer to the mother volume */
  CbmGeoMedium* medium;           /** pointer to medium */
  CbmGeoTransform* labTransform; /** Transformation to the LAB system */
  TObjArray *fDaughterList;	/** List of daughter Nodes  */
  //const char*   fTruncName;    // 
  TString   fTruncName;
public:
  CbmGeoNode();
  CbmGeoNode(CbmGeoNode&);
  virtual ~CbmGeoNode();
  void AddDaughter(CbmGeoNode *fNode){fDaughterList->AddLast(fNode);}
  TObjArray *GetListOfDaughters(){return fDaughterList;}
  ECbmGeoNodeType getVolumeType() { return volumeType; }
  Bool_t isTopNode() { return (Bool_t)(volumeType == kCbmGeoTopNode);}
  Bool_t isRefNode() { return (Bool_t)(volumeType == kCbmGeoRefNode);}
  Bool_t isKeepin()  { return (Bool_t)(volumeType == kCbmGeoKeepin);}
  Bool_t isModule()  { return (Bool_t)(volumeType == kCbmGeoModule);}
  Int_t getCopyNo();
  CbmGeoBasicShape* getShapePointer() { return pShape; }
  CbmGeoNode* getMotherNode() {return pMother;}
  CbmGeoMedium* getMedium() {return medium;}
  Bool_t isActive() {return active;}
  CbmGeoTransform& getCenterPosition() {return center;}
  TArrayD* getParameters();
  CbmGeoTransform* getPosition();
  CbmGeoTransform* getLabTransform();
  CbmGeoNode* getCopyNode() {return copyNode;}    
  TGeoVolume* getRootVolume() {return rootVolume;}
  TList* getTree();
  Bool_t isSensitive();
  Bool_t isCreated() {return created;}
  void setCreated() {created=kTRUE;}
  void setName(const Text_t* s);
  void setVolumeType(ECbmGeoNodeType t) {volumeType=t;}
  void setVolumePar(CbmGeoNode&);
  void setShape(CbmGeoBasicShape* s);
  void setMother(CbmGeoNode* s);
  void setMedium(CbmGeoMedium* m) {medium=m; }
  void setActive(Bool_t a=kTRUE) {active=a;}
  void setCenterPosition(const CbmGeoTransform& t) {center=t;}
  void setCopyNode(CbmGeoNode* p) {copyNode=p;}
  void setRootVolume(TGeoVolume* p) {rootVolume=p;}
  CbmGeoTransform* calcLabTransform();
  void setLabTransform(CbmGeoTransform&);
  Bool_t calcModuleTransform(CbmGeoTransform&);
  Bool_t calcRefPos(CbmGeoVector&);
  void clear();
  void print();
  Bool_t write(fstream&);
  Int_t compare(CbmGeoNode&);
  
  
  void setTruncName( const char* aName ) { fTruncName = aName;}
  const char* getTruncName() {
      if (fTruncName.Length()>0) return fTruncName.Data();
      else return GetName();
  }
 
  ClassDef(CbmGeoNode,1) //
};

// -------------------- inlines --------------------------

inline void CbmGeoNode::setName(const Text_t* s) {
  // Sets the name of the volume
  fName=s;
  fName.ToUpper();
}

inline void CbmGeoNode::setShape(CbmGeoBasicShape* s) {
  // Sets the shape of the volume
  if (s) {
    pShape=s;
    shape=pShape->GetName();
  }
}

inline void CbmGeoNode::setMother(CbmGeoNode* m) {
  // Sets the mother of the volume
  if (m) {
    pMother=m;
    mother=pMother->GetName();
    pMother->AddDaughter(this);
  }
}

inline Bool_t CbmGeoNode::isSensitive() {
  if (medium) return medium->isSensitive();
  else return kFALSE;
}

#endif /* !CBMGEONODE_H */
