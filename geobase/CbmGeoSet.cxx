//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// CbmGeoSet
//
// Base class for geometry of detector parts
//
/////////////////////////////////////////////////////////////

#include "CbmGeoSet.h"

#include "CbmGeoNode.h"
#include "CbmGeoShapes.h"
#include "CbmGeoBasicShape.h"
#include "CbmGeoMedium.h"
#include "CbmGeoBuilder.h"
#include "CbmGeoMedia.h"

#include "TString.h"
#include "TArrayI.h"

//#include "ctype.h"
using std::cout;
using std::endl;
using std::ios;


class CbmGeoTransform;

ClassImp(CbmGeoSet)

CbmGeoSet::CbmGeoSet() 
  : hadesGeo(0),
   volumes(new TList()),
   masterNodes(0),
   maxSectors(0),
   maxKeepinVolumes(0),
   maxModules(0),
   modules(0),
   pShapes(0),
   geoFile(""),
   author(""),
   description("")

{
  // Constructor
   
  
}

CbmGeoSet::~CbmGeoSet() {
  // Destructor
  if (volumes) {
//    volumes->Delete("slow");
    delete volumes;
    volumes=0;
  }
  if (modules) {
    delete modules;
    modules=0;
  }
}

void CbmGeoSet::setModules(Int_t s,Int_t* m){
  // Stores the modules given in 'm' as active modules in sector 's'
  // May be called with s=-1 for detectors not belonging to a sector
  if (!modules) {
    if (maxSectors==0&&maxModules>0) modules=new TArrayI(maxModules);
    if (maxSectors>0&&maxModules>0) modules=new TArrayI(maxSectors*maxModules);
  }
  Int_t sec=0;
  if (s>0) sec=s;
  for(Int_t i=0;i<maxModules;i++) {
    if (modules) modules->AddAt(m[i],(sec*maxModules+i));
  }
}

Int_t* CbmGeoSet::getModules(){
  // Returns a linear array of all modules
  if (modules) return modules->GetArray();
  return 0;
}

Int_t CbmGeoSet::getModule(Int_t s,Int_t m) {
  // Returns 1, if the module is not explicitly set inactive
  // (in this case it returns 0)
  // May be called with s=-1 for detectors not belonging to a sector
  if (!modules) return 1;
  if (m<maxModules&&s<0) return (*modules)[m];
  if (m<maxModules&&s<maxSectors) return (*modules)[(s*maxModules+m)];
  return 0;
}

Bool_t CbmGeoSet::read(fstream& fin,CbmGeoMedia* media) {
  // Reads the geometry from file
  Int_t s1=-1,s2=0;
  if (maxSectors>0) {
    s1=0;
    s2=maxSectors;
  }
  Bool_t rc=kTRUE;
  for (Int_t s=s1;s<s2&&rc;s++) {
    for (Int_t k=0;k<maxKeepinVolumes&&rc;k++) {
      TString keepinName=getKeepinName(s,k);
      rc=readKeepIn(fin,media,keepinName);
    }
  }
  for (Int_t m=0;m<maxModules&&rc;m++) {
    Bool_t containsActiveModule=kFALSE;
    for (Int_t s=s1;s<s2;s++) {
      if (getModule(s,m)) containsActiveModule=kTRUE;
    }
    TString modName=getModuleName(m);
    TString eleName=getEleName(m);
    rc=readModule(fin,media,modName,eleName,containsActiveModule);
  }
  return rc;
}

void CbmGeoSet::readInout(fstream& fin) {
  // Reads the inout flag (in old files)
  char c=' ';
  do {
    c=fin.get();
  } while (c==' ' || c=='\n');
  if (c!='0'&&c!='1') fin.putback(c);
  else do {
    c=fin.get();
  } while (c!='\n');
  return;
}

void CbmGeoSet::readTransform(fstream& fin,CbmGeoTransform& tf) {
  // Reads the transformation from file
  Double_t r[9], t[3];
  fin>>t[0]>>t[1]>>t[2];
  for(Int_t i=0;i<9;i++) fin>>r[i];
  tf.setRotMatrix(r);
  tf.setTransVector(t);
}

