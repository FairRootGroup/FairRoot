//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// PndGeoCave
//
// Class for the geometry of the detector part CAVE
//
/////////////////////////////////////////////////////////////

#include "PndGeoCave.h"
#include "CbmGeoNode.h"
#include "CbmGeoShapes.h"
#include "CbmGeoBasicShape.h"
#include "CbmGeoMedium.h"

using namespace std;
ClassImp(PndGeoCave)

PndGeoCave::PndGeoCave() {
  // Constructor
  fName="cave";
  name="cave";
  maxModules=1;
}

Bool_t PndGeoCave::read(fstream& fin,CbmGeoMedia* media) {
  // Reads the geometry from file
  if (!media) return kFALSE;
  const Int_t maxbuf=256;
  char buf[maxbuf];
  CbmGeoNode* volu=0;
  CbmGeoMedium* medium;
  Bool_t rc=kTRUE;
  do {
    fin.getline(buf,maxbuf);
    if (buf[0]!='\0' && buf[0]!='/' && !fin.eof()) {
      if (strcmp(buf,name)==0) {
        volu=new CbmGeoNode;
        volu->SetName(buf);
        volu->setVolumeType(kCbmGeoTopNode);
        volu->setActive();
        fin.getline(buf,maxbuf);
        TString shape(buf);
        CbmGeoBasicShape* sh=pShapes->selectShape(shape);
        if (sh) volu->setShape(sh);
        else rc=kFALSE;
        fin.getline(buf,maxbuf);
        medium=media->getMedium(buf);
        if (!medium) {
          medium=new CbmGeoMedium();
          media->addMedium(medium);
        }
        volu->setMedium(medium);
        Int_t n=0;
        if (sh) n=sh->readPoints(&fin,volu);
        if (n<=0) rc=kFALSE;
      } else rc=kFALSE;
    }
  } while (rc && !volu && !fin.eof()); 
  if (volu && rc) {
    volumes->Add(volu);
    masterNodes->Add(new CbmGeoNode(*volu));
  } else {
    delete volu;
    volu=0;
    rc=kFALSE;
  }
  return rc;
}

void PndGeoCave::addRefNodes() {
  // Adds the reference node
  CbmGeoNode* volu=getVolume(name);
  if (volu) masterNodes->Add(new CbmGeoNode(*volu));
}

void PndGeoCave::write(fstream& fout) {
  // Writes the geometry to file
  fout.setf(ios::fixed,ios::floatfield);
  CbmGeoNode* volu=getVolume(name);
  if (volu) {
    CbmGeoBasicShape* sh=volu->getShapePointer();
    CbmGeoMedium* med=volu->getMedium();
    if (sh&&med) {
      fout<<volu->GetName()<<'\n'<<sh->GetName()<<'\n'<<med->GetName()<<'\n';
      sh->writePoints(&fout,volu);
    }
  }
}

void PndGeoCave::print() {
  // Prints the geometry
  CbmGeoNode* volu=getVolume(name);
  if (volu) {
    CbmGeoBasicShape* sh=volu->getShapePointer();
    CbmGeoMedium* med=volu->getMedium();
    if (sh&&med) {
      cout<<volu->GetName()<<'\n'<<sh->GetName()<<'\n'<<med->GetName()<<'\n';
      sh->printPoints(volu);
    }
  }
}
