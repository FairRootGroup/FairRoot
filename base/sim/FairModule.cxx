/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                     FairModule source file                    -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------
/* Generated by Together */
#include "FairModule.h"

#include "FairGeoParSet.h"             // for FairBaseParSet
#include "FairGeoBuilder.h"             // for FairGeoBuilder
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoMedia.h"               // for FairGeoMedia
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairVolume.h"                 // for FairVolume
#include "FairVolumeList.h"             // for FairVolumeList

#include "TBuffer.h"                    // for TBuffer, operator<<, etc
#include "TCollection.h"                // for TIter
#include "TFile.h"                      // for TFile
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TGeoMaterial.h"               // for TGeoMaterial
#include "TGeoMatrix.h"                 // for TGeoMatrix, TGeoHMatrix
#include "TGeoNode.h"                   // for TGeoNode
#include "TGeoVolume.h"                 // for TGeoVolume
#include "TGeoVoxelFinder.h"            // for TGeoVoxelFinder
#include "TKey.h"                       // for TKey
#include "TList.h"                      // for TList, TListIter
#include "TObjArray.h"                  // for TObjArray
#include "TObject.h"                    // for TObject
#include "TRefArray.h"                  // for TRefArray
#include "TString.h"                    // for TString, operator!=, etc
#include "TSystem.h"                    // for TSystem, gSystem

#ifdef ROOT_HAS_GDML
#include "TGDMLParse.h"
#endif

#include <stdlib.h>                     // for getenv
#include <string.h>                     // for NULL, strcmp, strlen
#include <map>

class FairGeoMedium;
class TGeoMedium;

TArrayI* FairModule::volNumber=0;
Int_t FairModule::fNbOfVolumes=0;
FairVolumeList*  FairModule::vList=0;
TRefArray*    FairModule::svList=0;



//__________________________________________________________________________
void FairModule::ConstructGeometry()
{
  LOG(WARNING)<<"The method ConstructGeometry has to be implemented in the detector class which inherits from FairModule"<<FairLogger::endl;
}
//__________________________________________________________________________
void FairModule::ConstructOpGeometry()
{
  LOG(DEBUG2)<<"The method ConstructOpGeometry has to be implemented in the detector class which inherits from FairModule"<<FairLogger::endl;;
}
//__________________________________________________________________________
FairModule::~FairModule()
{

}
//__________________________________________________________________________
FairModule::FairModule(const char* Name, const char* title ,Bool_t Active)
  :TNamed(Name, title),
   fMotherVolumeName(""),
   fgeoVer("Not defined"),
   fgeoName("Not defined"),
   fModId(-1),
   fActive(Active),
   fNbOfSensitiveVol(0),
   fVerboseLevel(0),
   flGeoPar(0),
   kGeoSaved(kFALSE)
{
  if(!svList) { svList=new TRefArray(); }
  if(!vList) { vList=new FairVolumeList(); }

}

//__________________________________________________________________________
FairModule::FairModule(const FairModule& rhs)
  :TNamed(rhs),
   fMotherVolumeName(rhs.fMotherVolumeName),
   fgeoVer(rhs.fgeoVer),
   fgeoName(rhs.fgeoName),
   fModId(rhs.fModId),
   fActive(rhs.fActive),
   fNbOfSensitiveVol(rhs.fNbOfSensitiveVol),
   fVerboseLevel(rhs.fVerboseLevel),
   flGeoPar(0),
   kGeoSaved(rhs.kGeoSaved)
{
   // Do not change anything in global fields (svList. vList)

  // TO DO - add when we know what type is the elements of flGeoPar
  //flGeoPar=new TObjArray();
  //TIter it = rhs.flGeoPar->MakeIterator();
  // Copy parameters
  //TObject* obj;
  //while((obj=it->Next())) {
  //  flGeoPar->Add(...);
  //}

}

//__________________________________________________________________________

FairModule::FairModule()
  : TNamed(),
    fMotherVolumeName(""),
    fgeoVer("Not defined"),
    fgeoName("Not defined"),
    fModId(-1),
    fActive(kFALSE),
    fNbOfSensitiveVol(0),
    fVerboseLevel(0),
    flGeoPar(0),
    kGeoSaved(kFALSE)
{

}

