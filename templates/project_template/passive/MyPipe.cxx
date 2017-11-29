/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -------------------------------------------------------------------------
// -----                    MyPipe  file                               -----
// -----                Created by M. Al-Turany  June 2014             -----
// -------------------------------------------------------------------------

#include "MyPipe.h"
#include "TList.h"
#include "TObjArray.h"

#include "TGeoPcon.h"
#include "TGeoTube.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoManager.h"


MyPipe::~MyPipe()
{
}
MyPipe::MyPipe()
  : FairModule()
{
}

MyPipe::MyPipe(const char * name, const char * title)
  : FairModule(name ,title)
{
}


// -----  ConstructGeometry  --------------------------------------------------
void MyPipe::ConstructGeometry()
{
     TGeoVolume *top=gGeoManager->GetTopVolume();
    
    // define some materials
     TGeoMaterial *matCarbon    = new TGeoMaterial("C", 12.011, 6.0, 2.265);
     TGeoMaterial *matVacuum    = new TGeoMaterial("Vacuum", 0, 0, 0);
    
    // define some media
     TGeoMedium *Carbon     = new TGeoMedium("C", 3, matCarbon);
     TGeoMedium *Vacuum     = new TGeoMedium("Vacuum", 4, matVacuum);
   
    
    Int_t nSects=2;
    Double_t z[] = { -100, 300};    // in cm
    Double_t r[] = { 2.5, 2.5};    // in cm
    Double_t Thickness = 0.05;     // thickness of beam pipe [cm]
    TGeoPcon* shape = new TGeoPcon(0., 360., nSects);
    for (Int_t iSect = 0; iSect < nSects; iSect++) {
        shape->DefineSection(iSect, z[iSect], r[iSect], r[iSect]+Thickness);
    }
    
    // ---> Volume
    TGeoVolume* pipe = new TGeoVolume("MyPipe", shape, Carbon);
    
    // --Now create the same but diameter less by Thikness and vacuum instead of Carbon
    TGeoPcon* Vshape = new TGeoPcon(0., 360., nSects);
    for (Int_t iSect = 0; iSect < nSects; iSect++) {
        Vshape->DefineSection(iSect, z[iSect], r[iSect], r[iSect]);
    }
    
    // ---> Volume
    TGeoVolume* Vpipe = new TGeoVolume("MyPipe", shape, Vacuum);
    
    top->AddNode(pipe, 1);
    top->AddNode(Vpipe, 1);


}
// ----------------------------------------------------------------------------



ClassImp(MyPipe)

