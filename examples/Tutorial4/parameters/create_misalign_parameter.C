/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void create_misalign_parameter(Int_t nrOfDetLayers=40)
{
  Bool_t misalignX = kTRUE;
  Bool_t misalignY = kTRUE;
  Bool_t misalignZ = kFALSE;
  Bool_t rotX = kFALSE;
  Bool_t rotY = kFALSE;
  Bool_t rotZ = kFALSE;


  Float_t* ShiftX = new Float_t[nrOfDetLayers];
  Float_t* ShiftY = new Float_t[nrOfDetLayers];
  Float_t* ShiftZ = new Float_t[nrOfDetLayers];
  Float_t* RotX = new Float_t[nrOfDetLayers];
  Float_t* RotY = new Float_t[nrOfDetLayers];
  Float_t* RotZ = new Float_t[nrOfDetLayers];

  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    ShiftX[iLayer] = 0.;
    ShiftY[iLayer] = 0.;
    ShiftZ[iLayer] = 0.;
    RotX[iLayer] = 0.;
    RotY[iLayer] = 0.;
    RotZ[iLayer] = 0.;
  }

  Int_t lastEntry = nrOfDetLayers-1; 

  for (Int_t iLayer = 1; iLayer<lastEntry; ++iLayer) {

    Float_t shiftx = gRandom->Uniform(-1.,1.);
    Float_t shifty = gRandom->Uniform(-1.,1.);
    Float_t shiftz = gRandom->Uniform(-1.,1.);
    Float_t rotx = gRandom->Uniform(-1.,1.);
    Float_t roty = gRandom->Uniform(-1.,1.);
    Float_t rotz = gRandom->Uniform(-1.,1.);

    if (misalignX) ShiftX[iLayer] = shiftx;
    if (misalignY) ShiftY[iLayer] = shifty;
    if (misalignZ) ShiftZ[iLayer] = shiftz;
    if (rotX) RotX[iLayer] = rotx;
    if (rotY) RotY[iLayer] = roty;
    if (rotZ) RotZ[iLayer] = rotz;

  }

  ofstream myfile;
  myfile.open ("example.par");

  myfile << "##############################################################################" << endl;
  myfile << "# Class:   FairTutorialDetMissallignPar" << endl;
  myfile << "# Context: TestDefaultContext" << endl;
  myfile << "##############################################################################" << endl;
  myfile << "[FairTutorialDetMissallignPar]" << endl;
  myfile << "//----------------------------------------------------------------------------" << endl;
  myfile << "NrOfDetectors:  Int_t "<< nrOfDetLayers << endl;
  myfile << "ShiftX:  Double_t \\ "<< endl;

  Int_t counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << ShiftX[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << ShiftX[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "ShiftY:  Double_t \\ "<< endl;

  counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << ShiftY[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << ShiftY[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "ShiftZ:  Double_t \\ "<< endl;

  counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << ShiftZ[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << ShiftZ[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "RotationX:  Double_t \\ "<< endl;

  counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << RotX[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << RotX[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "RotationY:  Double_t \\ "<< endl;

  counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << RotY[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << RotY[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "RotationZ:  Double_t \\ "<< endl;

  counter = 0; 

  myfile <<"  ";
  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
    if ( (9 == counter) && (1 != nrOfDetLayers-iLayer) ) {
      myfile << RotZ[iLayer] <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << RotZ[iLayer] <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  myfile << "##############################################################################" << endl;
  
  myfile.close();

  ofstream myfile;
  myfile.open ("shifts.txt");

  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
      if (misalignX) myfile << iLayer+1 << "   " << ShiftX[iLayer] <<endl;
      if (misalignY) myfile << iLayer+101 << "   " << ShiftY[iLayer] <<endl;
      if (misalignZ) myfile << iLayer+201 << "   " << ShiftZ[iLayer] <<endl;
      if (rotX) myfile << iLayer+301 << "   " << RotX[iLayer] <<endl;
      if (rotY) myfile << iLayer+401 << "   " << RotY[iLayer] <<endl;
      if (rotZ) myfile << iLayer+501 << "   " << RotZ[iLayer] <<endl;
  }
 
  myfile.close();

}