//__________________________________________________________________________
FairModule& FairModule::operator= (const FairModule& rhs)
{
  // check assignment to self
  if (this == &rhs) return *this;

  // base class assignment
  TNamed::operator=(rhs);

  // assignment operator
  fMotherVolumeName = rhs.fMotherVolumeName;
  fgeoVer = rhs.fgeoVer;
  fgeoName = rhs.fgeoName;
  fModId = rhs.fModId;
  fActive = rhs.fActive;
  fNbOfSensitiveVol = rhs.fNbOfSensitiveVol;
  fVerboseLevel = rhs.fVerboseLevel;
  flGeoPar = 0;
  kGeoSaved = rhs.kGeoSaved;

  // TO DO - add when we know what type is the elements of flGeoPar
  //flGeoPar=new TObjArray();
  //TIter it = rhs.flGeoPar->MakeIterator();
  // copy parameters
  //TObject* obj;
  //while((obj=it->Next())) {
  //  flGeoPar->Add(...);
  //}

  return *this;
}

//__________________________________________________________________________
void FairModule::Streamer(TBuffer& b)
{
  TNamed::Streamer(b);


  if (b.IsReading()) {
    fgeoVer.Streamer(b);
    fgeoName.Streamer(b);
    b >> fActive;
    b >> fModId;
  } else {
    fgeoVer.Streamer(b);
    fgeoName.Streamer(b);
    b << fActive;
    b << fModId;
  }

}
//__________________________________________________________________________
void FairModule::SetGeometryFileName(TString fname, TString geoVer)
{

  // If absolute path is given as argument, try to find it there.
  // If the file don't exist break. Don't look anywhere else.
  if ( fname.BeginsWith("/") ) {
    if ( gSystem->AccessPathName(fname.Data()) ) {
      LOG(FATAL) << fName << ": geometry file " << fname
                 << " not found in absolut path!"
                 << FairLogger::endl;
      fgeoName = "";
    } // file not found
    fgeoName = fname;
    LOG(DEBUG) << fName << ": using geometry file "
               << fgeoName << FairLogger::endl;
    return;
  }

  // If GEOMPATH is set, try to find the file there.
  // If there is no such file go on to look in the default location.
  TString userPath = getenv("GEOMPATH");
  if ( ! userPath.IsNull() ) {
    if ( ! userPath.EndsWith("/") ) {
      userPath += "/";
    }
    fgeoName = userPath + fname;
    if ( ! gSystem->AccessPathName(fgeoName.Data()) ) {
      LOG(DEBUG) << fName << ": using geometry file " << fgeoName
                 << FairLogger::endl;
      return;
    }
    LOG(DEBUG) << fName << ": geometry file " << fname
               << " not found in GEOMPATH "
               << userPath << FairLogger::endl;
  }

  // Look in the standard path
  fgeoName = getenv("VMCWORKDIR");
  fgeoName += "/geometry/" + fname;
  if ( ! gSystem->AccessPathName(fgeoName.Data()) ) {
    LOG(DEBUG) << fName << ": using geometry file "
               << fgeoName << FairLogger::endl;
    return;
  }

  // File not found
  LOG(FATAL) << fName << ": geometry file " << fname
             << " not found in standard path "
             << FairLogger::endl;
  fgeoName = "";
  return;

}
//__________________________________________________________________________
void FairModule::ProcessNodes(TList* aList)
{

  TListIter iter(aList);
  FairGeoNode* node   = NULL;
  FairGeoNode* MotherNode =NULL;
  FairVolume*  volume = NULL;
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairGeoParSet* par=(FairGeoParSet*)(rtdb->getContainer("FairGeoParSet"));
  TObjArray* fNodes = par->GetGeoNodes();
  while( (node = (FairGeoNode*)iter.Next()) ) {

    node->calcLabTransform();
    MotherNode=node->getMotherNode();
    volume = new FairVolume( node->getTruncName(), fNbOfVolumes++);
    volume->setRealName(node->GetName());
    vList->addVolume(volume);
    volume->setGeoNode(node);
    volume->setCopyNo(  node->getCopyNo());

    if(MotherNode!=0) {
      volume->setMotherId(node->getMCid());
      volume->setMotherCopyNo(MotherNode->getCopyNo());
    }
    FairGeoVolume* aVol=NULL;

    if ( node->isSensitive() && fActive ) {
      volume->setModId(fModId);
      volume->SetModule(this);
      svList->Add(volume);
      aVol = dynamic_cast<FairGeoVolume*> ( node );
      fNodes->AddLast( aVol );
      fNbOfSensitiveVol++;
    }

  }
}
//__________________________________________________________________________
void  FairModule::AddSensitiveVolume(TGeoVolume* v)
{

  LOG(DEBUG2)<<"AddSensitiveVolume " << v->GetName() << FairLogger::endl;
  // Only register volumes which are not already registered
  // Otherwise the stepping will be slowed down
  if( ! vList->findObject(v->GetName() ) ) {
    FairVolume*  volume = NULL;
    volume = new FairVolume(v->GetName(), fNbOfVolumes++);
    vList->addVolume(volume);
    volume->setModId(fModId);
    volume->SetModule(this);
    svList->Add(volume);
    fNbOfSensitiveVol++;
  }
}


