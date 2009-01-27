#include "CbmTutorialDetDigitizer.h"

#include "CbmTutorialDetDigiPar.h"
#include "CbmTutorialDetPoint.h"

#include "CbmRootManager.h"
#include "CbmMCTrack.h"
#include "CbmRunAna.h"
#include "CbmRuntimeDb.h"
#include "CbmBaseParSet.h"

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
CbmTutorialDetDigitizer::CbmTutorialDetDigitizer()
    :CbmTask("TutorialDetDigitizer")
	//:fRef(0)
{
  //    fDigiCollection = new TClonesArray("CbmTrdDigi");
}
// --------------------------------------------------------------------

// ---- Constructor ----------------------------------------------------
CbmTutorialDetDigitizer::CbmTutorialDetDigitizer(const char *name, const char *title)
	:CbmTask(name)
{

}
// --------------------------------------------------------------------

// ---- Destructor ----------------------------------------------------
CbmTutorialDetDigitizer::~CbmTutorialDetDigitizer()
{
  //    CbmRootManager *ioman =CbmRootManager::Instance();
  //ioman->Write();
  //fDigiCollection->Clear("C");
  //delete fDigiCollection;

}
// --------------------------------------------------------------------

// ----  Initialisation  ----------------------------------------------
void CbmTutorialDetDigitizer::SetParContainers()
{
    cout<<" * CbmTutorialDetDigitizer * :: SetParContainers() "<<endl;


    // Get Base Container
    CbmRunAna* ana = CbmRunAna::Instance();
    CbmRuntimeDb* rtdb=ana->GetRuntimeDb();

    fDigiPar = (CbmTutorialDetDigiPar*)
               (rtdb->getContainer("CbmTutorialDetDigiPar"));

    fDigiPar->printparams();
}
// --------------------------------------------------------------------

// ---- ReInit  -------------------------------------------------------
InitStatus CbmTutorialDetDigitizer::ReInit(){

  cout<<" * CbmTutorialDetDigitizer * :: ReInit() "<<endl;


  CbmRunAna* ana = CbmRunAna::Instance();
  CbmRuntimeDb* rtdb=ana->GetRuntimeDb();

  fDigiPar = (CbmTutorialDetDigiPar*)
    (rtdb->getContainer("CbmTutorialDetDigiPar"));
  
  return kSUCCESS;
}
// --------------------------------------------------------------------

// ---- Init ----------------------------------------------------------
InitStatus CbmTutorialDetDigitizer::Init()
{

    cout<<" * CbmTutorialDetDigitizer * :: Init() "<<endl;

    CbmRootManager *ioman = CbmRootManager::Instance();
    if ( ! ioman ) Fatal("Init", "No CbmRootManager");
    
    fTutorialDetPoints=(TClonesArray *)  
      ioman->ActivateBranch("TutorialDetPoint");
 
    if ( ! fTutorialDetPoints ) {
      cout << "-W CbmTutorialDetDigitizer::Init: No TutorialDetPoints array!" << endl;
      cout << "                            Task will be inactive" << endl;
      return kERROR;
    }

    //fListStack = (TClonesArray*)ioman->ActivateBranch("MCTrack");
    //fDigiCollection = new TClonesArray("CbmTrdDigi", 100);
    //ioman->Register("TRDDigi","TRD Digis",fDigiCollection,kTRUE);

    return kSUCCESS;

}
// --------------------------------------------------------------------


// ---- Exec ----------------------------------------------------------
void CbmTutorialDetDigitizer::Exec(Option_t * option)
{

  // Here we print something

  cout <<" I am in CbmTutorialDetDigitizer::Exec" << endl;

  /*
    
  fNHits = 0;
  CbmTutorialDetPoint *pt=NULL;
  
  Int_t nentries = fTutorialDetPoints->GetEntriesFast();
  
  Double_t ELoss;       // total energy loss
  
  for (int j=0; j < nentries; j++ ) {
  
    pt = (CbmTutorialDetPoint*) fTutorialDetPoints->At(j);
  
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
void CbmTutorialDetDigitizer::Finish()
{
}
// --------------------------------------------------------------------

// ---- Register ------------------------------------------------------
void CbmTutorialDetDigitizer::Register(){

  //CbmRootManager::Instance()->Register("TrdDigi","Trd Digi", fDigiCollection, kTRUE);

}
// --------------------------------------------------------------------

ClassImp(CbmTutorialDetDigitizer)
