/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/


// forward declaration
void writeVectorToFile(std::vector<Double_t>& vec, ofstream* myfile);

void run_tutorial4_createParameterFile()
{

  // Create shift in x, y, z when true
  Bool_t ShiftX = kTRUE;
  Bool_t ShiftY = kTRUE;
  Bool_t ShiftZ = kFALSE;

  // Create a rotation around x, y, z when true
  Bool_t RotX = kFALSE;
  Bool_t RotY = kFALSE;
  Bool_t RotZ = kFALSE;

  // main container to store all relevant alignment informatio
  std::map<UInt_t, std::pair<TString, TGeoCombiTrans*>> misalignInfo;


  //Open file and get the stired TGeoManager
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

  Float_t shiftx{0.};
  Float_t shifty{0.};
  Float_t shiftz{0.};
  Float_t rotx{0.};
  Float_t roty{0.};
  Float_t rotz{0.};

  TGeoNode* topNode = gGeoManager->GetTopNode();
  TObjArray* nodes = topNode->GetNodes();
  for (Int_t iNode = 0; iNode < nodes->GetEntriesFast(); iNode++) {
    TGeoNode* node = static_cast<TGeoNode*>(nodes->At(iNode));
    if (!TString(node->GetName()).Contains("tutorial4")) continue; // trd_vXXy top node, e.g. trd_v13a, trd_v14b
    TGeoNode* station = node;
    TObjArray* layers = station->GetNodes();
    for (Int_t iLayer = 0; iLayer < layers->GetEntriesFast(); iLayer++) {
      TGeoNode* layer = static_cast<TGeoNode*>(layers->At(iLayer));
      TString path = TString("/") + topNode->GetName() + "/" + station->GetName() + "/"
	+ layer->GetName();

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

       if (misalignInfo.find(hash) != misalignInfo.end()) {
         cerr << "[ERROR ] Hash collision" << endl;
         cerr << "[ERROR ] Hash value " << hash << " already exist." << endl;
         auto it = misalignInfo.find(hash);
         cerr << "[ERROR ] TGeoNode: " << it->second.first << " and " << path
              << " both have hash " << hash << endl;
         cerr << "[FATAL ] This should never happen. Stop execution." << endl;
         exit(1);
       }

      misalignInfo[hash] = make_pair(path, combi);
    }
  }

  // Close the file with the TGeoManager after all information was extracted
  f->Close();

  cout << "There are in total " << misalignInfo.size() << " misalligned nodes" << endl;

  for (auto& elem: misalignInfo) {
    cout << "Module "<< elem.first << " " << elem.second.first << " "
                     << elem.second.second << endl;
  }


  // Write the paramter file
  ofstream myfile;
  myfile.open ("example.par");

  myfile << "##############################################################################" << endl;
  myfile << "# Class:   FairTutorialDetMissallignPar" << endl;
  myfile << "# Context: TestDefaultContext" << endl;
  myfile << "##############################################################################" << endl;
  myfile << "[FairTutorialDetMissallignPar]" << endl;
  myfile << "//----------------------------------------------------------------------------" << endl;
  myfile << "NrOfDetectors:  Int_t "<< misalignInfo.size() << endl;

  // vectors for the different components of the rotation matrix and
  // the translation vector.
  std::vector<Double_t> r11;
  std::vector<Double_t> r12;
  std::vector<Double_t> r13;
  std::vector<Double_t> r21;
  std::vector<Double_t> r22;
  std::vector<Double_t> r23;
  std::vector<Double_t> r31;
  std::vector<Double_t> r32;
  std::vector<Double_t> r33;
  std::vector<Double_t> tx;
  std::vector<Double_t> ty;
  std::vector<Double_t> tz;
  std::vector<TString> path;
  std::vector<UInt_t> hash;

  Int_t counter = 0;

  myfile << "DetectorId:  UInt_t \\ "<< endl;
  myfile <<"  ";
  for (auto& elem: misalignInfo) {
    const Double_t* rotation = elem.second.second->GetRotationMatrix();
    const Double_t* translation = elem.second.second->GetTranslation();
    r11.push_back(rotation[0]);
    r12.push_back(rotation[1]);
    r13.push_back(rotation[2]);
    r21.push_back(rotation[3]);
    r22.push_back(rotation[4]);
    r23.push_back(rotation[5]);
    r31.push_back(rotation[6]);
    r32.push_back(rotation[7]);
    r33.push_back(rotation[8]);
    tx.push_back(translation[0]);
    ty.push_back(translation[1]);
    tz.push_back(translation[2]);
    hash.push_back(elem.first);
    path.push_back(elem.second.first);

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

  // Due to performance issues when reading the parameters it is not possible
  // to store the information about rotation and translation for each
  // misaligned node. Instead store the values for one component of rotation
  // or translation for all nodes in one array. This reduces the number of
  // parameters from a (possible) very large number to 12 (9 components for
  // the rotation matrix and 3 for the translation matrix. The proper
  // matrices will be created when reading the parameter container.


  myfile << "R11:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r11, &myfile);
  myfile << "R12:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r12, &myfile);
  myfile << "R13:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r13, &myfile);

  myfile << "R21:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r21, &myfile);
  myfile << "R22:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r22, &myfile);
  myfile << "23:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r23, &myfile);

  myfile << "R31:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r31, &myfile);
  myfile << "R32:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r32, &myfile);
  myfile << "33:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(r33, &myfile);

  myfile << "TX:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(tx, &myfile);
  myfile << "TY:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(ty, &myfile);
  myfile << "TZ:  Double_t \\ "<< endl;
  myfile <<"  ";
  writeVectorToFile(tz, &myfile);

  myfile << "##############################################################################" << endl;

  myfile.close();

/*
  // To check if the vector sorting works and one gets in the end the same
  // results as when using the map
  myfile.open ("test1.txt");
  for (Int_t iCount = 0; iCount < r11.size(); iCount++) {
    myfile << "Module "<< hash[iCount] << " " << path[iCount] << " "
                     << r11[iCount] << " "
                     << r12[iCount] << " "
                     << r13[iCount] << " "
                     << r21[iCount] << " "
                     << r22[iCount] << " "
                     << r23[iCount] << " "
                     << r31[iCount] << " "
                     << r32[iCount] << " "
                     << r33[iCount] << " "
                     << tx[iCount] << " "
                     << ty[iCount] << " "
                     << tz[iCount]
                     << endl;
  }
  myfile.close();
*/

  myfile.open ("misalignment.txt");
  for (auto& elem: misalignInfo) {
    const Double_t* rotation = elem.second.second->GetRotationMatrix();
    const Double_t* translation = elem.second.second->GetTranslation();
    myfile << "Module " << elem.first << " " << elem.second.first << " "
         << rotation[0] << " " << rotation[1] << " " << rotation[2] <<" "
         << rotation[3] << " " << rotation[4] << " " << rotation[5] <<" "
         << rotation[6] << " " << rotation[7] << " " << rotation[8] <<" "
         << translation[0] << " " << translation[1] << " " << translation[2] <<endl;
  }
  myfile.close();

}

void writeVectorToFile(std::vector<Double_t>& vec, ofstream* myfile)
{
  Int_t counter = 0;
  for (auto& elem: vec) {
    if ( (8 == counter) ) {
      *myfile << elem <<" \\"<<endl;
      *myfile <<"  ";
      counter = 0;
    } else {
      *myfile << elem <<" ";
      ++counter;
    }
  }
  *myfile<<endl;
}
