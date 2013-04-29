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

    void Material(Int_t&, const char*, Double_t, Double_t, Double_t, Double_t, Double_t, Float_t*, Int_t) {StopExecution();}
    void Material(Int_t&, const char*, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t*, Int_t) {StopExecution();}
    void Mixture(Int_t&, const char*, Float_t*, Float_t*, Double_t, Int_t, Float_t*) {StopExecution();}
    void Mixture(Int_t&, const char*, Double_t*, Double_t*, Double_t, Int_t, Double_t*) {StopExecution();}
    void Medium(Int_t&, const char*, Int_t, Int_t, Int_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t, Float_t*, Int_t) {StopExecution();}
    virtual void Medium(Int_t&, const char*, Int_t, Int_t, Int_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t*, Int_t) {StopExecution();}
    virtual void Matrix(Int_t&, Double_t, Double_t, Double_t, Double_t, Double_t, Double_t) {StopExecution();}
    virtual void Gstpar(Int_t, const char*, Double_t) {StopExecution();}
    virtual Int_t Gsvolu(const char*, const char*, Int_t, Float_t*, Int_t) {StopExecution();}
    virtual Int_t Gsvolu(const char*, const char*, Int_t, Double_t*, Int_t) {StopExecution();}
    virtual void Gsdvn(const char*, const char*, Int_t, Int_t) {StopExecution();}
    virtual void Gsdvn2(const char*, const char*, Int_t, Int_t, Double_t, Int_t) {StopExecution();}
    virtual void Gsdvt(const char*, const char*, Double_t, Int_t, Int_t, Int_t) {StopExecution();}
    virtual void Gsdvt2(const char*, const char*, Double_t, Int_t, Double_t, Int_t, Int_t) {StopExecution();}
    virtual void Gfmate(Int_t, char*, Float_t&, Float_t&, Float_t&, Float_t&, Float_t&, Float_t*, Int_t&) {StopExecution();}
    virtual void Gfmate(Int_t, char*, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t*, Int_t&) {StopExecution();}
    virtual void Gckmat(Int_t, char*) {StopExecution();}
    virtual void Gsord(const char*, Int_t) {StopExecution();}
    virtual void Gspos(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*) {StopExecution();}
    virtual void Gsposp(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*, Float_t*, Int_t) {StopExecution();}
    virtual void Gsposp(const char*, Int_t, const char*, Double_t, Double_t, Double_t, Int_t, const char*, Double_t*, Int_t) {StopExecution();}
    virtual void Gsbool(const char*, const char*) {StopExecution();}
    virtual void SetCerenkov(Int_t, Int_t, Float_t*, Float_t*, Float_t*, Float_t*) {StopExecution();}
    virtual void SetCerenkov(Int_t, Int_t, Double_t*, Double_t*, Double_t*, Double_t*) {StopExecution();}
    virtual void DefineOpSurface(const char*, EMCOpSurfaceModel, EMCOpSurfaceType, EMCOpSurfaceFinish, Double_t) {StopExecution();}
    virtual void SetBorderSurface(const char*, const char*, int, const char*, int, const char*) {StopExecution();}
    virtual void SetSkinSurface(const char*, const char*, const char*) {StopExecution();}
    virtual void SetMaterialProperty(Int_t, const char*, Int_t, Double_t*, Double_t*) {StopExecution();}
    virtual void SetMaterialProperty(Int_t, const char*, Double_t) {StopExecution();}
    virtual void SetMaterialProperty(const char*, const char*, Int_t, Double_t*, Double_t*) {StopExecution();}
    virtual Bool_t GetTransformation(const TString&, TGeoHMatrix&) {StopExecution();}
    virtual Bool_t GetShape(const TString&, TString&, TArrayD&) {StopExecution();}
    virtual Bool_t GetMaterial(const TString&, TString&, Int_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, TArrayD&) {StopExecution();}
    virtual Bool_t GetMedium(const TString&, TString&, Int_t&, Int_t&, Int_t&, Int_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, Double_t&, TArrayD&) {StopExecution();}
    virtual void WriteEuclid(const char*, const char*, Int_t, Int_t) {StopExecution();}
    virtual void SetUserParameters(Bool_t) {StopExecution();}
    virtual const char* VolName(Int_t) const {StopExecution();}
    virtual Int_t MediumId(const char*) const {StopExecution();}
    virtual Int_t NofVolumes() const {StopExecution();}
    virtual Int_t VolId2Mate(Int_t) const {StopExecution();}
    virtual Int_t NofVolDaughters(const char*) const {StopExecution();}
    virtual const char* VolDaughterName(const char*, Int_t) const {StopExecution();}
    virtual Int_t VolDaughterCopyNo(const char*, Int_t) const {StopExecution();}
    virtual Bool_t SetCut(const char*, Double_t) {StopExecution();}
    virtual Bool_t SetProcess(const char*, Int_t) {StopExecution();}
    virtual Bool_t DefineParticle(Int_t, const char*, TMCParticleType, Double_t, Double_t, Double_t) {StopExecution();}
    virtual Bool_t DefineParticle(Int_t, const char*, TMCParticleType, Double_t, Double_t, Double_t, const TString&, Double_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Int_t, Bool_t, Bool_t, const TString&, Int_t, Double_t, Double_t) {StopExecution();}
    virtual Bool_t DefineIon(const char*, Int_t, Int_t, Int_t, Double_t, Double_t) {StopExecution();}
    virtual Bool_t SetDecayMode(Int_t, Float_t*, Int_t (*)[3]) {StopExecution();}
    virtual Double_t Xsec(char*, Double_t, Int_t, Int_t) {StopExecution();}
    virtual Int_t IdFromPDG(Int_t) const {StopExecution();}
    virtual Int_t PDGFromId(Int_t) const {StopExecution();}
    virtual TString ParticleName(Int_t) const {StopExecution();}
    virtual Double_t ParticleMass(Int_t) const {StopExecution();}
    virtual Double_t ParticleCharge(Int_t) const {StopExecution();}
    virtual Double_t ParticleLifeTime(Int_t) const {StopExecution();}
    virtual TMCParticleType ParticleMCType(Int_t) const {StopExecution();}
    virtual void StopTrack() {StopExecution();}
    virtual void StopEvent() {StopExecution();}
    virtual void StopRun() {StopExecution();}
    virtual void SetMaxStep(Double_t) {StopExecution();}
    virtual void SetMaxNStep(Int_t) {StopExecution();}
    virtual void SetUserDecay(Int_t) {StopExecution();}
    virtual void ForceDecayTime(Float_t) {StopExecution();}
    virtual Int_t CurrentVolID(Int_t&) const;
    virtual Int_t CurrentVolOffID(Int_t, Int_t&) const;
    virtual const char* CurrentVolName() const {StopExecution();}
    virtual const char* CurrentVolOffName(Int_t) const {StopExecution();}
    virtual const char* CurrentVolPath() {StopExecution();}
    virtual Int_t CurrentMaterial(Float_t&, Float_t&, Float_t&, Float_t&, Float_t&) const {StopExecution();}
    virtual Int_t CurrentMedium() const {StopExecution();}
    virtual Int_t CurrentEvent() const {StopExecution();}
    virtual void Gmtod(Float_t*, Float_t*, Int_t) {StopExecution();}
    virtual void Gmtod(Double_t*, Double_t*, Int_t) {StopExecution();}
    virtual void Gdtom(Float_t*, Float_t*, Int_t) {StopExecution();}
    virtual void Gdtom(Double_t*, Double_t*, Int_t) {StopExecution();}
    virtual Double_t MaxStep() const {StopExecution();}
    virtual Int_t GetMaxNStep() const {StopExecution();}
    virtual void TrackPosition(TLorentzVector&) const {StopExecution();}
    virtual void TrackPosition(Double_t&, Double_t&, Double_t&) const {StopExecution();}
    virtual void TrackMomentum(TLorentzVector&) const {StopExecution();}
    virtual void TrackMomentum(Double_t&, Double_t&, Double_t&, Double_t&) const {StopExecution();}
    virtual Double_t TrackStep() const {StopExecution();}
    virtual Double_t TrackLength() const {StopExecution();}
    virtual Double_t TrackTime() const {StopExecution();}
    virtual Double_t Edep() const {StopExecution();}
    virtual Int_t TrackPid() const {StopExecution();}
    virtual Double_t TrackCharge() const {StopExecution();}
    virtual Double_t TrackMass() const {StopExecution();}
    virtual Double_t Etot() const {StopExecution();}
    virtual Bool_t IsNewTrack() const {StopExecution();}
    virtual Bool_t IsTrackInside() const {StopExecution();}
    virtual Bool_t IsTrackEntering() const {StopExecution();}
    virtual Bool_t IsTrackExiting() const {StopExecution();}
    virtual Bool_t IsTrackOut() const {StopExecution();}
    virtual Bool_t IsTrackDisappeared() const {StopExecution();}
    virtual Bool_t IsTrackStop() const {StopExecution();}
    virtual Bool_t IsTrackAlive() const {StopExecution();}
    virtual Int_t NSecondaries() const {StopExecution();}
    virtual void GetSecondary(Int_t, Int_t&, TLorentzVector&, TLorentzVector&) {StopExecution();}
    virtual TMCProcess ProdProcess(Int_t) const {StopExecution();}
    virtual Int_t StepProcesses(TArrayI&) const {StopExecution();}
    virtual Bool_t SecondariesAreOrdered() const {StopExecution();}
    virtual void Init() {StopExecution();}
    virtual void BuildPhysics() {StopExecution();}
    virtual void ProcessEvent() {StopExecution();}
    virtual Bool_t ProcessRun(Int_t) {StopExecution();}
    virtual void InitLego() {StopExecution();}
    virtual void SetCollectTracks(Bool_t) {StopExecution();}
    virtual Bool_t IsCollectTracks() const {StopExecution();}

  protected:
    TGeoMCGeometry*  fMCGeo;
    Bool_t           fImportRootGeometry;
    FairLogger*      fLogger;
  private:
    ClassDef(FairMockVirtualMC,1)  //C++ interface to Geant basic routines
};

#endif
