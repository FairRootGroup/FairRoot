/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2Digitizer.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairTutorialDet2DigiPar.h"
#include "FairTutorialDet2Point.h"

#include <TClonesArray.h>

FairTutorialDet2Digitizer::FairTutorialDet2Digitizer()
    : FairTask("TutorialDetDigitizer", 0)
    , fTutorialDetPoints(nullptr)
    , fCustomData2(new std::vector<CustomClass>)
    , fDigiPar(nullptr)
{}

FairTutorialDet2Digitizer::FairTutorialDet2Digitizer(const char* name, const char* /*title*/)
    : FairTask(name, 0)
    , fTutorialDetPoints(nullptr)
    , fCustomData2(new std::vector<CustomClass>)
    , fDigiPar(nullptr)
{}

FairTutorialDet2Digitizer::~FairTutorialDet2Digitizer()
{
    // fDigiCollection->Clear("C");
    // delete fDigiCollection;
}

void FairTutorialDet2Digitizer::SetParContainers()
{
    LOG(debug) << "FairTutorialDet2Digitizer :: SetParContainers() ";

    // Get Base Container
    FairRunAna* ana = FairRunAna::Instance();
    FairRuntimeDb* rtdb = ana->GetRuntimeDb();

    fDigiPar = static_cast<FairTutorialDet2DigiPar*>(rtdb->getContainer("FairTutorialDet2DigiPar"));

    // parameters are not filled yet
    fDigiPar->printparams();
}

InitStatus FairTutorialDet2Digitizer::ReInit()
{
    LOG(info) << " FairTutorialDet2Digitizer :: ReInit() ";

    FairRunAna* ana = FairRunAna::Instance();
    FairRuntimeDb* rtdb = ana->GetRuntimeDb();

    fDigiPar = static_cast<FairTutorialDet2DigiPar*>(rtdb->getContainer("FairTutorialDet2DigiPar"));

    return kSUCCESS;
}

InitStatus FairTutorialDet2Digitizer::Init()
{
    LOG(debug) << " FairTutorialDet2Digitizer :: Init() ";

    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(fatal) << "No FairRootManager";
        return kERROR;
    } else {
        fTutorialDetPoints = static_cast<TClonesArray*>(ioman->GetObject("TutorialDetPoint"));
        if (!fTutorialDetPoints) {
            LOG(error) << "No TutorialDetPoints array!";
            LOG(error) << "Task will be inactive";
            LOG(info) << " Task FairTutorialDet2Digitizer will be inactive, No TutorialDetPoints";
            return kERROR;
        }

        fCustomData = ioman->InitObjectAs<std::vector<CustomClass> const*>("TutorialCustomData");
        if (!fCustomData) {
            LOG(error) << "Custom Data cannot be created!";
            LOG(error) << "Task will be inactive";
            LOG(info) << " Task FairTutorialDet2Digitizer will be inactive, No Custom Data Vector";
            return kERROR;
        }

        // fListStack = (TClonesArray*)ioman->GetObject("MCTrack");
        // fDigiCollection = new TClonesArray("FairTrdDigi", 100);
        // ioman->Register("TRDDigi","TRD Digis",fDigiCollection,kTRUE);

        // now parameters are filled
        // fDigiPar->printparams();

        // register data output of this task
        Register();

        return kSUCCESS;
    }
}

void FairTutorialDet2Digitizer::Exec(Option_t* /*option*/)
{
    // Here we print something

    LOG(debug) << " I am in FairTutorialDet2Digitizer::Exec";

    LOG(debug) << " The custom data input vector has size" << fCustomData->size() << "\n";

    for (auto& entry : *fCustomData) {
        LOG(debug) << " Got entry " << entry.GetX() << " " << entry.GetQ() << "\n";
        // process data and fill a structure here, which can be consumed by the next task
        fCustomData2->emplace_back(entry.GetX() * 2, entry.GetQ() * 10);
    }

    /*

  fNHits = 0;
  FairTutorialDet2Point *pt=nullptr;

  Int_t nentries = fTutorialDetPoints->GetEntriesFast();

  Double_t ELoss;       // total energy loss

  for (int j=0; j < nentries; j++) {

    pt = (FairTutorialDet2Point*) fTutorialDetPoints->At(j);

    if(nullptr == pt) continue;

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

  //        LOG(info) <<"x_in: " << pt->GetXIn();
  // LOG(info) <<"x_mean: " << x_mean;
        //LOG(info) <<"x_out: " << pt->GetXOut();

        //LOG(info) <<"y: " << y_mean;

        //LOG(info) <<"z_in: " << pt->GetZIn();
        //LOG(info) <<"z_mean: " << z_mean;
  //        LOG(info) <<"z_out: " << pt->GetZOut();


        if (matrix->IsRotation()){
          LOG(info) <<"Module is rotated";
  } else {
          LOG(info) <<"Module is not rotated";
  }


    }
  */
}

void FairTutorialDet2Digitizer::Finish() {}

void FairTutorialDet2Digitizer::Register()
{
    // testing to transfer a variable to another task via a memory branch
    LOG(info) << "Digitizer::Register\n";
    FairRootManager::Instance()->RegisterAny("InMemory1", fCustomData2, false);
}
