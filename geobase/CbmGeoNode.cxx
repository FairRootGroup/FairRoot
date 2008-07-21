//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003
//*---Modified: 21/06/2005 D.Bertini

////////////////////////////////////////////////////////////////
// CbmGeoNode
//
// Class to hold the basic geometry properties of a GEANT volume
//
////////////////////////////////////////////////////////////////
                                                                        
#include "CbmGeoNode.h"

#include "TList.h"
#include <cmath>
using std::cout;
using std::endl;

ClassImp(CbmGeoNode)

CbmGeoNode::CbmGeoNode() 
  : active(kFALSE),               
	center (CbmGeoTransform()),      
    volumeType(kCbmGeoElement),  
    created(kFALSE),               
    copyNode(0),        
    rootVolume(0),      
	pShape(0),      
	pMother(0),        
	medium(0),   
	labTransform(0), 
	fDaughterList(new TObjArray(5)),	  
	fTruncName("")


{
    // Constructor
  clear();

}

CbmGeoNode::CbmGeoNode(CbmGeoNode& r)
    :active(kFALSE),               
	center (r.getCenterPosition()),      
    volumeType(r.getVolumeType()),  
    created(kFALSE),               
    copyNode(r.getCopyNode()),        
    rootVolume(r.getRootVolume()),      
	pShape(0),      
	pMother(0),        
	medium(0),   
	labTransform(new CbmGeoTransform(*(r.getLabTransform()))), 
	fDaughterList(new TObjArray(*(r.GetListOfDaughters()))),	  
	fTruncName(r.getTruncName())

 {
  // Copy constructor
  points=0;
  nPoints = 0;
  fName=r.GetName();
  setVolumePar(r);
  if (r.isActive()) active=kTRUE;
  if (r.isCreated()) created=kTRUE;
  
}

CbmGeoNode::~CbmGeoNode() {
  // Destructor
  if (points) {
    for (Int_t i=0;i<nPoints;i++) points->RemoveAt(i);
    delete points;
    points=0;
  }
  if (labTransform) {
    delete labTransform;
    labTransform=0;
  }
  if(fDaughterList){
    fDaughterList->Delete();
    delete   fDaughterList;
  }
}

void CbmGeoNode::setVolumePar(CbmGeoNode& r) {
  // Copies all volume parameters except the name
  setMother(r.getMotherNode());
  medium=r.getMedium();
  setShape(r.getShapePointer());
  Int_t n=r.getNumPoints();
  createPoints(n);
  for (Int_t i=0;i<nPoints;i++) setPoint(i,*(r.getPoint(i)));
  transform=r.getTransform();
}

void CbmGeoNode::clear() {
  // Clears the volume and deletes the points
/*  pMother=0;
  medium=0;
  pShape=0;
  volumeType=kCbmGeoElement;
  active=kFALSE;
  created=kFALSE;
  copyNode=0;
  rootVolume=0;
*/  
  if (labTransform) {
    delete labTransform;
    labTransform=0;
  }
  CbmGeoVolume::clear();
}

Int_t CbmGeoNode::getCopyNo() {
  // Returns the copy number
  Int_t n=0;
  if (fHadFormat == 1 ) {

  Int_t l=fName.Length();
  if (l>4) {
    TString s(fName);
    s.Remove(0,4);
    sscanf(s.Data(),"%i",&n);
  }
  } else {

  Ssiz_t l=fName.Last('#');
  if (l>0) {
    TString s(fName);
    s.Remove(0,l+1);
    sscanf(s.Data(),"%i",&n);
  }
  }

  return n; 
}

TArrayD* CbmGeoNode::getParameters() {
  // Returns the parameters to create a GEANT/ROOT volume
  if (pShape) return pShape->calcVoluParam(this);
  return 0;
}

CbmGeoTransform* CbmGeoNode::getPosition() {
  // Returns the transformation to position a volume in GEANT/ROOT
  if (pShape&&pMother) {
    pShape->calcVoluPosition(this,pMother->getCenterPosition());
    center.setTransform(*(pShape->getCenterPosition()));
    return pShape->getVoluPosition();
  }
  return 0;
}

void CbmGeoNode::print() {
  // Prints all parameters of a volume
   cout<<"//----------------------------------------------------------\n";
   CbmGeoVolume::print();
   cout<<"//----------------------------------------------------------\n";
   return;

  cout<<((const char*)fName)<<'\n';
  if (pMother)cout<<((const char*)mother)<<'\n';
  else cout<<"-- unknown mother --\n";
  if (!copyNode) {
    if (pShape) cout<<((const char*)shape)<<'\n';
    else cout<<"-- unknown shape --\n";
    if (medium) cout<<medium->GetName()<<'\n';
    else cout<<"-- unknown medium --\n";
    if (points && pShape) pShape->printPoints(this);
    else cout<<"-- no points --\n";
  }
  transform.getTransVector().print();
  transform.getRotMatrix().print();
  cout<<"//----------------------------------------------------------\n";
}

Bool_t CbmGeoNode::write(fstream& fout) {
  // Writes all parameters of a volume to file
  fout<<fName.Data()<<'\n';
  if (pMother) fout<<((const char*)mother)<<'\n';
  else {
    Error("write","Unknown mother for %s\n",fName.Data());
    return kFALSE;
  }
  if (!copyNode) {
    if (pShape) fout<<((const char*)shape)<<'\n';
    else {
      Error("write","Unknown shape for %s\n",fName.Data());
      return kFALSE;
    }
    if (medium) fout<<medium->GetName()<<'\n';
    else {
      Error("write","Unknown medium for %s\n",fName.Data());
      return kFALSE;
    }
    if (points && pShape) pShape->writePoints(&fout,this);
    else {
      Error("write","No points for %s\n",fName.Data());
      return kFALSE;
    }
  }
  const CbmGeoRotation& r=transform.getRotMatrix();
  const CbmGeoVector& v=transform.getTransVector();
  fout.precision(3);
  fout<<v(0)<<" "<<v(1)<<" "<<v(2)<<'\n';
  fout.precision(7);
  for(Int_t i=0;i<9;i++) fout<<r(i)<<"  ";
  fout<<'\n';
  fout<<"//----------------------------------------------------------\n";
  return kTRUE;
}

