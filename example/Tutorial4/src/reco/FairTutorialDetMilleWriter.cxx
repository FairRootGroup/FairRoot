#include "FairTutorialDetMilleWriter.h"
#include "FairTutorialDetHit.h"

#include "FairTrackParam.h"

#include "Mille.h"

// ---- Default constructor -------------------------------------------
FairTutorialDetMilleWriter::FairTutorialDetMilleWriter()
  :FairTask("FairTutorialDetMilleWriter"),
   fTracks(),
   fHits(),
   fMille(NULL),
   fWriteAscii(kFALSE),
   fVersion(1)
{
  fLogger->Debug(MESSAGE_ORIGIN,"Defaul Constructor of FairTutorialDetMilleWriter");
}

// ---- Destructor ----------------------------------------------------
FairTutorialDetMilleWriter::~FairTutorialDetMilleWriter()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Destructor of FairTutorialDetMilleWriter");
}

// ----  Initialisation  ----------------------------------------------
void FairTutorialDetMilleWriter::SetParContainers()
{
  fLogger->Debug(MESSAGE_ORIGIN,"SetParContainers of FairTutorialDetMilleWriter");
  // Load all necessary parameter containers from the runtime data base
  /*
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();

  <FairTutorialDetMilleWriterDataMember> = (<ClassPointer>*)
    (rtdb->getContainer("<ContainerName>"));
  */
}

// ---- Init ----------------------------------------------------------
InitStatus FairTutorialDetMilleWriter::Init()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Initilization of FairTutorialDetMilleWriter");

  // Get a handle from the IO manager
  FairRootManager* ioman = FairRootManager::Instance();

  // Get a pointer to the previous already existing data level
  fTracks = (TClonesArray*) ioman->GetObject("TutorialDetTrack");
  if ( ! fTracks ) {
    fLogger->Error(MESSAGE_ORIGIN,"No InputDataLevelName array!\n FairTutorialDetMilleWriter will be inactive");
    return kERROR;
  }

  // Get a pointer to the previous already existing data level
  fHits = (TClonesArray*) ioman->GetObject("TutorialDetHit");
  if ( ! fHits ) {
    fLogger->Error(MESSAGE_ORIGIN,"No InputDataLevelName array!\n FairTutorialDetMilleWriter will be inactive");
    return kERROR;
  }

  //Open MillePede Output file
  if (fWriteAscii) {
    fMille = new Mille("mp2tst.ascii", false, true); // write human readable ascii file
  } else {
    fMille = new Mille("mp2tst.bin", true, false); // write binary file needed by pede
  }


  return kSUCCESS;

}

// ---- ReInit  -------------------------------------------------------
InitStatus FairTutorialDetMilleWriter::ReInit()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Initilization of FairTutorialDetMilleWriter");
  return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void FairTutorialDetMilleWriter::Exec(Option_t* option)
{
  if (IsGoodEvent()) {
    if (1 == fVersion) { StraightLineShiftX(option); }
    if (2 == fVersion) { StraightLineShiftXY(option); }
  }
}

Bool_t FairTutorialDetMilleWriter::IsGoodEvent()
{
  // Check if each for the event there is maximum 1 hit per detector
  // station. In the moment we create tracks with all hits in the
  // event, so we have to check for this.
  // In the end the algorithm should be able to work also with
  // missing hits in some stations
  FairTutorialDetHit* hit;
  std::set<Int_t> detIdSet;
  std::set<Int_t>::iterator it;

  Int_t nHits = fHits->GetEntriesFast();
  for (Int_t iHit=0; iHit<nHits; ++iHit) {
    hit = (FairTutorialDetHit*) fHits->At(iHit);
    Int_t detId = hit->GetDetectorID();
    it = detIdSet.find(detId);
    if ( it == detIdSet.end() ) {
      detIdSet.insert(detId);
    } else {
      // find hit in already used detector station
      // this is not a good event
      return kFALSE;
    }
  }
  return kTRUE;
}

