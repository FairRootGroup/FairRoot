//*-- Authors: Ilse Koenig & Denis Bertini
//*--Modified 21/05/2005 Denis Bertini
#include "CbmGeoG3Builder.h"

#include "CbmGeoMedium.h"
#include "CbmGeoNode.h"
#include "CbmGeoTransform.h"

#include "TGeoManager.h"
#include "TGeoMedium.h"
#include "TGeoMaterial.h"
#include "TGeoVolume.h"
#include "TGeoMatrix.h"
#include "TGeoPgon.h"
#include "TGeoPcon.h"
#include "TVirtualMC.h"
#include "TRandom.h"
#include "TGeant3.h"
#include "TArrayD.h"

#include <iostream>

using std::cout;
using std::endl;

ClassImp(CbmG3MapedNames)
ClassImp(CbmGeoG3Builder)

TMap CbmG3MapedNames::fVolumeMap;
TMap CbmG3MapedNames::fMediumMap;

void CbmG3MapedNames::saveVolumeName( const char* tname, const char* vname){
fVolumeMap.Add(new TNamed(vname,vname) , new TNamed(tname,tname));

cout << " -I- saveVolumeName:" << vname << ":" << tname << " size: "
     << fVolumeMap.GetSize() <<  endl;

}

void CbmG3MapedNames::saveMediumName( const char* tname, const char* vname){
fMediumMap.Add(new TNamed(vname,vname) , new TNamed(tname,tname));
cout << " -I- saveMediumName:" << vname <<":" << tname << " size: "
     << fMediumMap.GetSize() <<  endl;

}

const char* CbmG3MapedNames::getTruncVolName( const char *vname){
    TNamed *fObj=NULL;
    TPair* pObj =  dynamic_cast<TPair*> (fVolumeMap.FindObject( vname ));
    if ( pObj ) {
     fObj = dynamic_cast<TNamed*> (pObj->Value());
     cout << " -I   : " << vname << ":"
           << fObj->GetName()  << endl;
     return fObj->GetName();
    }else {
     cout << " -E  getTruncVolName : " << vname << " not found " << endl;
     return NULL;
    }

}

const char* CbmG3MapedNames::getTruncMedName( const char *vname){

    TNamed *fObj=NULL;
    TPair* pObj =  dynamic_cast<TPair*> (fMediumMap.FindObject( vname ));
    if ( pObj ) {
     fObj = dynamic_cast<TNamed*> (pObj->Value());
     cout << " -I  getTruncMedName : " << vname << ":"
           << fObj->GetName()  << endl;
     return fObj->GetName();
    }else {
     cout << " -E  getTruncMedName : " << vname << " not found " << endl;
     return NULL;
    }
}
void  CbmG3MapedNames:: listVolumes() {
    TNamed* fKey=NULL;
    TNamed* fVal=NULL;
    TMapIter next ( &fVolumeMap);
    while ( (fKey = dynamic_cast<TNamed*> (next())) ){
            fVal = (TNamed*) fVolumeMap.GetValue(fKey);
            cout << " key: " << fKey->GetName()
                << " value: " << fVal->GetName() << endl;
    }
}

void  CbmG3MapedNames:: listMedium() {
    TNamed* fKey=NULL;
    TNamed* fVal=NULL;
    TMapIter next ( &fMediumMap);
    while ( (fKey = dynamic_cast<TNamed*> (next()) )){
            fVal = (TNamed*) fMediumMap.GetValue(fKey);
            cout << " key: " << fKey->GetName()
                << " value: " << fVal->GetName() << endl;
    }

}

const char*  CbmG3MapedNames::getVolRealName(const char* tname) {
    TNamed* fKey=NULL;
    TNamed* fVal=NULL;
    TMapIter next ( &fVolumeMap);
    while ( (fKey = dynamic_cast<TNamed*> (next())) ){
           fVal = (TNamed*) fVolumeMap.GetValue(fKey);

           if (strcmp(fVal->GetName(), tname ) == 0){
               cout << "-I- real name: " << fKey->GetName() << endl;
               return   fKey->GetName();
     }
   }
 return NULL;
}

const char*  CbmG3MapedNames::getMedRealName(const char* tname) {
    TNamed* fKey=NULL;
    TNamed* fVal=NULL;
    TMapIter next ( &fMediumMap);
    while ( (fKey = dynamic_cast<TNamed*> (next())) ){
        if (strcmp(fKey->GetName(), tname ) == 0){
               fVal = (TNamed*) fMediumMap.GetValue(fKey);
                return   fVal->GetName();
     }
   }
 return NULL;
}


//--------------------------------------------------------------------------

CbmGeoG3Builder::CbmGeoG3Builder() {
  // Default constructor
  gMC3 = (TGeant3*) gMC;
  fDebug=kTRUE;
  fCountVolume=0;
  fCountMedium=0;
  fMapedNames = new CbmG3MapedNames();
}

