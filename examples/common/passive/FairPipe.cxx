/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* Generated by Together */
#include "FairPipe.h"

#include "FairGeoBuilder.h"             // for FairGeoBuilder
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoMedia.h"               // for FairGeoMedia
#include "FairGeoPassivePar.h"          // for FairGeoPassivePar
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "TGeoCompositeShape.h"         // for TGeoCompositeShape
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoMatrix.h"                 // for TGeoRotation
#include "TGeoPcon.h"                   // for TGeoPcon
#include "TGeoVolume.h"                 // for TGeoVolume, etc

class FairGeoMedium;

FairPipe::~FairPipe()
{
}

FairPipe::FairPipe()
  : FairModule("FairPipe", "")
{
}

FairPipe::FairPipe(const char* name, const char* title)
  : FairModule(name ,title)
{
}

FairPipe::FairPipe(const FairPipe& rhs)
 : FairModule(rhs)
{
}

void FairPipe::ConstructGeometry()
{

/*
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= fRun->GetRuntimeDb();
  FairGeoPassivePar* par=(FairGeoPassivePar*)(rtdb->getContainer("FairGeoPassivePar"));
*/

  FairGeoLoader* loader=FairGeoLoader::Instance();
  FairGeoInterface* GeoInterface =loader->getGeoInterface();
  FairGeoMedia* Media =  GeoInterface->getMedia();
  FairGeoBuilder* geobuild = loader->getGeoBuilder();

  // Call materials
  FairGeoMedium* medVacuum  = Media->getMedium("vacuum");
  FairGeoMedium* medSteel   = Media->getMedium("steel");
  FairGeoMedium* medAlBe    = Media->getMedium("Al+Be");

/*
  Int_t nMedVacuum = geobuild->createMedium(medVacuum);
  Int_t nMedSteel  = geobuild->createMedium(medSteel);
  Int_t nMedAlBe   = geobuild->createMedium(medAlBe);
*/
  geobuild->createMedium(medVacuum);
  geobuild->createMedium(medSteel);
  geobuild->createMedium(medAlBe);

  Double_t parPipeLeft[9] = { 0., 360., 2,
                              -200.,  7.9, 8.,
                              -32.,  7.9, 8.
                            };

  // The central part is totally filled because of the crossing operations
  Double_t parPipeCentral[12] = {    0., 360., 3,
                                     -32., 0.,   8.,
                                     -2., 0.,    .9,
                                     20., 0.,    .9
                                };

  Double_t parPipeRight[18] = { 0., 360., 5,
                                20.,  .8873, .9,
                                22., 2.073, 2.1,
                                120., 2.05,  2.1,
                                300.1, 2.85,  2.9,
                                1050., 5.4,   5.5
                              };

  Double_t parPipeVacuumLeft[9] = { 0., 360., 2,
                                    -200.,  0., 7.9,
                                    -32.,  0., 7.9
                                  };

  Double_t parPipeVacuumCentral[12] = {    0., 360., 3,
                                      -32., 0.,   7.9,
                                      -2., 0.,    .873,
                                      20., 0.,    .873
                                      };

  Double_t parPipeVacuumRight[18] = { 0., 360., 5,
                                      20., 0.,  .873,
                                      22., 0., 2.073,
                                      120., 0., 2.05,
                                      300.1, 0., 2.85,
                                      1050., 0., 5.4
                                    };


  Double_t parPipeTargetDown[27] = { 0., 360., 8,
                                     -215., 17.4,  17.5,
                                     -183., 17.4,  17.5,
                                     -173., 4.5,   4.6,
                                     -96., 4.5,   4.6,
                                     -95., 2.4,   2.5,
                                     -55., 2.4,   2.5,
                                     -54., 2.056, 2.1,
                                     -15., 1.067, 1.1,
                                   };

  Double_t parPipeTargetCentral[9] = { 0., 360., 2,
                                       -15., 0.,   1.1,
                                       15., 0.,   1.1,
                                     };

  Double_t parPipeTargetUp[27] = { 0., 360., 8,
                                   15., 1.067, 1.1,
                                   54., 2.056, 2.1,
                                   55., 2.4,   2.5,
                                   95., 2.4,   2.5,
                                   96., 4.5,   4.6,
                                   145., 4.5,   4.6,
                                   155., 14.4,  14.5,
                                   215., 14.4,   14.5
                                 };

  Double_t parPipeVacuumTargetDown[27] = { 0., 360., 8,
                                         -215., 0.,  17.4,
                                         -183., 0.,  17.4,
                                         -173., 0.,   4.5,
                                         -96., 0.,   4.5,
                                         -95., 0.,   2.4,
                                         -55., 0.,   2.4,
                                         -54., 0.,   2.056,
                                         -15., 0.,   1.067
                                         };

  Double_t parPipeVacuumTargetCentral[9] = { 0., 360., 2,
      -15., 0.,   1.067,
      15., 0.,   1.067,
                                           };

  Double_t parPipeVacuumTargetUp[27] = { 0., 360., 8,
                                         15., 0.,   1.067,
                                         54., 0.,   2.056,
                                         55., 0.,   2.4,
                                         95., 0.,   2.4,
                                         96., 0.,   4.5,
                                         145., 0.,   4.5,
                                         155., 0.,  14.4,
                                         215., 0.,  14.4
                                       };

  TGeoPcon* pipeLeft          = new TGeoPcon(parPipeLeft);
  TGeoPcon* pipeCentral       = new TGeoPcon(parPipeCentral);
  pipeCentral->SetName("PIPE_CN");
  TGeoPcon* pipeRight         = new TGeoPcon(parPipeRight);
  TGeoPcon* pipeTargetDown    = new TGeoPcon(parPipeTargetDown);
  TGeoPcon* pipeTargetCentral = new TGeoPcon(parPipeTargetCentral);
  pipeTargetCentral->SetName("TRG_CN");
  TGeoPcon* pipeTargetUp      = new TGeoPcon(parPipeTargetUp);

  TGeoPcon* pipeVacuumLeft          = new TGeoPcon(parPipeVacuumLeft);
  TGeoPcon* pipeVacuumCentral       = new TGeoPcon(parPipeVacuumCentral);
  pipeVacuumCentral->SetName("PIPEV_CN");
  TGeoPcon* pipeVacuumRight         = new TGeoPcon(parPipeVacuumRight);
  TGeoPcon* pipeVacuumTargetDown    = new TGeoPcon(parPipeVacuumTargetDown);
  TGeoPcon* pipeVacuumTargetCentral = new TGeoPcon(parPipeVacuumTargetCentral);
  pipeVacuumTargetCentral->SetName("TRGV_CN");
  TGeoPcon* pipeVacuumTargetUp      = new TGeoPcon(parPipeVacuumTargetUp);

  TGeoRotation* r1 = new TGeoRotation("r1");
  r1->RotateX(90.);
  r1->RegisterYourself();

  TGeoCompositeShape* pipeCross       = new TGeoCompositeShape("pipeCross",       "(PIPE_CN+TRG_CN:r1) - (PIPEV_CN+TRGV_CN:r1)");
  TGeoCompositeShape* pipeVacuumCross = new TGeoCompositeShape("pipeVacuumCross", "PIPEV_CN+TRGV_CN:r1");


  TGeoVolume* volPipeLeft       = new TGeoVolume("PipeLeft",       pipeLeft,       gGeoManager->GetMedium("steel"));
  TGeoVolume* volPipeCross      = new TGeoVolume("PipeCross",      pipeCross,      gGeoManager->GetMedium("Al+Be"));
  TGeoVolume* volPipeRight      = new TGeoVolume("PipeRight",      pipeRight,      gGeoManager->GetMedium("steel"));
  TGeoVolume* volPipeTargetUp   = new TGeoVolume("PipeTargetUp",   pipeTargetUp,   gGeoManager->GetMedium("steel"));
  TGeoVolume* volPipeTargetDown = new TGeoVolume("PipeTargetDown", pipeTargetDown, gGeoManager->GetMedium("steel"));

  TGeoVolume* volPipeVacuumLeft       = new TGeoVolume("PipeVacuumLeft",       pipeVacuumLeft,       gGeoManager->GetMedium("vacuum"));
  TGeoVolume* volPipeVacuumCross      = new TGeoVolume("PipeVacuumCross",      pipeVacuumCross,      gGeoManager->GetMedium("vacuum"));
  TGeoVolume* volPipeVacuumRight      = new TGeoVolume("PipeVacuumRight",      pipeVacuumRight,      gGeoManager->GetMedium("vacuum"));
  TGeoVolume* volPipeVacuumTargetUp   = new TGeoVolume("PipeVacuumTargetUp",   pipeVacuumTargetUp,   gGeoManager->GetMedium("vacuum"));
  TGeoVolume* volPipeVacuumTargetDown = new TGeoVolume("PipeVacuumTargetDown", pipeVacuumTargetDown, gGeoManager->GetMedium("vacuum"));

  TGeoRotation rot;
  rot.RotateX(90.);

  TGeoVolume* beamPipe = new TGeoVolumeAssembly("BeamPipe");
  beamPipe->AddNode(volPipeLeft,             0);
  beamPipe->AddNode(volPipeRight,            0);
  beamPipe->AddNode(volPipeVacuumLeft,       0);
  beamPipe->AddNode(volPipeVacuumRight,      0);
  beamPipe->AddNode(volPipeTargetUp,         0, new TGeoRotation(rot));
  beamPipe->AddNode(volPipeTargetDown,       0, new TGeoRotation(rot));
  beamPipe->AddNode(volPipeVacuumTargetUp,   0, new TGeoRotation(rot));
  beamPipe->AddNode(volPipeVacuumTargetDown, 0, new TGeoRotation(rot));
  beamPipe->AddNode(volPipeCross,            0);
  beamPipe->AddNode(volPipeVacuumCross,      0);

  TGeoVolume* cave = gGeoManager->GetTopVolume();
  cave->AddNode(beamPipe, 1);

}

FairModule* FairPipe::CloneModule() const
{
  return new FairPipe(*this);
}

ClassImp(FairPipe)