//__________________________________________________________________________
FairVolume* FairModule::getFairVolume(FairGeoNode* fN)
{
  FairVolume* fv;
  FairVolume*  fvol=0;
  for(Int_t i=0; i<vList->getEntries(); i++) {
    fv=vList->At(i);
    if((fv->getGeoNode())==fN) {
      fvol=fv;
      return fvol;
      break;
    }
  }
  return fvol;
}
//__________________________________________________________________________
void FairModule::ConstructRootGeometry()
{
  /** Construct the detector geometry from ROOT files, possible inputs are:
   * 1. A TGeoVolume as a mother (master) volume containing the detector geometry
   * 2. A TGeoManager with the detector geometry
   * 3. A TGeoVolume as a mother or Master volume which is the output of the CAD2ROOT geometry, in this case
   *    the materials are not proprely defined and had to be reset
   *  In all cases we have to check that the material properties are the same or is the materials defined in
   *  the current simulation session
   */
  TGeoManager* OldGeo=gGeoManager;
  TGeoManager* NewGeo=0;
  TGeoVolume* volume=0;;
  TFile* f=new TFile(GetGeometryFileName().Data());
  TList* l= f->GetListOfKeys();
  TKey* key;
  TIter next( l);
  TGeoNode* n=0;
  TGeoVolume* v1=0;
  while ((key = (TKey*)next())) {
    /**loop inside the delivered root file and try to fine a TGeoManager object
     * the first TGeoManager found will be read
     */
    if (strcmp(key->GetClassName(),"TGeoManager") != 0) { continue; }
    gGeoManager=0;
    NewGeo = (TGeoManager*)key->ReadObj();
    break;
  }
  if (NewGeo!=0) {
    /** in case a TGeoManager was found get the top most volume and the node
     */

    NewGeo->cd();
    volume=(TGeoVolume*)NewGeo->GetNode(0)->GetDaughter(0)->GetVolume();
    v1=volume->MakeCopyVolume(volume->GetShape());
    // n=NewGeo->GetTopNode();
    n=v1->GetNode(0);
    //  NewGeo=0;
    // delete NewGeo; //move it to the end of the method

  } else {
    /** The file does not contain any TGeoManager, so we assume to have a file with a TGeoVolume
     * try to look for a TGeoVolume inside the file
     */

    key=(TKey*) l->At(0);  //Get the first key in the list
    volume=dynamic_cast<TGeoVolume*> (key->ReadObj());
    if(volume!=0) { n=volume->GetNode(0); }
    if(n!=0) { v1=n->GetVolume(); }
  }

  if(v1==0) {
    LOG(FATAL)<<"Could not find any geometry in file " << GetGeometryFileName().Data() << FairLogger::endl;
  } else {
    gGeoManager=OldGeo;
    gGeoManager->cd();
    // If AddToVolume is empty add the volume to the top volume Cave
    // If it is defined check i´f the volume exists and if it exists add the volume from the root file
    // to the already existing volume
    TGeoVolume* Cave=NULL;
    if ( 0 == fMotherVolumeName.Length() ) {
      Cave= gGeoManager->GetTopVolume();
    } else {
      Cave = gGeoManager->GetVolume(fMotherVolumeName);
    }
    if(Cave!=NULL) {
      /**Every thing is OK, we have a TGeoVolume and now we add it to the simulation TGeoManager  */
      gGeoManager->AddVolume(v1);
      /** force rebuilding of voxels */
      TGeoVoxelFinder* voxels = v1->GetVoxels();
      if (voxels) { voxels->SetNeedRebuild(); }

      // else { fLogger->Fatal(MESSAGE_ORIGIN, "\033[5m\033[31mFairModule::ConstructRootGeometry(): could not find voxels  \033[0m"); }

      /**To avoid having different names of the default matrices because we could have get the volume from another
       * TGeoManager, we reset the default matrix name
       */
      TGeoMatrix* M = n->GetMatrix();
      SetDefaultMatrixName(M);

      /** NOw we can remove the matrix so that the new geomanager will rebuild it properly*/
      gGeoManager->GetListOfMatrices()->Remove(M);
      TGeoHMatrix* global = gGeoManager->GetHMatrix();
      gGeoManager->GetListOfMatrices()->Remove(global); //Remove the Identity matrix
      /**Now we can add the node to the existing cave */
      Cave->AddNode(v1,0, M);
      /** correction from O. Merle: in case of a TGeoVolume (v1) set the material properly */

      AssignMediumAtImport(v1);
      /** now go through the herachy and set the materials properly, this is important becase the CAD converter
       *  produce TGeoVolumes with materials that have only names and no properties
       */
      ExpandNode(n);
      if(NewGeo!=0) { delete NewGeo; }
      delete f;
    } else {
      LOG(FATAL)<<"Could not find the given mother volume "<< fMotherVolumeName.Data() << " where the geomanger should be added."<<FairLogger::endl;
    }
  }
}
#ifdef ROOT_HAS_GDML
void FairModule::ConstructGDMLGeometry(TGeoMatrix* posrot)
{
    // Parse the GDML file
    TFile *old = gFile;
	TGDMLParse parser;
	TGeoVolume* gdmlTop;
	gdmlTop = parser.GDMLReadFile(GetGeometryFileName());

    // Change ID of media. TGDMLParse starts allways from 0. Need to shift.
    ReAssignMediaId();

    // Add volume to the cave and go through it recursively
	gGeoManager->GetTopVolume()->AddNode(gdmlTop,1,posrot);
	ExpandNodeForGDML(gGeoManager->GetTopVolume()->GetNode(gGeoManager->GetTopVolume()->GetNdaughters()-1));
    gFile = old;
}

