#ifndef FAIRGEONODE_H
#define FAIRGEONODE_H

#include "FairGeoVolume.h"
#include "FairGeoBasicShape.h"
//#include "FairGeoMedium.h"
#include "FairGeoTransform.h"

//#include "TArrayD.h"
//#include "TObjArray.h"
#include "TGeoVolume.h"

//#include <fstream>
//#include <iomanip>

class FairGeoMedium;
class FairGeoVector;
class TArrayD;
class TObjArray;
//class TGeoVolume;

enum EFairGeoNodeType {
  kFairGeoElement = 0,
  kFairGeoKeepin  = 1,
  kFairGeoModule  = 2,
  kFairGeoTopNode = 3,
  kFairGeoRefNode = 4
};


/**
 * basic geometry parameters of a volume
 * @author Ilse koenig
 */
class FairGeoNode : public FairGeoVolume
{
  private:
    FairGeoNode(const FairGeoNode&);
    FairGeoNode& operator=(const FairGeoNode&);
  protected:
    Bool_t active;                /** in/out flag for creation */
    FairGeoTransform center;        /** position of the GEANT/ROOT center */
    EFairGeoNodeType volumeType;    /** type of volume */
    Bool_t created;               /** Flag set kTRUE after creation of volume */
    FairGeoNode* copyNode;         /** pointer to the reference volume for a copy */
    TGeoVolume* rootVolume;       /** pointer to the ROOT node */
    FairGeoBasicShape*  pShape;       /** pointer to the shape */
    FairGeoNode* pMother;        //!    /** pointer to the mother volume */
    FairGeoMedium* medium;           /** pointer to medium */
    FairGeoTransform* labTransform; /** Transformation to the LAB system */
    TObjArray* fDaughterList; /** List of daughter Nodes  */
    //const char*   fTruncName;    //
    TString   fTruncName;
  public:
    FairGeoNode();
    FairGeoNode(FairGeoNode&);
    virtual ~FairGeoNode();
    void AddDaughter(FairGeoNode* fNode) {fDaughterList->AddLast(fNode);}
    TObjArray* GetListOfDaughters() {return fDaughterList;}
    EFairGeoNodeType getVolumeType() { return volumeType; }
    Bool_t isTopNode() { return (Bool_t)(volumeType == kFairGeoTopNode);}
    Bool_t isRefNode() { return (Bool_t)(volumeType == kFairGeoRefNode);}
    Bool_t isKeepin()  { return (Bool_t)(volumeType == kFairGeoKeepin);}
    Bool_t isModule()  { return (Bool_t)(volumeType == kFairGeoModule);}
    Int_t getCopyNo();
    FairGeoBasicShape* getShapePointer() { return pShape; }
    FairGeoNode* getMotherNode() {return pMother;}
    FairGeoMedium* getMedium() {return medium;}
    Bool_t isActive() {return active;}
    FairGeoTransform& getCenterPosition() {return center;}
    TArrayD* getParameters();
    FairGeoTransform* getPosition();
    FairGeoTransform* getLabTransform();
    FairGeoNode* getCopyNode() {return copyNode;}
    TGeoVolume* getRootVolume() {return rootVolume;}
    TList* getTree();
    Bool_t isSensitive();
    Bool_t isCreated() {return created;}
    void setCreated() {created=kTRUE;}
    void setName(const Text_t* s);
    void setVolumeType(EFairGeoNodeType t) {volumeType=t;}
    void setVolumePar(FairGeoNode&);
    void setShape(FairGeoBasicShape* s);
    void setMother(FairGeoNode* s);
    void setMedium(FairGeoMedium* med) {medium=med; }
    void setActive(Bool_t a=kTRUE) {active=a;}
    void setCenterPosition(const FairGeoTransform& t) {center=t;}
    void setCopyNode(FairGeoNode* p) {copyNode=p;}
    void setRootVolume(TGeoVolume* p) {rootVolume=p;}
    FairGeoTransform* calcLabTransform();
    void setLabTransform(FairGeoTransform&);
    Bool_t calcModuleTransform(FairGeoTransform&);
    Bool_t calcRefPos(FairGeoVector&);
    void clear();
    void print();
    Bool_t write(fstream&);
    Int_t compare(FairGeoNode&);


    void setTruncName( const char* aName ) { fTruncName = aName;}
    const char* getTruncName() {
      if (fTruncName.Length()>0) { return fTruncName.Data(); }
      else { return GetName(); }
    }

    ClassDef(FairGeoNode,1) //
};

// -------------------- inlines --------------------------

inline void FairGeoNode::setName(const Text_t* s)
{
  // Sets the name of the volume
  fName=s;
  fName.ToUpper();
}

inline void FairGeoNode::setShape(FairGeoBasicShape* s)
{
  // Sets the shape of the volume
  if (s) {
    pShape=s;
    shape=pShape->GetName();
  }
}

inline void FairGeoNode::setMother(FairGeoNode* moth)
{
  // Sets the mother of the volume
  if (moth) {
    pMother=moth;
    mother=pMother->GetName();
    pMother->AddDaughter(this);
  }
}

inline Bool_t FairGeoNode::isSensitive()
{
  if (medium) { return medium->isSensitive(); }
  else { return kFALSE; }
}

#endif /* !FAIRGEONODE_H */
