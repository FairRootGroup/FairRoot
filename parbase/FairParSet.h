#ifndef FAIRPARSET_H
#define FAIRPARSET_H

#include "FairLogger.h"
#include "TNamed.h"
//#include "TArrayI.h"

class FairParIo;

class FairParSet : public TNamed
{
  protected:
    TString detName;         //! name of the detector the container belongs to
    Int_t versions[3];       //! versions of container in the 2 possible inputs
    Bool_t status;           //! static flag
    Bool_t changed;          //! flag is kTRUE if parameters have changed
    TString paramContext;    // Context/purpose for parameters and conditions
    TString author;          // Author of parameters
    TString description ;    // Description of parameters
    /** Fair Logger */
    FairLogger*  fLogger;  //!
  public:
    FairParSet(const char* name="",const char* title="",const char* context="");
    virtual ~FairParSet() {}
    virtual Bool_t init();
    virtual Bool_t init(FairParIo* io) { return kFALSE; }
    virtual Int_t write();
    virtual Int_t write(FairParIo*) { return kFALSE; }
    virtual void clear() {}
    virtual void print();
    const char* getDetectorName() {return detName.Data();}
    void resetInputVersions();

    void setInputVersion(Int_t v=-1,Int_t i=0) {
      if (i>=0 && i<3) { versions[i]=v; }
    }
    Int_t getInputVersion(Int_t i) {
      if (i>=0 && i<3) { return versions[i]; }
      else { return 0; }
    }
    void setStatic(Bool_t flag=kTRUE) {status=flag;}
    Bool_t isStatic() {return status;}
    void setChanged(Bool_t flag=kTRUE) {changed=flag;}
    Bool_t hasChanged() {return changed;}

    const char* getParamContext() const { return paramContext.Data(); }

    void setAuthor(const char* s) {author=s;}
    const char* getAuthor() const { return author.Data(); }

    void setDescription(const char* s) {description=s;}
    const char* getDescription() const { return description.Data(); }

    void copyComment(FairParSet& r) {
      author=r.getAuthor();
      description=r.getDescription();
    }

  private:

    FairParSet& operator=(const FairParSet&);
    FairParSet(const FairParSet&);

    ClassDef(FairParSet,1) // Base class for all parameter containers
};

#endif  /* !FAIRPARSET_H */

