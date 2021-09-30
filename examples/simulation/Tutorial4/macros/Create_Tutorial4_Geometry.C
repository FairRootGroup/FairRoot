/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// in root all sizes are given in cm

#include <TFile.h>
#include <TGeoCompositeShape.h>
#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMatrix.h>
#include <TGeoMedium.h>
#include <TGeoPgon.h>
#include <TGeoVolume.h>
#include <TList.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>
#include <iostream>

// Name of geometry version and output file
const TString geoVersion = "tutorial4";
const TString FileName = geoVersion + ".root";
const TString FileName1 = geoVersion + "_geomanager.root";

// Names of the different used materials which are used to build the modules
// The materials are defined in the global media.geo file
const TString KeepingVolumeMedium = "air";
const TString BoxVolumeMedium = "silicon";

// Distance of the center of the first detector layer [cm];
const Float_t First_Z_Position = 10;
const Float_t Z_Distance = 10;

// Silicon box for both module types
const Float_t Module_Size_X = 80.;
const Float_t Module_Size_Y = 80.;
const Float_t Module_Size_Z = .04;

// some global variables
TGeoManager* gGeoMan = NULL;   // Pointer to TGeoManager instance
TGeoVolume* gModules;          // Global storage for module types

// Forward declarations
void create_materials_from_media_file();
TGeoVolume* create_detector();
void position_detector();
void add_alignable_volumes();

void Create_Tutorial4_Geometry()
{
    // Load needed material definition from media.geo file
    create_materials_from_media_file();

    // Get the GeoManager for later usage
    gGeoMan = (TGeoManager*)gROOT->FindObject("FAIRGeom");
    gGeoMan->SetVisLevel(7);

    // Create the top volume

    TGeoVolume* top = new TGeoVolumeAssembly("TOP");
    gGeoMan->SetTopVolume(top);

    TGeoVolume* tut4 = new TGeoVolumeAssembly(geoVersion);
    top->AddNode(tut4, 1);

    gModules = create_detector();

    position_detector();

    cout << "Voxelizing." << endl;
    top->Voxelize("");
    gGeoMan->CloseGeometry();

    add_alignable_volumes();

    gGeoMan->CheckOverlaps(0.001);
    gGeoMan->PrintOverlaps();
    gGeoMan->Test();

    TFile* outfile = TFile::Open(FileName, "RECREATE");
    top->Write();
    outfile->Close();

    TFile* outfile1 = TFile::Open(FileName1, "RECREATE");
    gGeoMan->Write();
    outfile1->Close();

    // ------------------------------------------------------------------------
}

void create_materials_from_media_file()
{
    // Use the FairRoot geometry interface to load the media which are already defined
    FairGeoLoader* geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();
    TString geoPath = FairConfig::Instance().GetVMCWorkDir();
    TString geoFile = geoPath + "/common/geometry/media.geo";
    geoFace->setMediaFile(geoFile);
    geoFace->readMedia();

    // Read the required media and create them in the GeoManager
    FairGeoMedia* geoMedia = geoFace->getMedia();
    FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

    FairGeoMedium* air = geoMedia->getMedium("air");
    FairGeoMedium* silicon = geoMedia->getMedium("silicon");

    // include check if all media are found

    geoBuild->createMedium(air);
    geoBuild->createMedium(silicon);
}

TGeoVolume* create_detector()
{

    // needed materials
    TGeoMedium* SiliconVolMed = gGeoMan->GetMedium(BoxVolumeMedium);

    // Single detector_layer
    TGeoBBox* det_plane = new TGeoBBox("", Module_Size_X / 2., Module_Size_Y / 2., Module_Size_Z / 2.);
    TGeoVolume* det_plane_vol = new TGeoVolume("tut4_det", det_plane, SiliconVolMed);
    det_plane_vol->SetLineColor(kBlue);   // set line color
    det_plane_vol->SetTransparency(70);   // set transparency
    TGeoTranslation* det_plane_trans = new TGeoTranslation("", 0., 0., 0.);

    return det_plane_vol;
}

void position_detector()
{

    TGeoTranslation* det_trans = NULL;

    Int_t numDets = 0;
    for (Int_t detectorPlanes = 0; detectorPlanes < 40; detectorPlanes++) {
        det_trans = new TGeoTranslation("", 0., 0., First_Z_Position + (numDets * Z_Distance));
        gGeoMan->GetVolume(geoVersion)->AddNode(gModules, numDets, det_trans);
        numDets++;
    }
}

void add_alignable_volumes()
{

    TString volPath;
    TString symName;
    TString detStr = "Tutorial4/det";
    TString volStr = "/TOP_1/tutorial4_1/tut4_det_";

    for (Int_t detectorPlanes = 0; detectorPlanes < 40; detectorPlanes++) {

        volPath = volStr;
        volPath += detectorPlanes;

        symName = detStr;
        symName += Form("%02d", detectorPlanes);

        cout << "Path: " << volPath << ", " << symName << endl;
        //    gGeoMan->cd(volPath);

        gGeoMan->SetAlignableEntry(symName.Data(), volPath.Data());
    }
    cout << "Nr of alignable objects: " << gGeoMan->GetNAlignable() << endl;
}
