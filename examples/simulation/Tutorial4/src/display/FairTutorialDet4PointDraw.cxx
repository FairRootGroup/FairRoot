// -------------------------------------------------------------------------
// -----                FairTutorialDet4PointDraw                      -----
// -----               Created 02.03.16 by F. Uhlig                    -----
// -------------------------------------------------------------------------

#include "FairTutorialDet4PointDraw.h"

#include "FairEventManager.h"   // for FairEventManager
#include "FairLogger.h"
#include "FairRootManager.h"   // for FairRootManager
#include "FairRun.h"           // for FairRunAna
#include "FairRuntimeDb.h"     // for FairRuntimeDb
#include "FairTutorialDet4GeoHandler.h"
#include "FairTutorialDet4GeoPar.h"
#include "FairTutorialDet4Point.h"

#include <TClonesArray.h>   // for TClonesArray
#include <TEveManager.h>    // for TEveManager, gEve
#include <TEvePointSet.h>   // for TEveBoxSet, etc

FairTutorialDet4PointDraw::FairTutorialDet4PointDraw()
    : FairTask("FairTutorialDet4PointDraw")
    , fPointList(nullptr)
    , fGeoPar(nullptr)
    , fEventManager(nullptr)
    , fq(nullptr)
    , fColor()
    , fStyle()
    , fGlobalCoordinates(kTRUE)
    , fGeoHandler(new FairTutorialDet4GeoHandler)
{}

FairTutorialDet4PointDraw::FairTutorialDet4PointDraw(const char* name, Color_t color, Style_t mystyle)
    : FairTask(name)
    , fPointList(nullptr)
    , fGeoPar(nullptr)
    , fEventManager(nullptr)
    , fq(nullptr)
    , fColor(color)
    , fStyle(mystyle)
    , fGlobalCoordinates(kTRUE)
    , fGeoHandler(new FairTutorialDet4GeoHandler)
{}

void FairTutorialDet4PointDraw::SetParContainers()
{
    // Get Base Container
    FairRun* run = FairRun::Instance();
    FairRuntimeDb* rtdb = run->GetRuntimeDb();

    fGeoPar = static_cast<FairTutorialDet4GeoPar*>(rtdb->getContainer("FairTutorialDet4GeoPar"));
}

InitStatus FairTutorialDet4PointDraw::Init()
{
    FairRootManager* fManager = FairRootManager::Instance();
    fPointList = static_cast<TClonesArray*>(fManager->GetObject(GetName()));
    if (nullptr == fPointList) {
        LOG(error) << "FairTutorialDet4PointDraw::Init()  branch " << GetName()
                   << " not found! Task will be deactivated.";
        return kERROR;
    }
    fEventManager = FairEventManager::Instance();
    fq = 0;

    fGlobalCoordinates = fGeoPar->IsGlobalCoordinateSystem();

    return kSUCCESS;
}

void FairTutorialDet4PointDraw::Exec(Option_t* /*option*/)
{
    if (IsActive()) {
        FairTutorialDet4Point* point = 0;

        Int_t npoints = fPointList->GetEntriesFast();
        Reset();

        TEvePointSet* q = new TEvePointSet(GetName(), npoints, TEvePointSelectorConsumer::kTVT_XYZ);
        q->SetOwnIds(kTRUE);
        q->SetMarkerColor(fColor);
        q->SetMarkerSize(1.5);
        q->SetMarkerStyle(fStyle);

        // Int_t refCounter=0;

        for (Int_t i = 0; i < npoints; ++i) {
            point = static_cast<FairTutorialDet4Point*>(fPointList->At(i));

            if (!point) {
                continue;
            }

            // Detector ID
            Int_t detID = point->GetDetectorID();

            // Determine hit position
            Double_t x = point->GetX();
            Double_t y = point->GetY();
            Double_t z = point->GetZ();

            if (!fGlobalCoordinates) {
                Double_t local[3] = {x, y, z};
                Double_t global[3];

                fGeoHandler->LocalToGlobal(local, global, detID);

                x = global[0];
                y = global[1];
                z = global[2];
            }
            q->SetNextPoint(x, y, z);
            // q->SetPointId(GetValue(p, i));
        }

        gEve->AddElement(q);
        gEve->Redraw3D(kFALSE);
        fq = q;
    }
}

void FairTutorialDet4PointDraw::Reset()
{
    if (fq) {
        fq->Reset();
        gEve->RemoveElement(fq, fEventManager);
    }
}
