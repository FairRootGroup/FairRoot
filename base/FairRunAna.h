#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H


/**
 * Configure the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"
#include "TObjArray.h"
#include "TString.h"
#include "TFile.h"
#include <iostream>
#include <list>
#include <map>

class FairRuntimeDb;
class FairEventHeader;
class FairField;

class FairRunAna : public FairRun {

public:

    static FairRunAna *Instance();
    virtual ~FairRunAna();
    FairRunAna();

    void        AddFriend(TString fName);
    void        AddFriend(TFile *f ) {  fFriendFileList->Add(f);}
    void        AddAndMerge( const char* fName );
    void        AddAndMerge(TFile *f ) { fMergedFileList->Add(f);}    
    void        Init();
    void        Run(Int_t NStart ,Int_t NStop);
    void 	    Run(Long64_t entry);
    /** the dummy run does not check the evt header or the parameters!! */
    void 	    DummyRun(Int_t NStart ,Int_t NStop);
    TFile*      SetInputFile(TString fname);
    void        SetInputFile(TFile *f);
    TObjArray * GetListOfMergedFile() { return fMergedFileList;}
    TObjArray * GetListOfFriendFile() { return fFriendFileList;}
    void        SetWildcard(TString Wildcard) {fWildcard = Wildcard;}
    void        DumpfInputFileStruct();
    void        AddFile(TString name);
    std::map <TString, std::list<TString> * > GetFileStructure() { return fInputFileStruct;}
    TString     GetCurrentFileName() { return fCurrentFileName;}
    TString     GetNextFileName();
    void        LoadGeometry(){fLoadGeo=kTRUE;}
    void   	Reinit(UInt_t runId);
    UInt_t 	getRunId(){return fRunId;}
    std::list <TString>  GetChainList() {return fChainList;}
    /** Get the magnetic field **/
    FairField*  GetField(){return fField; }
    void 	SetField (FairField *ffield ) {fField=ffield ;}
    TFile      *GetInputFile(){return fInputFile; }
    void 	SetGeomFile(const char *GeoFileName);
    TFile*      GetGeoFile(){return fInputGeoFile;}
    void SetContainerStatic() {
        fStatic=kTRUE;
        std::cout << "-I- FairRunAna : Parameter Cont. initialisation is static"
              << std::endl;

    }
 
private:

    FairRunAna(const FairRunAna &M);
    FairRunAna& operator= (const  FairRunAna&) {return *this;}
    TObjArray*                              fFriendFileList; 
    TObjArray*                              fMergedFileList; 
    TFile*                                  fInputFile;
    TFile*                                  fInputGeoFile;
    TString                                 fCurrentFileName;//!
    TString                                 fWildcard;//!
    std::list<TString>                      fChainList;//!
    std::list<TString>::iterator            fcurrent;//!
    std::map<TString, std::list<TString>* > fInputFileStruct; //!
    static FairRunAna*                      fgRinstance;
    Bool_t                                  fLoadGeo;
    FairEventHeader *                       fEvtHeader;//!
    FairRuntimeDb*                          fRtdb;//!
    UInt_t                                  fRunId;//!
     /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;
    ClassDef(FairRunAna ,1)

};

#endif //FAIRRUNANA_H