Bool_t CbmGeoSet::readVolumeParams(fstream& fin,CbmGeoMedia* media,
                                 CbmGeoNode* volu,TList* refVolumes) {
  // Reads the volume definition from file
//  Int_t hadgeo =  1;
  if (volu==0||media==0||refVolumes==0) return kFALSE;
  const Int_t maxbuf=256;
  char buf[maxbuf];
  TString name(volu->GetName());
  Int_t nameLength=name.Length();
  Bool_t isCopy=kFALSE;
  fin>>buf;
  CbmGeoNode* mother=0;
  CbmGeoCopyNode* refNode=0;
  TString refName;

  if (volu->isKeepin()) mother=getMasterNode(buf);
  else if (volu->isModule()) { 
    mother=getMasterNode(buf);
    if (!mother) mother=getVolume(buf);
    if (volu->isActive()&&mother) mother->setActive();
  } else {
    mother=getVolume(buf);
    if (!mother) mother=getMasterNode(buf); 
  }

  volu->setMother(mother);
  if (!mother) Warning("readVolumeParams","Mother volume %s not found!",buf);

  if ( hadesGeo == 1 ) {
      //  cout << " read copies in Hades format " << endl;

  if (nameLength>4) {
   char c;
    do {
      c=fin.get();
    } while (c==' ' || c=='\n');
    Int_t i=(Int_t)c ;
    fin.putback(c);
   
    if (!isalpha(i))  isCopy=kTRUE;
    refName=name(0,4);
    refNode=(CbmGeoCopyNode*)refVolumes->FindObject(refName);
    if (!refNode) {
      if (isCopy) return kFALSE;
      refVolumes->Add(new CbmGeoCopyNode(refName.Data(),volu));
    } else {
	CbmGeoNode* cn=refNode->pNode;
      volu->setCopyNode(cn);
      volu->setMedium(cn->getMedium());
      volu->setShape(cn->getShapePointer());
      Int_t n=cn->getNumPoints();
      volu->createPoints(n);
      for (Int_t i=0;i<n;i++) volu->setPoint(i,*(cn->getPoint(i)));
    }
  }

  } else {
  // cbm format
  Ssiz_t l=name.Last('#');
  if (l>0) {
    char c;
    do {
      c=fin.get();
    } while (c==' ' || c=='\n');
    Int_t i=(Int_t)c;
    fin.putback(c);
    if (!isalpha(i)) isCopy=kTRUE;
    refName=name(0,l);
    refNode=(CbmGeoCopyNode*)refVolumes->FindObject(refName);
    if (!refNode) {
      if (isCopy) return kFALSE;
      refVolumes->Add(new CbmGeoCopyNode(refName.Data(),volu));
    } else {
      CbmGeoNode* cn=refNode->pNode;
      volu->setCopyNode(cn);
      volu->setMedium(cn->getMedium());
      volu->setShape(cn->getShapePointer());
      Int_t n=cn->getNumPoints();
      volu->createPoints(n);
      for (Int_t i=0;i<n;i++) volu->setPoint(i,*(cn->getPoint(i)));
    }
  }

  }

  if (!isCopy) {
    fin>>buf;
    CbmGeoBasicShape* sh=pShapes->selectShape(buf);
    if (sh) volu->setShape(sh);
    else return kFALSE;
    fin>>buf;
    CbmGeoMedium* medium=media->getMedium(buf);
    if (!medium) {
      Error("readVolumeParams","Medium %s not found in list of media",buf);
      return kFALSE;
    }
    volu->setMedium(medium);
    Int_t n=0;
    fin.getline(buf,maxbuf); // to read the end of line
    if (sh) n=sh->readPoints(&fin,volu);
    if (n<=0) return kFALSE;
  }
  readTransform(fin,volu->getTransform());
  return kTRUE;
}

Bool_t CbmGeoSet::readKeepIn(fstream& fin,CbmGeoMedia* media,TString& name) {
  // Reads the keepin volume from file
  fin.clear();
  fin.seekg(0, ios::beg);
  CbmGeoNode* volu=0;
  Bool_t rc=kTRUE;
  TList refVolumes;
  const Int_t maxbuf=256;
  char buf[maxbuf];
  while(rc && !volu && !fin.eof()) {
    fin>>buf;
    if (buf[0]=='/') fin.getline(buf,maxbuf);
    else if (!fin.eof()) {
      if (strcmp(buf,name)==0) {
        volu=new CbmGeoNode;
        volu->SetName(buf);
        volu->setVolumeType(kCbmGeoKeepin);
        readInout(fin);
        rc=readVolumeParams(fin,media,volu,&refVolumes);
      } else {
        do {
          fin.getline(buf,maxbuf); 
        } while(!fin.eof()&&buf[0]!='/'); 
      }
    }
  }
  if (rc) volumes->Add(volu);
  else {
    delete volu;
    volu=0;
  }
  refVolumes.Delete();
  return rc;
}