void FairModule::ExpandNodeForGDML(TGeoNode* curNode)
{
    // Get pointer to volume and assign medium
	TGeoVolume* curVol = curNode->GetVolume();
    AssignMediumAtImport(curVol);

    // Check if the volume is sensitive
    if ( (this->InheritsFrom("FairDetector")) && CheckIfSensitive(curVol->GetName())) {
        LOG(DEBUG2)<<"Sensitive Volume "<< curVol->GetName() << FairLogger::endl;
        AddSensitiveVolume(curVol);
    }

	//! Recursevly go down the tree of nodes
	if (curVol->GetNdaughters() != 0)
	{
		TObjArray* NodeChildList = curVol->GetNodes();
		TGeoNode* curNodeChild;
		for (Int_t j=0; j<NodeChildList->GetEntriesFast(); j++)
		{
			curNodeChild = (TGeoNode*)NodeChildList->At(j);
			ExpandNodeForGDML(curNodeChild);
		}
	}
}
#else
void FairModule::ConstructGDMLGeometry(TGeoMatrix* posrot)
{
    gLogger->Error(MESSAGE_ORIGIN," Could not construct magnet geometry from gdml file. ");
    gLogger->Error(MESSAGE_ORIGIN," The used ROOT version does not support gdml. ");
    gLogger->Error(MESSAGE_ORIGIN," Please recompile ROOT with gdml support. ");
    gLogger->Fatal(MESSAGE_ORIGIN," Stop execution at this point. ");
}

