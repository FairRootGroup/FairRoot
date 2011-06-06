#ifndef FAIRRTDBRUN_H
#define FAIRRTDBRUN_H

#include "TNamed.h"
#include "TList.h"
#include "TString.h"

//#include <iostream>
//#include <iomanip>
#include <fstream>

class FairParVersion : public TNamed
{
  protected:
    Int_t inputVersions[3]; //! version of the parameter container in the 2 possible inputs
    Int_t rootVersion;      // version of the parameter container in the ROOT output file
  public:
    FairParVersion() : TNamed(),rootVersion(0) {}
    FairParVersion(Text_t* name);
    ~FairParVersion() {}
    void setInputVersion(Int_t v=-1,Int_t i=0) {
      if (i>=0 && i<3) { inputVersions[i]=v; }
    }
    Int_t getInputVersion(Int_t i) {
      if (i>=0 && i<3) { return inputVersions[i]; }
      else { return -1; }
    }
    void resetInputVersions() {
      for(Int_t i=0; i<3; i++) {inputVersions[i]=-1;}
    }
    void setRootVersion(Int_t v) {rootVersion=v;}
    Int_t getRootVersion() {return rootVersion;}
    ClassDef(FairParVersion,1) // Class for parameter versions
};

class FairRtdbRun : public TNamed
{
  protected:
    TList* parVersions;   // List of container names with the versions
    TString refRun;       //! name of the reference run for initialization
  public:
    FairRtdbRun();
    FairRtdbRun(const Text_t* name,const Text_t* refName="");
    FairRtdbRun(Int_t r,Int_t rr=-1);
    FairRtdbRun(FairRtdbRun& run);
    ~FairRtdbRun();
    inline Int_t getRunId(void);
    void addParVersion(FairParVersion* pv);
    FairParVersion* getParVersion(const Text_t* name);
    TList* getParVersions() {return parVersions;}
    const Text_t* getRefRun() {return refRun.Data();}
    void setRefRun(Text_t* s) {refRun=s;}
    inline void setRefRun(Int_t r);
    void resetInputVersions();
    void resetOutputVersions();
    void print();
    void write(fstream&);

  private:
    FairRtdbRun& operator=(const FairRtdbRun&);

    ClassDef(FairRtdbRun,1) // Class for parameter version management of a run
};

// -------------------- inlines ---------------------------

inline Int_t FairRtdbRun::getRunId(void)
{
  Int_t r;
  sscanf(GetName(),"%i",&r);
  return r;
}

inline void FairRtdbRun::setRefRun(Int_t r)
{
  if (r==-1) { refRun=""; }
  else {
    char name[255];
    sprintf(name,"%i",r);
    refRun=name;
  }
}

#endif  /* !FAIRRTDBRUN_H */

