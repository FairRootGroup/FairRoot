//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// FairGeoCave
//
// Class for the geometry of the detector part CAVE
//
/////////////////////////////////////////////////////////////

#include "FairGeoCave.h"
#include "FairGeoNode.h"
#include "FairGeoShapes.h"
#include "FairGeoBasicShape.h"
#include "FairGeoMedium.h"

using namespace std;
ClassImp(FairGeoCave)

FairGeoCave::FairGeoCave()
  : FairGeoSet(),
    name("cave")
{
  // Constructor
  fName="cave";
  name="cave";
  maxModules=1;
}

Bool_t FairGeoCave::read(fstream& fin,FairGeoMedia* media)
{
  // Reads the geometry from file
  if (!media) { return kFALSE; }
  const Int_t maxbuf=256;
  char buf[maxbuf];
  FairGeoNode* volu=0;
  FairGeoMedium* medium;
  Bool_t rc=kTRUE;
  do {
    fin.getline(buf,maxbuf);
    if (buf[0]!='\0' && buf[0]!='/' && !fin.eof()) {
      if (strcmp(buf,name)==0) {
        volu=new FairGeoNode;
        volu->SetName(buf);
        volu->setVolumeType(kFairGeoTopNode);
        volu->setActive();
        fin.getline(buf,maxbuf);
        TString shape(buf);
        FairGeoBasicShape* sh=pShapes->selectShape(shape);
        if (sh) { volu->setShape(sh); }
        else { rc=kFALSE; }
        fin.getline(buf,maxbuf);
        medium=media->getMedium(buf);
        if (!medium) {
          medium=new FairGeoMedium();
          media->addMedium(medium);
        }
        volu->setMedium(medium);
        Int_t n=0;
        if (sh) { n=sh->readPoints(&fin,volu); }
        if (n<=0) { rc=kFALSE; }
      } else { rc=kFALSE; }
    }
  } while (rc && !volu && !fin.eof());
  if (volu && rc) {
    volumes->Add(volu);
    masterNodes->Add(new FairGeoNode(*volu));
  } else {
    delete volu;
    volu=0;
    rc=kFALSE;
  }
  return rc;
}

void FairGeoCave::addRefNodes()
{
  // Adds the reference node
  FairGeoNode* volu=getVolume(name);
  if (volu) { masterNodes->Add(new FairGeoNode(*volu)); }
}

void FairGeoCave::write(fstream& fout)
{
  // Writes the geometry to file
  fout.setf(ios::fixed,ios::floatfield);
  FairGeoNode* volu=getVolume(name);
  if (volu) {
    FairGeoBasicShape* sh=volu->getShapePointer();
    FairGeoMedium* med=volu->getMedium();
    if (sh&&med) {
      fout<<volu->GetName()<<'\n'<<sh->GetName()<<'\n'<<med->GetName()<<'\n';
      sh->writePoints(&fout,volu);
    }
  }
}

void FairGeoCave::print()
{
  // Prints the geometry
  FairGeoNode* volu=getVolume(name);
  if (volu) {
    FairGeoBasicShape* sh=volu->getShapePointer();
    FairGeoMedium* med=volu->getMedium();
    if (sh&&med) {
      cout<<volu->GetName()<<'\n'<<sh->GetName()<<'\n'<<med->GetName()<<'\n';
      sh->printPoints(volu);
    }
  }
}