void FairModule::ExpandNodeForGDML(TGeoNode* curNode)
{
}
#endif
void FairModule::ReAssignMediaId()
{
    // Initialise pointer to GeoBuilder
    FairGeoBuilder* geoBuilder = FairGeoLoader::Instance()->getGeoBuilder();
    // Get list of TGeo media
    TList* media = gGeoManager->GetListOfMedia();
    // Loop over new media which are not in GeoBase and shift the ID
    TGeoMedium* med;
    TGeoMedium* med2;
    for(Int_t i = geoBuilder->GetNMedia(); i < media->GetEntries(); i++)
    {
        med = (TGeoMedium*) media->At(i);
        med->SetId(i+1);
    }
    // Change GeoBase medium index
    geoBuilder->SetNMedia(media->GetEntries());

    // Revove dublicated materials
    TList* materials = gGeoManager->GetListOfMaterials();
    TIter next1(materials);
    // map for existing materials
    std::map<TString, Bool_t> mapMatName;
    TGeoMaterial* mat;
    while( (mat = (TGeoMaterial*)next1()) )
    {
        // If material exist - delete dublicated. If not - set the flag
        if(mapMatName[mat->GetName()])
        {
            materials->Remove(mat);
        }
        else
        {
            mapMatName[mat->GetName()] = kTRUE;
        }
    }
}
//__________________________________________________________________________
void FairModule::ConstructASCIIGeometry()
{
  LOG(WARNING)<<"The method ConstructASCIIGeometry has to be implemented in the detector class which inherits from FairModule"<<FairLogger::endl;
}
//__________________________________________________________________________
Bool_t FairModule::CheckIfSensitive(std::string name)
{
  LOG(WARNING)<<"The method CheckIfSensitive has to be implemented in the detector class which inherits from FairModule"<<FairLogger::endl;
  return kFALSE;
}
//__________________________________________________________________________
void FairModule::ExpandNode(TGeoNode* fN)
{
  //FairGeoLoader* geoLoad = FairGeoLoader::Instance();
  //FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  //FairGeoMedia* Media =  geoFace->getMedia();
  //FairGeoBuilder* geobuild=geoLoad->getGeoBuilder();
  TGeoMatrix* Matrix =fN->GetMatrix();
  if(gGeoManager->GetListOfMatrices()->FindObject(Matrix)) { gGeoManager->GetListOfMatrices()->Remove(Matrix); }
  TGeoVolume* v1=fN->GetVolume();
  TObjArray* NodeList=v1->GetNodes();
  for (Int_t Nod=0; Nod<NodeList->GetEntriesFast(); Nod++) {
    TGeoNode* fNode =(TGeoNode*)NodeList->At(Nod);
    TGeoMatrix* M =fNode->GetMatrix();
    //M->SetDefaultName();
    SetDefaultMatrixName(M);
    if(fNode->GetNdaughters()>0) { ExpandNode(fNode); }
    TGeoVolume* v= fNode->GetVolume();
    AssignMediumAtImport(v);
    if (!gGeoManager->FindVolumeFast(v->GetName())) {
      LOG(DEBUG2)<<"Register Volume " << v->GetName()<<FairLogger::endl;
      v->RegisterYourself();
    }
    if ( (this->InheritsFrom("FairDetector")) && CheckIfSensitive(v->GetName())) {
      LOG(DEBUG2)<<"Sensitive Volume "<< v->GetName() << FairLogger::endl;
      AddSensitiveVolume(v);
    }
  }
}
//__________________________________________________________________________
void FairModule::SetDefaultMatrixName(TGeoMatrix* matrix)
{
  // Copied from root TGeoMatrix::SetDefaultName() and modified (memory leak)
  // If no name was supplied in the ctor, the type of transformation is checked.
  // A letter will be prepended to the name :
  //   t - translation
  //   r - rotation
  //   s - scale
  //   c - combi (translation + rotation)
  //   g - general (tr+rot+scale)
  // The index of the transformation in gGeoManager list of transformations will
  // be appended.
  if (!gGeoManager) { return; }
  if (strlen(matrix->GetName())) { return; }
  char type = 'n';
  if (matrix->IsTranslation()) { type = 't'; }
  if (matrix->IsRotation()) { type = 'r'; }
  if (matrix->IsScale()) { type = 's'; }
  if (matrix->IsCombi()) { type = 'c'; }
  if (matrix->IsGeneral()) { type = 'g'; }
  TObjArray* matrices = gGeoManager->GetListOfMatrices();
  Int_t index = 0;
  if (matrices) { index =matrices->GetEntriesFast() - 1; }
  matrix->SetName(Form("%c%i", type, index));
}