CbmGeoG3Builder::CbmGeoG3Builder(const char* name,const char* title)
               : CbmGeoBuilder(name,title) {
  // Constructor
  gMC3 = (TGeant3*) gMC;
  fDebug=kTRUE;
  fCountVolume=0;
  fCountMedium=0;
  fMapedNames = new CbmG3MapedNames();

}

Bool_t CbmGeoG3Builder::createNode(CbmGeoNode* volu, Int_t hadFormat) {

  if (!gMC3 ) gMC3 = (TGeant3*) gMC;
  fCountVolume++;

  // Creates the volume
  if (!volu) return kFALSE;
  TString nodeName= volu->GetName();
  const char* tname = NULL;

  if(fDebug)
      cout << " -I Full NodeName: " << nodeName << " copy no: "
       << volu->getCopyNo() << endl;

  if ( hadFormat == 1 ) {
  	volu->setHadFormat( hadFormat );
	nodeName=nodeName(0,4);
  } else {
  	nodeName = (volu->GetName());
  	Ssiz_t l=nodeName.Last('#');
  	if (l>0) nodeName=nodeName(0,l);
  }

  CbmGeoNode* mother=volu->getMotherNode();
  if (!mother&&!volu->isTopNode()) {
    Error("createNode","Mother volume of %s not found\n",volu->GetName());
    return kFALSE;
  }

  CbmGeoNode* cv=volu->getCopyNode();
  if (cv && fDebug){
          cout <<"Copy of: "<<cv->GetName()
          << " Copy No: " << cv->getCopyNo() <<endl;
     tname = fMapedNames->getTruncVolName(nodeName);
     cout << " Copy: NodeName " << nodeName
           << " truncated: " << tname << endl;

      volu->setTruncName ( tname );

  }else{
    // truncate names
    tname = truncateName( fCountVolume );
    fMapedNames->saveVolumeName(tname, nodeName);
    volu->setTruncName( tname );
  }

  if ( (!cv) || (!cv->isCreated()) ) {
    CbmGeoMedium* medium=volu->getMedium();
    Int_t nMed=medium->getMediumIndex();
    if (nMed<=0) nMed=createMedium(medium);
    if (nMed<=0) return kFALSE;
    TArrayD* dPar=volu->getParameters();
    // transform to float
    Int_t nPar=dPar->GetSize();
    Float_t* fPar=new Float_t[nPar];
//    Int_t ivolu;
    for (Int_t i=0;i<nPar;i++) fPar[i]=(Float_t)(dPar->At(i));

    cout << "-I- GSVOLU: creates " << nodeName << "trunc: " << tname << endl;
    gMC3->Gsvolu( tname ,
 		(const char*)volu->getShape().Data(),
 		 nMed,fPar,nPar);

    if (fDebug) {
      cout <<"GSVOLU: "<<nodeName<<" "<< tname << " " << volu->getShape()<<" "<<nMed;
      for (Int_t i=0;i<nPar;i++) cout<<" "<<fPar[i];
      cout <<'\n';
    }
    delete [] fPar;
    volu->setCreated();
    if (cv) cv->setCreated();
 //   if (volu->isModule()&&cv) {
 //     cv->setCreated();
 //     cv->getPosition();
 //   }
  }
  if (!volu->isTopNode()) {

   //  fMapedNames->listVolumes();
 
    char cTmp[]="ONLY";
    CbmGeoTransform* trans=volu->getPosition();
    const CbmGeoRotation& rot=trans->getRotMatrix();
    const CbmGeoVector& pos=trans->getTransVector();
    Int_t nR=0;

    if (!((CbmGeoRotation&)rot).isUnitMatrix()) {
      Float_t rowmat[3], theta[3], phi[3], sinth, costh, sinph, cosph;
      Int_t rotate;
      const Double_t deg2rad=TMath::DegToRad();
      for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) rowmat[j]=rot(i+j*3);
        gMC3->Gfang(rowmat,costh,sinth,cosph,sinph,rotate);
        theta[i]=(float)(atan2((sinth*deg2rad),(costh*deg2rad))/deg2rad);
        if (theta[i]<0.0F) theta[i]+=180.0F;
        theta[i]=((int)(theta[i]*1000.F+0.5F))/1000.F;
        phi[i]=(float)(atan2((sinph*deg2rad),(cosph*deg2rad))/deg2rad);
        if (phi[i]<0.0F) phi[i]+=360.0F;
        phi[i]=((int)(phi[i]*1000.F+0.5F))/1000.F;
      }
      nR=++nRot;
      gMC3->Gsrotm(nR,theta[0],phi[0],theta[1],phi[1],theta[2],phi[2]);
      if (fDebug) {
         cout<<"GSROTM: "<<nR<<" "<<theta[0]<<" "<<phi[0]<<" "<<theta[1]
                  <<" "<<phi[1]<<" "<<theta[2]<<" "<<phi[2]<<'\n';
      }
    }
    //truncate  mName
    TString mName = volu->getMother();

   
    if ( hadFormat == 1 ) {
    	mName=mName(0,4);
    }else {
        Ssiz_t l=mName.Last('#');
    	if(l>0)mName=mName(0,l);
    }
    
    const char * mTname = fMapedNames->getTruncVolName(mName.Data() );
    cout << "-I- Gspos: Mother " << tname << ": "
         << volu->getMother().Data() << ":" << mTname  << endl;

      if (fDebug) {
        cout  <<"GSPOS: "<<nodeName<<" "<< tname << " "
              << volu->getCopyNo()<<" "<<volu->getMother()
              <<" "<<(Float_t)pos.getX()
              <<" "<<(Float_t)pos.getY()<<" "
              <<(Float_t)pos.getZ()<<" "<<nR<<'\n';
      }

      gMC3->Gspos( tname ,volu->getCopyNo(), mTname,
          (Float_t)pos.getX(),(Float_t)pos.getY(),(Float_t)pos.getZ(),nR,cTmp);

  }
  return kTRUE;
}

