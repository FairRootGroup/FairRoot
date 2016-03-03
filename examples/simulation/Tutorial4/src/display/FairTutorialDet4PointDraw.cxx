// -------------------------------------------------------------------------
// -----                FairTutorialDet4PointDraw                      -----
// -----               Created 02.03.16 by F. Uhlig                    -----
// -------------------------------------------------------------------------

#include "FairTutorialDet4PointDraw.h"

#include "FairTutorialDet4GeoPar.h"
#include "FairTutorialDet4Point.h"
#include "FairTutorialDet4GeoHandler.h"

#include "FairEventManager.h"           // for FairEventManager
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRunAna
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairLogger.h"

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TEvePointSet.h"                 // for TEveBoxSet, etc
#include "TEveManager.h"                // for TEveManager, gEve
#include "TVector3.h"                   // for TVector3


// -----   Default constructor   -------------------------------------------
FairTutorialDet4PointDraw::FairTutorialDet4PointDraw()
  : FairTask("FairTutorialDet4PointDraw"),
    fPointList(NULL),
    fGeoPar(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(),
    fStyle(),
    fGlobalCoordinates(kTRUE),
    fGeoHandler(new FairTutorialDet4GeoHandler)
{
}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
FairTutorialDet4PointDraw::FairTutorialDet4PointDraw(const char* name,
						     Color_t color ,
						     Style_t mystyle)
  : FairTask(name),
    fPointList(NULL),
    fGeoPar(NULL),
    fEventManager(NULL),
    fq(NULL),
    fColor(color),
    fStyle(mystyle),
    fGlobalCoordinates(kTRUE),
    fGeoHandler(new FairTutorialDet4GeoHandler)
{
}

// ----  Initialisation  ----------------------------------------------
void FairTutorialDet4PointDraw::SetParContainers()
{
  // Get Base Container
  FairRun* run = FairRun::Instance();
  FairRuntimeDb* rtdb=run->GetRuntimeDb();

  fGeoPar = (FairTutorialDet4GeoPar*)(rtdb->getContainer("FairTutorialDet4GeoPar"));

}
// --------------------------------------------------------------------

// -------------------------------------------------------------------------
InitStatus FairTutorialDet4PointDraw::Init()
{
   FairRootManager* fManager = FairRootManager::Instance();
   fPointList = (TClonesArray *)fManager->GetObject(GetName());
   if(NULL==fPointList){
     LOG(ERROR) << "FairTutorialDet4PointDraw::Init()  branch " << GetName()
		<< " not found! Task will be deactivated."<< FairLogger::endl;
     return kERROR;
    }
   fEventManager = FairEventManager::Instance();
   fq =0;

   fGlobalCoordinates = fGeoPar->IsGlobalCoordinateSystem();

   return kSUCCESS;


}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void FairTutorialDet4PointDraw::Exec(Option_t* option)
{
  if (IsActive()){

    FairTutorialDet4Point *point=0;

    Int_t npoints=fPointList->GetEntriesFast();
    Reset();

    TEvePointSet* q = new TEvePointSet(GetName(), npoints,
				      TEvePointSelectorConsumer::kTVT_XYZ);
    q->SetOwnIds(kTRUE);
    q->SetMarkerColor(fColor);
    q->SetMarkerSize(1.5);
    q->SetMarkerStyle(fStyle);

    Int_t refCounter=0;

    for (Int_t i=0; i<npoints; ++i) {

      point = static_cast<FairTutorialDet4Point*>(fPointList->At(i));

      if(!point) { continue; }

      // Detector ID
      Int_t detID = point->GetDetectorID();

      // Determine hit position
      Double_t  x  = point->GetX();
      Double_t  y  = point->GetY();
      Double_t  z  = point->GetZ();

      if(!fGlobalCoordinates) {
        Double_t local[3] = {x, y, z};
        Double_t global[3];

        fGeoHandler->LocalToGlobal(local, global, detID);

        x = global[0];
	y = global[1];
	z = global[2];
      }
      q->SetNextPoint(x, y, z);
      //     q->SetPointId(GetValue(p, i));

    }
    gEve->AddElement(q);
    gEve->Redraw3D(kFALSE);
    fq=q;
  }
}

// -----   Destructor   ----------------------------------------------------
FairTutorialDet4PointDraw::~FairTutorialDet4PointDraw()
{
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void FairTutorialDet4PointDraw::Finish()
{
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void FairTutorialDet4PointDraw::Reset()
{
  if(fq){
    fq->Reset();
    gEve->RemoveElement(fq, fEventManager );
  }
}