Bool_t CbmGeoSet::readModule(fstream& fin,CbmGeoMedia* media,TString& modName,
                           TString& eleName,Bool_t containsActiveMod) {
  // Reads the whole geometry of a module from file
  const Int_t maxbuf=256;
  Text_t buf[maxbuf];
  fin.clear();
  fin.seekg(0,ios::beg);
  CbmGeoNode* volu=0;
  Bool_t rc=kTRUE;
  TList refVolumes;
  TString name;
  while(rc && !fin.eof()) {
    fin>>buf;
    if (buf[0]=='/') fin.getline(buf,maxbuf);
    else if (!fin.eof()) {
      TString name(buf);      
      if (name.BeginsWith(modName)) {
        volu=new CbmGeoNode;
        volu->SetName(buf);
        volu->setVolumeType(kCbmGeoModule);
        Int_t a=getModule(getSecNumInMod(buf),getModNumInMod(buf));
        if (a>0) volu->setActive(kTRUE);
        else volu->setActive(kFALSE);
        readInout(fin);
        rc=readVolumeParams(fin,media,volu,&refVolumes);
        if (rc) volumes->Add(volu);
        else {
          Error("readModule","Failed for module %s\n",volu->GetName());
          delete volu;
          volu=0;
        }
      } else if (!eleName.IsNull()&&name.BeginsWith(eleName)) {
        volu=new CbmGeoNode;
        volu->SetName(buf);
        volu->setVolumeType(kCbmGeoElement);
        volu->setActive(containsActiveMod);
        rc=readVolumeParams(fin,media,volu,&refVolumes);
        if (rc) volumes->Add(volu);
        else {
          Error("readModule","Failed for %s\n",volu->GetName());
          delete volu;
          volu=0;
        }
      } else {
        do {
          fin.getline(buf,maxbuf);
        } while(!fin.eof()&&buf[0]!='/'); 
      }
    }
  }
  refVolumes.Delete();
  return rc;
}

void CbmGeoSet::print() {
  // Prints the geometry
  if (!author.IsNull())      cout<<"//Author:      "<<author<<'\n';
  if (!description.IsNull()) cout<<"//Description: "<<description<<'\n';
  if (!description.IsNull()) 
  cout<<"//----------------------------------------------------------\n";
  cout.setf(ios::fixed,ios::floatfield);
  TListIter iter(volumes);
  CbmGeoNode* volu;
  while((volu=(CbmGeoNode*)iter.Next())) {
    volu->print();
  }
}

void CbmGeoSet::write(fstream& fout) {
  // Writes the volumes to file
  if (!author.IsNull())      fout<<"//Author:      "<<author<<'\n';
  if (!description.IsNull()) fout<<"//Description: "<<description<<'\n';
  fout<<"//----------------------------------------------------------\n";
  fout.setf(ios::fixed,ios::floatfield);
  TListIter iter(volumes);
  CbmGeoNode* volu;
  Bool_t rc=kTRUE;
  while((volu=(CbmGeoNode*)iter.Next())&&rc) {
    rc=volu->write(fout);
  }
}

Bool_t CbmGeoSet::create(CbmGeoBuilder* builder) {
  // Creates the geometry
  if (!builder) return kFALSE;
  TListIter iter(volumes);
  CbmGeoNode* volu;
  Bool_t rc=kTRUE;
  while((volu=(CbmGeoNode*)iter.Next())&&rc) {
    if (volu->isActive()) {

	if (hadesGeo == 1)   rc=builder->createNode(volu, hadesGeo);
        else rc=builder->createNode(volu) ;
      if (rc) {
        if (volu->isTopNode()||volu->isRefNode()) {
          CbmGeoNode* n=getMasterNode(volu->GetName());
          if (n) {
            n->setCenterPosition(volu->getCenterPosition());
            n->setRootVolume(volu->getRootVolume());
          }
        }
      } else Error("create","Creation of %s failed!",volu->GetName());
    }
  }
  return rc;
}

void CbmGeoSet::compare(CbmGeoSet& rset) {
  // Compares the geometry parameters and print a diagnose
  if (fName.CompareTo(rset.GetName())!=0) {
    Error("compare","Sets have different type");
    return;
  }
  TListIter iter(volumes);
  CbmGeoNode* volu;
  Int_t n=0, nnf=0, nDiff=0;
  cout<<"name\t mother medium shape  points    pos    rot\n";
  cout<<"------------------------------------------------\n";
  while((volu=(CbmGeoNode*)iter.Next())) {
    n++;
    CbmGeoNode* rNode=rset.getVolume(volu->GetName());
    if (!rNode) nnf++;
    else if (volu->compare(*rNode)>0) nDiff++;
  }
  cout<<"Number of volumes in first list:             "<<n<<'\n';
  cout<<"Number of different volumes:                 "<<nDiff<<endl;
  cout<<"Number of volumes not found in second list:  "<<nnf<<'\n';
  TList* rlist=rset.getListOfVolumes();
  if (rlist->GetSize()!=(n-nnf)) {
    nnf=0;
    TListIter riter(rlist);
    while((volu=(CbmGeoNode*)riter.Next())) {
      CbmGeoNode* rNode=getVolume(volu->GetName());
      if (!rNode) nnf++;
    }
  } else nnf=0;
  cout<<"Number of additional volumes in second list: "<<nnf<<'\n';
}
