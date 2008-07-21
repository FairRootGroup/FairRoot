#ifndef CBMRTDBRUN_H
#define CBMRTDBRUN_H

#include "TNamed.h"
#include "TList.h"
#include "TString.h"

//#include <iostream> 
//#include <iomanip>
#include <fstream>

class CbmParVersion : public TNamed {
protected:
  Int_t inputVersions[3]; //! version of the parameter container in the 2 possible inputs
  Int_t rootVersion;      // version of the parameter container in the ROOT output file
public:
  CbmParVersion() {}
  CbmParVersion(Text_t* name);
  ~CbmParVersion() {}
  void setInputVersion(Int_t v=-1,Int_t i=0) {
    if (i>=0 && i<3)  inputVersions[i]=v;
  }
  Int_t getInputVersion(Int_t i) {
    if (i>=0 && i<3) return inputVersions[i];
    else return -1;
  }
  void resetInputVersions() {
    for(Int_t i=0;i<3;i++) {inputVersions[i]=-1;}
  }
  void setRootVersion(Int_t v) {rootVersion=v;}
  Int_t getRootVersion() {return rootVersion;}
  ClassDef(CbmParVersion,1) // Class for parameter versions
};

class CbmRtdbRun : public TNamed {
protected:
  TList* parVersions;   // List of container names with the versions
  TString refRun;       //! name of the reference run for initialization
public:
  CbmRtdbRun();
  CbmRtdbRun(Text_t* name,Text_t* refName="");
  CbmRtdbRun(Int_t r,Int_t rr=-1);
  CbmRtdbRun(CbmRtdbRun &run);
  ~CbmRtdbRun();
  inline Int_t getRunId(void);
  void addParVersion(CbmParVersion *pv);
  CbmParVersion* getParVersion(Text_t* name);
  TList* getParVersions() {return parVersions;}
  const Text_t* getRefRun() {return refRun.Data();}
  void setRefRun(Text_t* s) {refRun=s;}
  inline void setRefRun(Int_t r);
  void resetInputVersions();
  void resetOutputVersions();
  void print();
  void write(fstream&);

  ClassDef(CbmRtdbRun,1) // Class for parameter version management of a run
};

// -------------------- inlines ---------------------------

inline Int_t CbmRtdbRun::getRunId(void) {
  Int_t r;
  sscanf(GetName(),"%i",&r);
  return r;
}

inline void CbmRtdbRun::setRefRun(Int_t r) {
  if (r==-1) refRun="";
  else {  
    char name[255];
    sprintf(name,"%i",r);
    refRun=name;
  }
}

#endif  /* !CBMRTDBRUN_H */

