#include "FairTutorialDetDigitizer.h"

#include "FairTutorialDetDigiPar.h"
#include "FairTutorialDetPoint.h"

#include "FairRootManager.h"
#include "FairMCTrack.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairBaseParSet.h"

#include "TRandom.h"
#include "TMath.h"
#include "TVector3.h"
#include "TClonesArray.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMaterial.h"
#include "TGeoNode.h"
#include "TGeoMatrix.h"
#include "TGeoBBox.h"

#include <iostream>
using std::cout;
using std::endl;

// ---- Default constructor -------------------------------------------
FairTutorialDetDigitizer::FairTutorialDetDigitizer()
  :FairTask("TutorialDetDigitizer")
  //:fRef(0)
{
  //    fDigiCollection = new TClonesArray("FairTrdDigi");
}
// --------------------------------------------------------------------

// ---- Constructor ----------------------------------------------------
FairTutorialDetDigitizer::FairTutorialDetDigitizer(const char* name, const char* title)
  :FairTask(name)
{

}
// --------------------------------------------------------------------

// ---- Destructor ----------------------------------------------------
FairTutorialDetDigitizer::~FairTutorialDetDigitizer()
{
  //    FairRootManager *ioman =FairRootManager::Instance();
  //ioman->Write();
  //fDigiCollection->Clear("C");
  //delete fDigiCollection;

}
// --------------------------------------------------------------------

// ----  Initialisation  ----------------------------------------------
void FairTutorialDetDigitizer::SetParContainers()
{
  cout<<" * FairTutorialDetDigitizer * :: SetParContainers() "<<endl;


  // Get Base Container
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = (FairTutorialDetDigiPar*)
             (rtdb->getContainer("FairTutorialDetDigiPar"));

  fDigiPar->printparams();
}
// --------------------------------------------------------------------

// ---- ReInit  -------------------------------------------------------
InitStatus FairTutorialDetDigitizer::ReInit()
{

  cout<<" * FairTutorialDetDigitizer * :: ReInit() "<<endl;


  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = (FairTutorialDetDigiPar*)
             (rtdb->getContainer("FairTutorialDetDigiPar"));

  return kSUCCESS;
}
// --------------------------------------------------------------------

// ---- Init ----------------------------------------------------------
InitStatus FairTutorialDetDigitizer::Init()
{

  cout<<" * FairTutorialDetDigitizer * :: Init() "<<endl;

  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) { Fatal("Init", "No FairRootManager"); }

  fTutorialDetPoints=(TClonesArray*)
                     ioman->GetObject("TutorialDetPoint");

  if ( ! fTutorialDetPoints ) {
    cout << "-W FairTutorialDetDigitizer::Init: No TutorialDetPoints array!" << endl;
    cout << "                            Task will be inactive" << endl;
    return kERROR;
  }

  //fListStack = (TClonesArray*)ioman->GetObject("MCTrack");
  //fDigiCollection = new TClonesArray("FairTrdDigi", 100);
  //ioman->Register("TRDDigi","TRD Digis",fDigiCollection,kTRUE);

  return kSUCCESS;

}
// --------------------------------------------------------------------


// ---- Exec ----------------------------------------------------------
void FairTutorialDetDigitizer::Exec(Option_t* option)
{

  // Here we print something

  cout <<" I am in FairTutorialDetDigitizer::Exec" << endl;

  /*

  fNHits = 0;
  FairTutorialDetPoint *pt=NULL;

  Int_t nentries = fTutorialDetPoints->GetEntriesFast();

  Double_t ELoss;       // total energy loss

  for (int j=0; j < nentries; j++ ) {

    pt = (FairTutorialDetPoint*) fTutorialDetPoints->At(j);

    if(NULL == pt) continue;

  //        Double_t x_mean = (pt->GetXIn()+pt->GetXOut())/2.;
  //        Double_t y_mean = (pt->GetYIn()+pt->GetYOut())/2.;
  //        Double_t z_mean = (pt->GetZIn()+pt->GetZOut())/2.;


        Double_t x_mean = pt->GetXOut();
        Double_t y_mean = pt->GetYOut();
        Double_t z_mean = pt->GetZOut();

        gGeoManager->FindNode(x_mean, y_mean, z_mean);
        TString path = gGeoManager->GetPath();
        Int_t ID =  gGeoManager->GetCurrentNodeId();

        TGeoNode *curnode = gGeoManager->GetCurrentNode();
        TGeoVolume *curvol = gGeoManager->GetCurrentVolume();
        TGeoMaterial *curmat =curvol->GetMedium()->GetMaterial();

        const Double_t *global_point = gGeoManager->GetCurrentPoint();
        Double_t local_point[3];  // global_point[3];

        gGeoManager->MasterToLocal(global_point, local_point);

        TGeoHMatrix *matrix = gGeoManager->GetCurrentMatrix();

        TGeoBBox *shape = (TGeoBBox*)curvol->GetShape();
        Float_t sizex = shape->GetDX();
        Float_t sizey = shape->GetDY();
        Float_t sizez = shape->GetDZ();

  //        cout <<"x_in: " << pt->GetXIn() << endl;
  // cout <<"x_mean: " << x_mean << endl;
        //cout <<"x_out: " << pt->GetXOut() << endl;

        //cout <<"y: " << y_mean << endl;

        //cout <<"z_in: " << pt->GetZIn() << endl;
        //cout <<"z_mean: " << z_mean << endl;
  //        cout <<"z_out: " << pt->GetZOut() << endl;


        if (matrix->IsRotation()){
          cout <<"Module is rotated" << endl;
  } else {
          cout <<"Module is not rotated" << endl;
  }


    }
  */
}
// --------------------------------------------------------------------

// --------------------------------------------------------------------

// ---- Finish --------------------------------------------------------
void FairTutorialDetDigitizer::Finish()
{
}
// --------------------------------------------------------------------

// ---- Register ------------------------------------------------------
void FairTutorialDetDigitizer::Register()
{

  //FairRootManager::Instance()->Register("TrdDigi","Trd Digi", fDigiCollection, kTRUE);

}
// --------------------------------------------------------------------

ClassImp(FairTutorialDetDigitizer)