void FairTutorialDetMilleWriter::StraightLineShiftX(Option_t* option)
{
  fLogger->Info(MESSAGE_ORIGIN,"Exec Version2");

  const Int_t nLC = 2; // number of local parameters
  // two for track x-coordinate
  // x(z) = a1*z + a2
  // dx(z)/da1 = z
  // dx(z)/da2 = 1


  const Int_t nGL = 1; // number of global parameters per point
  // taken from millepede 1 dim example

  Float_t sigma = 0.1;

  Float_t* derLC = new Float_t[nLC]; // array of derivatives for local parameters
  Float_t* derGL = new Float_t[nGL]; // array of derivatives for global parameters

  Int_t* label = new Int_t[nGL]; // array of labels


  for (Int_t help = 0; help < nGL; help++) {
    derGL[help] = 0;
  }

  for (Int_t help = 0; help < nLC; help++) {
    derLC[help] = 0;
  }

  FairTrackParam* track = (FairTrackParam*) fTracks->At(0);

  //Extract Track parameters
  Double_t OffX = track->GetX();
  Double_t SlopeX = track->GetTx();

  Double_t residual;

  FairTutorialDetHit* hit;

  Int_t nHits = fHits->GetEntriesFast();
  for (Int_t iHit=0; iHit<nHits; ++iHit) {
    hit = (FairTutorialDetHit*) fHits->At(iHit);

    Float_t Z = hit->GetZ();
    Float_t hitX = hit->GetX();
    Float_t fitX = OffX + SlopeX * Z;
    LOG(INFO)<<"hitX, fitX: "<< hitX<<" ,"<<fitX<<FairLogger::endl;

    label[0] = iHit+1;

    derGL[0] = -1;

    derLC[0] = 1;
    derLC[1] = Z;

    residual = fitX - hitX;
    LOG(INFO)<<"ResidualX: "<< residual<<FairLogger::endl;
    //call to Mille Writer
    fMille->mille(nLC,derLC,nGL,derGL,label,residual,sigma);

  }
  fMille->end();

}

// ---- Exec ----------------------------------------------------------
void FairTutorialDetMilleWriter::StraightLineShiftXY(Option_t* option)
{
  fLogger->Info(MESSAGE_ORIGIN,"Exec Version2");

  const Int_t nLC = 4; // number of local parameters
  // two for track x-coordinate
  // x(z) = a1*z + a2
  // dx(z)/da1 = z
  // dx(z)/da2 = 1


  const Int_t nGL = 2; // number of global parameters per point
  // taken from millepede 1 dim example

  Float_t sigma = 0.1;

  Float_t* derLC = new Float_t[nLC]; // array of derivatives for local parameters
  Float_t* derGL = new Float_t[nGL]; // array of derivatives for global parameters

  Int_t* label = new Int_t[nGL]; // array of labels


  for (Int_t help = 0; help < nGL; help++) {
    derGL[help] = 0;
  }

  for (Int_t help = 0; help < nLC; help++) {
    derLC[help] = 0;
  }

  FairTrackParam* track = (FairTrackParam*) fTracks->At(0);

  //Extract Track parameters
  Double_t OffX = track->GetX();
  Double_t SlopeX = track->GetTx();
  Double_t OffY = track->GetY();
  Double_t SlopeY = track->GetTy();

  Double_t residual;

  FairTutorialDetHit* hit;

  Int_t nHits = fHits->GetEntriesFast();
  for (Int_t iHit=0; iHit<nHits; ++iHit) {
    hit = (FairTutorialDetHit*) fHits->At(iHit);

    Float_t Z = hit->GetZ();
    Float_t hitX = hit->GetX();
    Float_t fitX = OffX + SlopeX * Z;
    Float_t hitY = hit->GetY();
    Float_t fitY = OffY + SlopeY * Z;
    LOG(INFO)<<"hitX, fitX: "<< hitX<<" ,"<<fitX<<FairLogger::endl;

    label[0] = iHit+1;
    label[1] = iHit+101;

    derGL[0] = -1;
    derGL[1] = 0;

    derLC[0] = 1;
    derLC[1] = Z;
    derLC[2] = 0;
    derLC[3] = 0;

    residual = fitX - hitX;
    LOG(INFO)<<"ResidualX: "<< residual<<FairLogger::endl;
    //call to Mille Writer
    fMille->mille(nLC,derLC,nGL,derGL,label,residual,sigma);

    derGL[0] = 0;
    derGL[1] = -1;

    derLC[0] = 0;
    derLC[1] = 0;
    derLC[2] = 1;
    derLC[3] = Z;

    residual = fitY - hitY;
    LOG(INFO)<<"ResidualX: "<< residual<<FairLogger::endl;
    //call to Mille Writer
    fMille->mille(nLC,derLC,nGL,derGL,label,residual,sigma);

  }
  fMille->end();

}

// ---- Finish --------------------------------------------------------
void FairTutorialDetMilleWriter::Finish()
{
  fLogger->Debug(MESSAGE_ORIGIN,"Finish of FairTutorialDetMilleWriter");
}

ClassImp(FairTutorialDetMilleWriter)