Int_t CbmGeoG3Builder::createMedium(CbmGeoMedium* med) {
   if (!gMC3 ) gMC3 = (TGeant3*) gMC;
  fCountMedium++;

   // Creates the medium
  if (!med) return 0;
  Int_t nComp=med->getNComponents();
  Int_t nCompW=nComp*med->getWeightFac();
  Double_t p[3];
  const char* tname = NULL;
  tname = truncateName( fCountMedium );
  fMapedNames->saveMediumName(tname,med->GetName());

  if (nComp==1) {
      med->getComponent(0,p);
      gMC3->Gsmate(++nMed, tname ,(Float_t)p[0],(Float_t)p[1],
           (Float_t)med->getDensity(),(Float_t)med->getRadiationLength(),
                 -1.);

  } else {
    Float_t* a=new Float_t[nComp];
    Float_t* z=new Float_t[nComp];
    Float_t* w=new Float_t[nComp];
    for(Int_t i=0;i<nComp;i++) {
      med->getComponent(i,p);
      a[i]=(Float_t)p[0];
      z[i]=(Float_t)p[1];
      w[i]=(Float_t)p[2];
    }
    gMC3->Gsmixt(++nMed, tname ,a,z,med->getDensity(),nCompW,w);
    delete [] a;
    delete [] z;
    delete [] w;
  }
  Double_t mp[10];
  med->getMediumPar(mp);
  gMC3->Gstmed(nMed, tname ,nMed,(int)mp[0],(int)mp[1],(float)mp[2],
         (float)mp[3],(float)mp[4],(float)mp[5],(float)mp[6],
               (float)mp[7]);
  med->setMediumIndex(nMed);
  // Optical properties
  Int_t nPckov=med->getNpckov();
  if (nPckov>0) {
      if (fDebug ) cout << " -I- Optical properties set for Medium: "
          << med->GetName() << "nMed" << nMed << ":" << med->getMediumIndex() << endl;
    Double_t pc[4];
    Float_t* ppckov=new Float_t[nPckov];
    Float_t* absco=new Float_t[nPckov];
    Float_t* effic=new Float_t[nPckov];
    Float_t* rindex=new Float_t[nPckov];
    for(Int_t i=0;i<nPckov;i++) {
      med->getCerenkovPar(i,pc);
      ppckov[i]=(Float_t)pc[0]*1.e-9;
      absco[i]=(Float_t)pc[1];
      effic[i]=(Float_t)pc[2];
      rindex[i]=(Float_t)pc[3];
    }
     gMC3->Gsckov(nMed,nPckov,ppckov,absco,effic,rindex);
     gMC->SetCerenkov(nMed,nPckov,ppckov,absco,effic,rindex);
    delete [] ppckov;
    delete [] absco;
    delete [] effic;
    delete [] rindex;
  }

  return nMed;
}

const char* CbmGeoG3Builder::truncateName( Int_t id ){

 int pos1=0, pos2=0, pos3=0, pos4=0;
 char* tName = new  char[4];
 char cbuf[] = {'0','1','2','3','4','5','6',
                 '7','8','9','A','B','C','D',
                 'E','F','G','H','I','J','K',
                 'L','M','N','O','P','Q','R',
                 'S','T','U','V','W','X','Y',
                 'Z'};
  
 /*
  pos4 = ( id / (46656) ) ;
  pos3 = ( id / (1296) ) - (pos4 * 36);
  pos2 = ( id / (36)) - (pos3 * 36 ) - (pos4 * 1296);
  pos1 = ( id % 36 );
  */
  pos4 = (Int_t) ( gRandom->Rndm() *36);
  pos3 = (Int_t) ( gRandom->Rndm() *36);
  pos2 = (Int_t) ( gRandom->Rndm() *36);
  pos1 = (Int_t) ( gRandom->Rndm() *36);

  sprintf(tName,"%c%c%c%c",cbuf[pos4],cbuf[pos3],cbuf[pos2],cbuf[pos1]);
  if (fDebug) cout << " -I-  CbmGeoG3Builder G3 truncated name created " << tName << endl;
  return tName;
}

