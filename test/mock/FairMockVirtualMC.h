/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef Fair_Mock_Virtual_MC
#define Fair_Mock_Virtual_MC

#include "TVirtualMC.h"
#include "TGeoMCGeometry.h"
#include "FairLogger.h"

class FairMockVirtualMC : public TVirtualMC
{

  public:
    FairMockVirtualMC();
    FairMockVirtualMC(const char* title, Int_t nwgeant=0);
    virtual ~FairMockVirtualMC();

    //  virtual void LoadAddress();
    //  virtual Bool_t  IsRootGeometrySupported() const {return kTRUE;}

    Int_t VolId(const Text_t* name) const;
    void  SetRootGeometry();
    void StopExecution() const;

    void Material(Int_t&, const char*, Double_t, Double_t, Double_t, Double_t, Double_t, Float_t*, Int_t) {StopExecution(); return;}
    void Material(Int_t&, const char*, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t*, Int_t) {StopExecution(); return;}
    void Mixture(Int_t&, const char*, Float_t*, Float_t*, Double_t, Int_t, Float_t*) {StopExecution(); return;}
    void Mixture(Int_t&, const char*, Double_t*, Double_t*, Double_t, Int_t, Double_t*) {StopExecution(); return;}
    void Medium(Int_t&, const char*, Int_t, Int_t, Int_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t, Float_t*, Int_t) {StopExecution(); return;}
    virtual void Medium(Int_t&, const char*, Int_t, Int_t, Int_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t*, Int_t) {StopExecution(); return;}
    virtual void Matrix(Int_t&, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t) {StopExecution(); return;}
    virtual void Gstpar(Int_t, const char*, Double_t) {StopExecution(); return;}
    virtual Int_t Gsvolu(const char*, const char*, Int_t, Float_t*, Int_t) {StopExecution(); return -1;}
    virtual Int_t Gsvolu(const char*, const char*, Int_t, Double_t*, Int_t) {StopExecution(); return -1;}
    virtual void Gsdvn(const char*, const char*, Int_t, Int_t) {StopExecution(); return;}
    virtual void Gsdvn2(const char*, const char*, Int_t, Int_t, Double_t, Int_t) {StopExecution(); return;}
    virtual void Gsdvt(const char*, const char*, Double_t, Int_t, Int_t, Int_t) {StopExecution(); return;}
    virtual void Gsdvt2(const char*, const char*, Double_t, Int_t, Double_t, Int_t, Int_t) {StopExecution(); return;}
    virtual void Gfmate(Int_t, char*, Float_t&, Float_t&, Float_t&, Float_t&, Float_t&, Float_t*, Int_t&) {StopExecution(); return;}
    virtual void Gfmate(Int_t, char*, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t*, Int_t&) {StopExecution(); return;}
    virtual void Gckmat(Int_t, char*) {StopExecution(); return;}
    virtual void Gsord(const char*, Int_t) {StopExecution(); return;}
    virtual void Gspos(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*) {StopExecution(); return;}
    virtual void Gsposp(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*, Float_t*, Int_t) {StopExecution(); return;}
    virtual void Gsposp(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*, Double_t*, Int_t) {StopExecution(); return;}
    virtual void Gsbool(const char*, const char*) {StopExecution(); return;}
    virtual void SetCerenkov(Int_t, Int_t, Float_t*, Float_t*, Float_t*, Float_t*) {StopExecution(); return;}
    virtual void SetCerenkov(Int_t, Int_t, Double_t*, Double_t*, Double_t*, Double_t*) {StopExecution(); return;}
    virtual void DefineOpSurface(const char*, EMCOpSurfaceModel, EMCOpSurfaceType, EMCOpSurfaceFinish, Double_t) {StopExecution(); return;}
    virtual void SetBorderSurface(const char*, const char*, int, const char*, int, const char*) {StopExecution(); return;}
    virtual void SetSkinSurface(const char*, const char*, const char*) {StopExecution(); return;}
    virtual void SetMaterialProperty(Int_t, const char*, Int_t, Double_t*, Double_t*) {StopExecution(); return;}
    virtual void SetMaterialProperty(Int_t, const char*, Double_t) {StopExecution(); return;}
    virtual void SetMaterialProperty(const char*, const char*, Int_t, Double_t*, Double_t*) {StopExecution(); return;}
    virtual Bool_t GetTransformation(const TString&, TGeoHMatrix&) {StopExecution(); return kFALSE;}
    virtual Bool_t GetShape(const TString&, TString&, TArrayD&) {StopExecution(); return kFALSE;}
    virtual Bool_t GetMaterial(const TString&, TString&, Int_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, TArrayD&) {StopExecution();  return kFALSE;}
    virtual Bool_t GetMedium(const TString&, TString&, Int_t&, Int_t&, Int_t&, Int_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, TArrayD&) {StopExecution();  return kFALSE;}
    virtual void WriteEuclid(const char*, const char*, Int_t, Int_t) {StopExecution(); return;}
    virtual void SetUserParameters(Bool_t) {StopExecution(); return;}
    virtual const char* VolName(Int_t) const {StopExecution(); return "";}
    virtual Int_t MediumId(const char*) const {StopExecution(); return -1;}
    virtual Int_t NofVolumes() const {StopExecution(); return -1;}
    virtual Int_t VolId2Mate(Int_t) const {StopExecution(); return -1;}
    virtual Int_t NofVolDaughters(const char*) const {StopExecution(); return -1;}
    virtual const char* VolDaughterName(const char*, Int_t) const {StopExecution(); return "";}
    virtual Int_t VolDaughterCopyNo(const char*, Int_t) const {StopExecution(); return -1;}
    virtual Bool_t SetCut(const char*, Double_t) {StopExecution(); return kFALSE;}
    virtual Bool_t SetProcess(const char*, Int_t) {StopExecution(); return kFALSE;}
    virtual Bool_t DefineParticle(Int_t, const char*, TMCParticleType, Double_t, Double_t, Double_t) {StopExecution(); return kFALSE;}
    virtual Bool_t DefineParticle(Int_t, const char*, TMCParticleType, Double_t, Double_t, Double_t, const TString&, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Bool_t, Bool_t, const TString&, Int_t, Double_t, Double_t) {StopExecution();  return kFALSE;}
    virtual Bool_t DefineIon(const char*, Int_t, Int_t, Int_t, Double_t, Double_t) {StopExecution(); return kFALSE;}
    virtual Bool_t SetDecayMode(Int_t, Float_t*, Int_t (*)[3]) {StopExecution(); return kFALSE;}
    virtual Double_t Xsec(char*, Double_t, Int_t, Int_t) {StopExecution(); return -1.;}
    virtual Int_t IdFromPDG(Int_t) const {StopExecution(); return -1;}
    virtual Int_t PDGFromId(Int_t) const {StopExecution();  return -1;}
    virtual TString ParticleName(Int_t) const {StopExecution(); return "";}
    virtual Double_t ParticleMass(Int_t) const {StopExecution(); return -1.;}
    virtual Double_t ParticleCharge(Int_t) const {StopExecution(); return -1.;}
    virtual Double_t ParticleLifeTime(Int_t) const {StopExecution(); return -1.;}
    virtual TMCParticleType ParticleMCType(Int_t) const {StopExecution(); return kPTUndefined;}
    virtual void StopTrack() {StopExecution();  return;}
    virtual void StopEvent() {StopExecution(); return;}
    virtual void StopRun() {StopExecution(); return;}
    virtual void SetMaxStep(Double_t) {StopExecution(); return;}
    virtual void SetMaxNStep(Int_t) {StopExecution(); return;}
    virtual void SetUserDecay(Int_t) {StopExecution(); return;}
    virtual void ForceDecayTime(Float_t) {StopExecution(); return;}
    virtual Int_t CurrentVolID(Int_t&) const;
    virtual Int_t CurrentVolOffID(Int_t, Int_t&) const;
    virtual const char* CurrentVolName() const {StopExecution(); return "";}
    virtual const char* CurrentVolOffName(Int_t) const {StopExecution(); return "";}
    virtual const char* CurrentVolPath() {StopExecution(); return "";}
    virtual Int_t CurrentMaterial(Float_t&, Float_t&, Float_t&, Float_t&, Float_t&) const {StopExecution(); return -1;}
    virtual Int_t CurrentMedium() const {StopExecution(); return -1;}
    virtual Int_t CurrentEvent() const {StopExecution(); return -1;}
    virtual void Gmtod(Float_t*, Float_t*, Int_t) {StopExecution(); return;}
    virtual void Gmtod(Double_t*, Double_t*, Int_t) {StopExecution(); return;}
    virtual void Gdtom(Float_t*, Float_t*, Int_t) {StopExecution(); return;}
    virtual void Gdtom(Double_t*, Double_t*, Int_t) {StopExecution(); return;}
    virtual Double_t MaxStep() const {StopExecution(); return -1.;}
    virtual Int_t GetMaxNStep() const {StopExecution(); return -1;}
    virtual void TrackPosition(TLorentzVector&) const {StopExecution(); return;}
    virtual void TrackPosition(Double_t&, Double_t&, Double_t&) const {StopExecution(); return;}
    virtual void TrackMomentum(TLorentzVector&) const {StopExecution(); return;}
    virtual void TrackMomentum(Double_t&, Double_t&, Double_t&, Double_t&) const {StopExecution(); return;}
    virtual Double_t TrackStep() const {StopExecution(); return -1.;}
    virtual Double_t TrackLength() const {StopExecution(); return -1.;}
    virtual Double_t TrackTime() const {StopExecution(); return -1.;}
    virtual Double_t Edep() const {StopExecution(); return -1.;}
    virtual Int_t TrackPid() const {StopExecution(); return -1;}
    virtual Double_t TrackCharge() const {StopExecution(); return -1.;}
    virtual Double_t TrackMass() const {StopExecution(); return -1.;}
    virtual Double_t Etot() const {StopExecution(); return -1.;}
    virtual Bool_t IsNewTrack() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackInside() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackEntering() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackExiting() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackOut() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackDisappeared() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackStop() const {StopExecution(); return kFALSE;}
    virtual Bool_t IsTrackAlive() const {StopExecution(); return kFALSE;}
    virtual Int_t NSecondaries() const {StopExecution(); return -1;}
    virtual void GetSecondary(Int_t, Int_t&, TLorentzVector&, TLorentzVector&) {StopExecution(); return;}
    virtual TMCProcess ProdProcess(Int_t) const {StopExecution(); return kPNoProcess;}
    virtual Int_t StepProcesses(TArrayI&) const {StopExecution(); return -1;}
    virtual Bool_t SecondariesAreOrdered() const {StopExecution(); return kFALSE;}
    virtual void Init() {StopExecution(); return;}
    virtual void BuildPhysics() {StopExecution(); return;}
    virtual void ProcessEvent() {StopExecution(); return;}
    virtual Bool_t ProcessRun(Int_t) {StopExecution(); return kFALSE;}
    virtual void InitLego() {StopExecution(); return;}
    virtual void SetCollectTracks(Bool_t) {StopExecution(); return;}
    virtual Bool_t IsCollectTracks() const {StopExecution(); return kFALSE;}

  protected:
    TGeoMCGeometry*  fMCGeo;
    Bool_t           fImportRootGeometry;
    FairLogger*      fLogger;
  private:
    ClassDef(FairMockVirtualMC,1)  //C++ interface to Geant basic routines
};

#endif
