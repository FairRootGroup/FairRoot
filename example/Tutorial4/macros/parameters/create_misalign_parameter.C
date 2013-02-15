//void create_misalign_parameter(Bool_t onlyshiftx=kFALSE, Int_t nrOfDetLayers=40)
void create_misalign_parameter(Int_t nrOfDetLayers=40)
{
  Float_t* ShiftX = new Float_t[nrOfDetLayers];
  Float_t* ShiftY = new Float_t[nrOfDetLayers];

  ShiftX[0] = 0.;
  ShiftY[0] = 0.;

  Int_t lastEntry = nrOfDetLayers-1; 
  ShiftX[lastEntry] = 0.;
  ShiftY[lastEntry] = 0.;

Bool_t onlyshiftx = kTRUE;

  for (Int_t iLayer = 1; iLayer<lastEntry; ++iLayer) {
    Float_t shiftx = gRandom->Uniform(-1.,1.);
    Float_t shifty = gRandom->Uniform(-1.,1.);

     ShiftX[iLayer] = shiftx;
     ShiftY[iLayer] = shifty;
    if (onlyshiftx) {
     ShiftY[iLayer] = 0.;
    } else {
        ShiftY[iLayer] = shifty;
    }
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
  myfile << "##############################################################################" << endl;
  
  myfile.close();

  ofstream myfile;
  myfile.open ("shifts.txt");

  for (Int_t iLayer = 0; iLayer<nrOfDetLayers; ++iLayer) {
      myfile << iLayer+1 << "   " << ShiftX[iLayer] <<endl;
  }
 
  myfile.close();

}