#ifndef FAIR_MOCK_MC_APPLICATION_H
#define FAIR_MOCK_MC_APPLICATION_H

#include "TVirtualMCApplication.h"
#include "TVirtualMC.h"

class FairMockMCApplication : public TVirtualMCApplication
{

  public:
    // Standard constructor
    FairMockMCApplication(const char* name, const char* title);

    // Default constructor
    FairMockMCApplication();

    // Destructor
    virtual ~FairMockMCApplication();

    // Static access method
    static FairMockMCApplication* Instance();

    //
    // methods
    //

    // Construct user geometry
    virtual void ConstructGeometry() {gMC->SetRootGeometry();}

    // Misalign user geometry (optional)
    virtual Bool_t MisalignGeometry() {return kFALSE;}

    // Define parameters for optical processes (optional)
    virtual void ConstructOpGeometry() {}

    // Initialize geometry
    // (Usually used to define sensitive volumes IDs)
    virtual void InitGeometry() {}

    // Add user defined particles (optional)
    virtual void AddParticles() {}

    // Add user defined ions (optional)
    virtual void AddIons() {}

    // Generate primary particles
    virtual void GeneratePrimaries() {};

    // Define actions at the beginning of the event
    virtual void BeginEvent() {};

    // Define actions at the beginning of the primary track
    virtual void BeginPrimary() {};

    // Define actions at the beginning of each track
    virtual void PreTrack() {};

    // Define action at each step
    virtual void Stepping() {};

    // Define actions at the end of each track
    virtual void PostTrack() {};

    // Define actions at the end of the primary track
    virtual void FinishPrimary() {};

    // Define actions at the end of the event
    virtual void FinishEvent() {};

    // Define maximum radius for tracking (optional)
    virtual Double_t TrackingRmax() const { return DBL_MAX; }

    // Define maximum z for tracking (optional)
    virtual Double_t TrackingZmax() const { return DBL_MAX; }

    // Calculate user field \a b at point \a x
    virtual void     Field(const Double_t* x, Double_t* b) const {;}

    // Define action at each step for Geane
    virtual void GeaneStepping() {;}

  private:
    FairMockMCApplication(const FairMockMCApplication&);
    FairMockMCApplication& operator=(const FairMockMCApplication&);

    ClassDef(FairMockMCApplication,1)  //Interface to MonteCarlo application
};


inline FairMockMCApplication* FairMockMCApplication::Instance()
{ return (FairMockMCApplication*)(TVirtualMCApplication::Instance());}


#endif

