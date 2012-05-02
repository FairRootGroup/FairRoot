//#ifndef FairMockVirtualMC
//#define FairMockVirtualMC

#include "TVirtualMC.h"
//#include "TMCProcess.h"
//#include "TMCParticleType.h"
#include "TGeoMCGeometry.h"

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

  protected:
    TGeoMCGeometry*  fMCGeo;
    Bool_t           fImportRootGeometry;

  private:
    ClassDef(FairMockVirtualMC,1)  //C++ interface to Geant basic routines
};

//#endif
