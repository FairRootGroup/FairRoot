/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARSET_H
#define FAIRPARSET_H

#include <Rtypes.h>   // for Int_t, Bool_t, etc
#include <TObject.h>
#include <TString.h>   // for TString

class FairParIo;

class FairParSet : public TObject
{
  protected:
    TString fName;          //
    TString fTitle;         //
    TString detName;        //! name of the detector the container belongs to
    int versions[3];        //! versions of container in the 2 possible inputs
    bool status;            //! static flag
    bool changed;           //! flag is kTRUE if parameters have changed
    bool owned;             //! if flag is KTRUE FairDB has the par. class ownership
    bool creationMode;      //! allow creation mode, it suppresses error message in the init
    TString paramContext;   // Context/purpose for parameters and conditions
    TString author;         // Author of parameters
    TString description;    // Description of parameters

  public:
    FairParSet(const char* name = "", const char* title = "", const char* context = "", bool owner = false);
    virtual ~FairParSet() {}

    const char* GetName() const override { return fName.Data(); }
    const char* GetTitle() const override { return fTitle.Data(); }

    virtual Bool_t init();
    virtual Bool_t init(FairParIo*) { return kFALSE; }
    virtual Int_t write();
    virtual Int_t write(FairParIo*) { return kFALSE; }
    virtual void clear();
    virtual void print();

    const char* getDetectorName() { return detName.Data(); }
    void resetInputVersions();

    void setInputVersion(int v = -1, int i = 0)
    {
        if (i >= 0 && i < 3) {
            versions[i] = v;
        }
    }
    int getInputVersion(int i)
    {
        if (i >= 0 && i < 3) {
            return versions[i];
        } else {
            return 0;
        }
    }

    void setStatic(bool flag = kTRUE) { status = flag; }
    bool isStatic() { return status; }

    void setOwnership(bool flag = kTRUE) { owned = flag; }
    bool isOwned() { return owned; }

    void setChanged(bool flag = kTRUE) { changed = flag; }
    bool hasChanged() { return changed; }

    void setCreationMode(bool flag = true) { creationMode = flag; }
    bool isCreationMode() { return creationMode; }

    const char* getParamContext() const { return paramContext.Data(); }

    void setAuthor(const char* s) { author = s; }
    const char* getAuthor() const { return author.Data(); }

    void setDescription(const char* s) { description = s; }
    const char* getDescription() const { return description.Data(); }

    void copyComment(FairParSet& r)
    {
        author = r.getAuthor();
        description = r.getDescription();
    }

    // TODO These two methods are not used in FairRoot at all.
    // They probably should be marked deprecated (or final, or = delete)
    // and later removed.
    virtual void fill(UInt_t){};
    virtual void store(UInt_t){};

    FairParSet& operator=(const FairParSet&);
    FairParSet(const FairParSet&);

    ClassDefOverride(FairParSet, 3);   // Base class for all parameter containers
};

#endif /* !FAIRPARSET_H */
