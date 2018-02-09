/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * FairMQSimDevice.h
 *
 * @since 2018-02-01
 * @author R. Karabowicz
 */

#ifndef FAIRMQSIMDEVICE_H_
#define FAIRMQSIMDEVICE_H_

#include <string>

#include "FairSink.h"
#include "FairMQDevice.h"

class FairEventHeader;
class FairRunSim;
class TObjArray;
class FairField;
class FairParIo;
class FairPrimaryGenerator;

class FairMQSimDevice : public FairMQDevice, public FairSink
{
 public:
    FairMQSimDevice();
    virtual ~FairMQSimDevice();
  
    virtual Bool_t      InitSink();
    virtual void        Close();
    virtual void        Reset();

    virtual Sink_Type   GetSinkType() { return kONLINESINK; }

    virtual void        FillEventHeader(FairEventHeader* feh) {}

    virtual void        SetOutTree(TTree* fTree) { return; }

    virtual void        Fill();

    virtual Int_t       Write(const char* name=0, Int_t option=0, Int_t bufsize=0) {return -1;}

    virtual void        RegisterImpl(const char* , const char* , void* );
    virtual void        RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj);

    virtual void        WriteFolder() {}
    virtual bool        CreatePersistentBranchesAny() {return false;}

    virtual void        WriteObject(TObject* f, const char*, Int_t option = 0) {}
    virtual void        WriteGeometry() {}

    // ------ FairRunSim setters ------
    void SetNofEvents       (int64_t nofev)                 { fNofEvents = nofev;};
    void SetTransportName   (std::string str)               { fTransportName = str;};
    void SetMaterials       (std::string str)               { fMaterialsFile = str;};
    void SetMagneticField   (FairField* field)              { fMagneticField = field;};
    void SetDetectorArray   (TObjArray* array)              { fDetectorArray = array;};
    void SetGenerator       (FairPrimaryGenerator* primGen) { fPrimaryGenerator = primGen;};
    void SetStoreTraj       (bool flag=true)                { fStoreTrajFlag = flag;};
    void SetTaskArray       (TObjArray* array)              { fTaskArray = array;};
    void SetFirstParameter  (FairParIo* par)                { fFirstParameter  = par;};
    void SetSecondParameter (FairParIo* par)                { fSecondParameter = par;};
    void SetUserConfig      (const TString& Config)         { fUserConfig = Config;}
    void SetUserCuts        (const TString& Cuts)           { fUserCuts = Cuts;}
    // ------ ---------- -------- ------

 protected:
    virtual void InitTask();
    virtual void PreRun();
    virtual void PostRun();
    virtual bool ConditionalRun();

 private: 
    std::string fUpdateChannelName;

    FairRunSim*     fRunSim;
    // ------ FairRunSim settings ------
    int64_t               fNofEvents;
    std::string           fTransportName;
    std::string           fMaterialsFile;
    FairField*            fMagneticField;
    TObjArray*            fDetectorArray;
    FairPrimaryGenerator* fPrimaryGenerator;
    bool                  fStoreTrajFlag;
    TObjArray*            fTaskArray;
    FairParIo*            fFirstParameter;    // first (prefered) input for parameters
    FairParIo*            fSecondParameter;   // second input (used if not found in first input)
    TString               fUserConfig;        //!                  /** Macro for geant configuration*/
    TString               fUserCuts;          //!                  /** Macro for geant cuts*/
    // ------ ---------- -------- ------

    void UpdateParameterServer();
    void SendObject(TObject* obj, std::string chan);

    FairMQSimDevice(const FairMQSimDevice&);
    FairMQSimDevice& operator=(const FairMQSimDevice&);
};

#endif /* FAIRMQSIMDEVICE_H_ */
