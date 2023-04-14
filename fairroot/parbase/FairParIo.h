/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARIO_H
#define FAIRPARIO_H

#include <Rtypes.h>    // for Bool_t, Text_t, etc
#include <TList.h>     // for TList
#include <TObject.h>   // for TObject
#include <TString.h>   // for TString

class FairDetParIo;
class FairRtdbRun;

class FairParIo : public TObject
{
  protected:
    TList* detParIoList;   // list of detector I/Os
    Bool_t autoWritable;   // flag indicating if automatic write is possible
    TString filename;

  public:
    FairParIo();
    ~FairParIo() override;
    virtual FairDetParIo* getDetParIo(const Text_t*);
    virtual void setDetParIo(FairDetParIo*);
    virtual void removeDetParIo(Text_t*);
    void setInputNumber(Int_t);
    virtual void close();

    // returns the filename
    const char* getFilename() { return filename.Data(); }

    // creates input/output class for a special detector and stores pointer
    // used only for Oracle input/output
    // (code in  class OraIo)
    virtual void setDetParIo(Text_t*) { ; }

    // prints information about input/output
    virtual void print();

    // checks if the input/output is open
    virtual Bool_t check() { return kFALSE; }

    // reads versions of parameter containers for an event file
    virtual void readVersions(FairRtdbRun*) { ; }

    // sets global file pointer in ROOT if input/output is a ROOT-file
    // (code in FairParRootFileIo)
    virtual void cd() {}

    // set and get for flag autoWritable
    void setAutoWritable(Bool_t f = kTRUE) { autoWritable = f; }
    Bool_t isAutoWritable() const { return autoWritable; }

  private:
    FairParIo(const FairParIo&);
    FairParIo& operator=(const FairParIo&);

    ClassDefOverride(FairParIo, 0);   // Base class for all parameter I/Os
};

#endif /* !FAIRPARIO_H */