//__________________________________________________________________________

void FairModule::AssignMediumAtImport(TGeoVolume* v)
{

  /**
   * Assign medium to the the volume v, this has to be done in all cases:
   * case 1: For CAD converted volumes they have no mediums (only names)
   * case 2: TGeoVolumes, we need to be sure that the material is defined in this session
   */
  FairGeoMedia* Media       = FairGeoLoader::Instance()->getGeoInterface()->getMedia();
  FairGeoBuilder* geobuild  = FairGeoLoader::Instance()->getGeoBuilder();

  TGeoMedium* med1=v->GetMedium();


  if(med1) {
    // In newer ROOT version also a TGeoVolumeAssembly has a material and medium.
    // This medium is called dummy and is automatically set when the geometry is constructed.
    // Since this material and medium is neither in the TGeoManager (at this point) nor in our
    // ASCII file we have to create it the same way it is done in TGeoVolume::CreateDummyMedium()
    // In the end the new medium and material has to be added to the TGeomanager, because this is
    // not done automatically when using the default constructor. For all other constructors the
    // newly created medium or material is added to the TGeomanger.
    // Create the medium and material only the first time.
    TString medName = (TString)(med1->GetName());
    if ( medName.EqualTo("dummy") && NULL == gGeoManager->GetMedium(medName) ) {

      TGeoMaterial *dummyMaterial = new TGeoMaterial();
      dummyMaterial->SetName("dummy");

      TGeoMedium* dummyMedium = new TGeoMedium();
      dummyMedium->SetName("dummy");
      dummyMedium->SetMaterial(dummyMaterial);

      gGeoManager->GetListOfMedia()->Add(dummyMedium);
      gGeoManager->AddMaterial(dummyMaterial);
    }

    TGeoMaterial* mat1=v->GetMaterial();
    TGeoMaterial* newMat = gGeoManager->GetMaterial(mat1->GetName());
    if( newMat==0) {
      /**The Material is not defined in the TGeoManager, we try to create one if we have enough information about it*/
      FairGeoMedium* FairMedium=Media->getMedium(mat1->GetName());
      if (!FairMedium) {
        LOG(FATAL)<<"Material "<< mat1->GetName() << "is not defined in ASCII file nor in Root file." << FairLogger::endl;
        //     FairMedium=new FairGeoMedium(mat1->GetName());
        //      Media->addMedium(FairMedium);
      } else {

        Int_t nmed=geobuild->createMedium(FairMedium);
        v->SetMedium(gGeoManager->GetMedium(nmed));
        gGeoManager->SetAllIndex();
      }
    } else {
      /**Material is already available in the TGeoManager and we can set it */
      TGeoMedium* med2= gGeoManager->GetMedium(mat1->GetName());
      v->SetMedium(med2);
    }
  } else {
    if (strcmp(v->ClassName(),"TGeoVolumeAssembly") != 0) {
      //[R.K.-3.3.08]  // When there is NO material defined, set it to avoid conflicts in Geant
      LOG(FATAL)<<"The volume "<< v->GetName() << "has no medium information and not an Assembly so we have to quit"<<FairLogger::endl;
    }
  }
}

//__________________________________________________________________________
FairModule* FairModule::CloneModule() const
{
  Fatal("CloneModule","Has to be overriden in multi-threading applications.");
  return 0;
}

//__________________________________________________________________________
ClassImp(FairModule)



