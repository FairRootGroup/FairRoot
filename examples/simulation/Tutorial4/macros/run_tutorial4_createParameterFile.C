/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_tutorial4_createParameterFile()
{

  Bool_t ShiftX = kTRUE;
  Bool_t ShiftY = kTRUE;
  Bool_t ShiftZ = kFALSE;

  Bool_t RotX = kFALSE;
  Bool_t RotY = kFALSE;
  Bool_t RotZ = kFALSE;

  
  TString mcEngine="TGeant3";
  TString dir = getenv("VMCWORKDIR");
  
  TString outDir = "./data/";
  
  TString geoFile ="makeGeoFile_";
  geoFile = outDir + geoFile + mcEngine + "_full.root";
  
  TFile* f = new TFile(geoFile, "READ");
  if (!f) {
    std::cout << "Could not open the file" << std::endl;
    exit(1);
  }
  
  TList* l = f->GetListOfKeys();
  
  TKey* key;
  TIter next( l);
  
  TGeoManager* geoMan{nullptr};

  while ((key = (TKey*)next())) {
    if ( key->ReadObj()->InheritsFrom("TGeoManager") ) {
      geoMan = static_cast<TGeoManager*>(key->ReadObj());
      break;
    }
  }
  
  if (! geoMan) {
    f->Close();
    std::cout << "Could not find TGeoManager inside the file" << std::endl;
    exit(1);
  }
  
  geoMan->Print();


  Double_t     fGlobal[3];     //! Global center of volume
  Float_t shiftx{0.};
  Float_t shifty{0.};
  Float_t shiftz{0.};
  Float_t rotx{0.};
  Float_t roty{0.};
  Float_t rotz{0.};

  std::map<UInt_t, std::pair<TString, TGeoCombiTrans*>> misalignInfo;
  
  TGeoNode* topNode = gGeoManager->GetTopNode();
  
  TObjArray* nodes = topNode->GetNodes();
  for (Int_t iNode = 0; iNode < nodes->GetEntriesFast(); iNode++) {
    TGeoNode* node = static_cast<TGeoNode*>(nodes->At(iNode));
    cout << "Node: " << node->GetName() << std::endl;
    if (!TString(node->GetName()).Contains("tutorial4")) continue; // trd_vXXy top node, e.g. trd_v13a, trd_v14b
    TGeoNode* station = node;
    TObjArray* layers = station->GetNodes();
    for (Int_t iLayer = 0; iLayer < layers->GetEntriesFast(); iLayer++) {
      TGeoNode* layer = static_cast<TGeoNode*>(layers->At(iLayer));
      cout << "Layer: " << layer->GetName() << std::endl;
      TString path = TString("/") + topNode->GetName() + "/" + station->GetName() + "/"
	+ layer->GetName();
      cout << "Path: " << path << endl; 

      UInt_t hash = path.Hash();
      if (ShiftX) {
        shiftx = gRandom->Uniform(-1.,1.);
      } 
      if (ShiftY) {
        shifty = gRandom->Uniform(-1.,1.);
      } 
      if (ShiftZ) {
        shiftz = gRandom->Uniform(-1.,1.);
      } 

      TGeoTranslation* trans{nullptr};
      TGeoRotation* rot{nullptr};
      if ( iLayer > 0 & iLayer < layers->GetEntriesFast()-1 ) {
        trans = new TGeoTranslation(shiftx, shifty, shiftz);
        rot = new TGeoRotation("temp",rotx, roty, rotz);
      } else {
        trans = new TGeoTranslation(0., 0., 0.);
        rot = new TGeoRotation("temp",0.,0., 0.);
      }
      TGeoCombiTrans* combi= new TGeoCombiTrans(*trans, *rot);

      misalignInfo[hash] = make_pair(path, combi);
    }
  }

  cout << "There are in total " << misalignInfo.size() << " detectors" << endl;

  for (auto& elem: misalignInfo) {
    cout << "Module "<< elem.first << " " << elem.second.first << " " 
                     << elem.second.second << endl;
  } 


  ofstream myfile;
  myfile.open ("example.par");

  myfile << "##############################################################################" << endl;
  myfile << "# Class:   FairTutorialDetMissallignPar" << endl;
  myfile << "# Context: TestDefaultContext" << endl;
  myfile << "##############################################################################" << endl;
  myfile << "[FairTutorialDetMissallignPar]" << endl;
  myfile << "//----------------------------------------------------------------------------" << endl;
  myfile << "NrOfDetectors:  Int_t "<< misalignInfo.size() << endl;
  myfile << "DetectorId:  UInt_t \\ "<< endl;

  Int_t counter = 0; 

  myfile <<"  ";
  for (auto& elem: misalignInfo) {
    if ( (8 == counter) ) {
      myfile << elem.first <<" \\"<<endl;
      myfile <<"  ";
      counter = 0;
    } else {
      myfile << elem.first <<" ";
      ++counter;
    }
  }
  myfile<<endl;

  for (auto& elem: misalignInfo) {
    const Double_t* rotation = elem.second.second->GetRotationMatrix();
    const Double_t* translation = elem.second.second->GetTranslation();
    myfile << elem.first << " :  Double_t \\ "<< endl;
    myfile << rotation[0] << " " << rotation[1] << " " << rotation[2] <<" \\"<<endl;
    myfile << rotation[3] << " " << rotation[4] << " " << rotation[5] <<" \\"<<endl;
    myfile << rotation[6] << " " << rotation[7] << " " << rotation[8] <<" \\"<<endl;
    myfile << translation[0] << " " << translation[1] << " " << translation[2] <<endl;
  }
  myfile << "##############################################################################" << endl;

  myfile.close();


}
