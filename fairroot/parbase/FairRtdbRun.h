/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRTDBRUN_H
#define FAIRRTDBRUN_H

#include <Rtypes.h>    // for Int_t, Text_t, UInt_t, etc
#include <TNamed.h>    // for TNamed
#include <TString.h>   // for TString
#include <iosfwd>      // for fstream
#include <stdio.h>     // for sprintf, sscanf

class TList;
using std::fstream;

class FairParVersion : public TNamed
{
  protected:
    Int_t inputVersions[3];   //! version of the parameter container in the 2 possible inputs
    Int_t rootVersion;        // version of the parameter container in the ROOT output file

  public:
    FairParVersion()
        : TNamed()
        , rootVersion(0)
    {}
    FairParVersion(const char* name);
    ~FairParVersion() {}
    void setInputVersion(Int_t v = -1, Int_t i = 0)
    {
        if (i >= 0 && i < 3) {
            inputVersions[i] = v;
        }
    }
    Int_t getInputVersion(Int_t i) const
    {
        if (i >= 0 && i < 3) {
            return inputVersions[i];
        } else {
            return -1;
        }
    }
    void resetInputVersions()
    {
        for (Int_t i = 0; i < 3; i++) {
            inputVersions[i] = -1;
        }
    }
    void setRootVersion(Int_t v) { rootVersion = v; }
    Int_t getRootVersion() const { return rootVersion; }
    ClassDefOverride(FairParVersion, 1);   // Class for parameter versions
};

class FairRtdbRun : public TNamed
{
  protected:
    TList* parVersions;   // List of container names with the versions
    TString refRun;       //! name of the reference run for initialization

  public:
    FairRtdbRun();
    FairRtdbRun(const Text_t* name, const Text_t* refName = "");
    FairRtdbRun(Int_t r, Int_t rr = -1);
    FairRtdbRun(FairRtdbRun& run);
    ~FairRtdbRun();
    inline UInt_t getRunId();
    void addParVersion(FairParVersion* pv);
    FairParVersion* getParVersion(const Text_t* name);
    TList* getParVersions() { return parVersions; }
    const Text_t* getRefRun() { return refRun.Data(); }
    void setRefRun(Text_t* s) { refRun = s; }
    inline void setRefRun(Int_t r);
    void resetInputVersions();
    void resetOutputVersions();
    void print();
    void write(std::fstream&);

    void ls(Option_t* option = "") const override;

  private:
    FairRtdbRun& operator=(const FairRtdbRun&);

    ClassDefOverride(FairRtdbRun, 1);   // Class for parameter version management of a run
};

// -------------------- inlines ---------------------------

inline UInt_t FairRtdbRun::getRunId()
{
    UInt_t r;
    sscanf(GetName(), "%i", &r);
    return r;
}

inline void FairRtdbRun::setRefRun(Int_t r)
{
    if (r == -1) {
        refRun = "";
    } else {
        char name[255];
        sprintf(name, "%i", r);
        refRun = name;
    }
}

#endif /* !FAIRRTDBRUN_H */
