/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * FairOnlineSink.h
 *
 * @since 2018-02-01
 * @author R. Karabowicz
 */

#ifndef FAIRONLINESINK_H_
#define FAIRONLINESINK_H_

#include "FairSink.h"

#include <Rtypes.h>

#include <string>
#include <typeinfo>

class FairEventHeader;
class FairMQRunDevice;
class TObject;
class TTree;

class FairOnlineSink : public FairSink
{
  public:
    FairOnlineSink();
    virtual ~FairOnlineSink() {}

    virtual Bool_t    InitSink() { return kTRUE; }
    virtual void      Close() {}
    virtual void      Reset() {}

    virtual Sink_Type GetSinkType() { return kONLINESINK; }

    virtual void      FillEventHeader(FairEventHeader* /* feh */) {}

    virtual void      SetOutTree(TTree* /* fTree */) { return; }

    virtual void      Fill();

    virtual Int_t     Write(const char* /* name=0 */, Int_t /* option=0 */, Int_t /* bufsize=0 */) {return -1;}

    virtual void      RegisterImpl(const char* , const char* , void* ) {}
    virtual void      RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj) {}

    virtual void      WriteFolder() {}
    virtual bool      CreatePersistentBranchesAny() {return false;}

    virtual void      WriteObject(TObject* /* f */, const char*, Int_t /* option = 0 */) {}
    virtual void      WriteGeometry() {}

    virtual void        SetMQRunDevice(FairMQRunDevice* mrs) { fMQRunDevice = mrs;}
    virtual FairMQRunDevice*       GetMQRunDevice()   { return fMQRunDevice;}

    virtual FairSink*   CloneSink();

 private:
    FairMQRunDevice* fMQRunDevice;

    FairOnlineSink(const FairOnlineSink&);
    FairOnlineSink& operator=(const FairOnlineSink&);
};

#endif /* FAIRONLINESIK_H_ */