TList* CbmGeoNode::getTree() {
  // Returns the tree of the mother volumes
  TList* tree=new TList();  
  CbmGeoNode* v=this;
  CbmGeoNode* mother;
  do {
    mother=v->getMotherNode();
    if (mother) tree->Add(mother);
    v=mother;
  } while (v&&!v->isTopNode());
  return tree; 
}

CbmGeoTransform* CbmGeoNode::getLabTransform() {
  // Returns the lab transformation
  if (labTransform) return labTransform;
  else return calcLabTransform();
}

CbmGeoTransform* CbmGeoNode::calcLabTransform() {
  // Calculates the lab transformation

  labTransform=new CbmGeoTransform(transform);

  if (!isTopNode()) {
    if (!pMother) {
      Error("calcLabTransform()","Mother volume of %s not found!",GetName());
      delete labTransform;
      return 0;
    }
    CbmGeoTransform* tm=pMother->getLabTransform();
    if (!tm) {; 
      Error("calcLabTransform()",
            "Lab Transformation of mother volume of %s not found!",GetName());
      delete labTransform;
      return 0;
    } 
    labTransform->transFrom(*tm);
  }

  fLabTransform = *labTransform;
  fMedium = *medium;
  return labTransform;
}

void CbmGeoNode::setLabTransform(CbmGeoTransform& t) {
  // Sets the lab transformation
  if (!isTopNode()) {
    if (labTransform) labTransform->setTransform(t); 
    else labTransform=new CbmGeoTransform(t);
    if (!pMother) {
      Error("calcLabTransform()","Mother volume of %s not found!",GetName());
      delete labTransform;
      return;
    }
    CbmGeoTransform* tm=pMother->getLabTransform();
    if (!tm) {; 
      Error("calcLabTransform()",
            "Lab Transformation of mother volume of %s not found!",GetName());
      delete labTransform;
      return;
    } 
    transform=t;
    transform.transTo(*tm);
  }
}

Bool_t CbmGeoNode::calcModuleTransform(CbmGeoTransform& modTransform) {
  // Calculates the transformation relative to the detectors coordinate system
  CbmGeoNode* node=this;
  modTransform=transform;
  while (node&&!node->isModule()) {
    CbmGeoNode* pm=node->getMotherNode();
    if (!pm) {
      Error("calcModuleTransform","Mother volume of %s not found!",node->GetName());
      return kFALSE;
    }
    modTransform.transFrom(pm->getTransform());
    node=pm;
  }
  if (isTopNode()) return kFALSE;
  else return kTRUE;
}

Bool_t CbmGeoNode::calcRefPos(CbmGeoVector& refPos) {
  // Calculates the position in the detectors coordinate system
  CbmGeoNode* node=this;
  refPos=center.getTransVector();
  do {
    refPos=node->getTransform().transFrom(refPos);
    node=node->getMotherNode();
    if (!node) {
      Error("calcModuleTransform","Mother volume %s not found!",node->GetName());
      return kFALSE;
    }
  } while (node&&!node->isModule());
  if (isTopNode()) return kFALSE;
  else return kTRUE;
}

Int_t CbmGeoNode::compare(CbmGeoNode& rn) {
  // Compares the volume with the volume rn and prints the diagnose
  // Returns kTRUE if the volume parameters are the same
  Int_t diff[]={0,0,0,0,0,0};
  Int_t n=0;
  cout<<fName<<'\t';
  if (mother.CompareTo(rn.getMother())!=0) {
    diff[0]=1;
    n++;
  }
  if (medium&&rn.getMedium()) {
    TString med=medium->GetName();
     if (med.CompareTo(rn.getMedium()->GetName())!=0) {
       diff[1]=1;
       n++;
     }
  } else {
    diff[1]=1;
    n++;
  }
  if (shape.CompareTo(rn.getShape())!=0) {
    diff[2]=1;
    n++;
  }
  Int_t np=rn.getNumPoints();
  if (points&&nPoints==np) {
    for (Int_t i=0;i<np;i++) {
      CbmGeoVector v1=*(getPoint(i));
      CbmGeoVector v2=*(rn.getPoint(i));
      if (fabs(v1(0)-v2(0))>=0.001||fabs(v1(1)-v2(1))>=0.001||fabs(v1(1)-v2(1))>=0.001) {
        diff[3]=1;
        n++;
        break;
      }
    }
  } else {
    diff[3]=1;
    n++;
  }
  CbmGeoVector v1=transform.getTransVector();
  CbmGeoVector v2=rn.getTransform().getTransVector();
  if (fabs(v1(0)-v2(0))>=0.001||fabs(v1(1)-v2(1))>=0.001||fabs(v1(1)-v2(1))>=0.001) {
    diff[4]=1;
    n++;
  }
  CbmGeoRotation r1=transform.getRotMatrix();
  CbmGeoRotation r2=rn.getTransform().getRotMatrix();
  for (Int_t i=0;i<9;i++) {
    if (fabs(r1(i)-r2(i))>=1.e-7) {
      diff[5]=1;
      n++;
      break;
    }
  }
  if (n>0) {
    for (Int_t i=0;i<6;i++) cout<<"    "<<diff[i]<<"  ";
    cout<<'\n';
  } else cout<<" same\n";
  return n;
}
