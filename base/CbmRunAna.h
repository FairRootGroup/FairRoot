#ifndef CBMRUNANA_H
#define CBMRUNANA_H


/**
 * Configure the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "CbmRun.h"
#include "TObjArray.h"
#include "TString.h"
#include "TFile.h"
#include <iostream>
#include <list>
#include <map>

class CbmRuntimeDb;
class CbmEventHeader;
class CbmField;

class CbmRunAna : public CbmRun {

public:

    static CbmRunAna *Instance();
    virtual ~CbmRunAna();
    CbmRunAna();

    void        AddFriend(TString fName);
    void        AddFriend(TFile *f ) {  FriendFileList->Add(f);}
    void        AddAndMerge( const char* fName );
    void        AddAndMerge(TFile *f ) { MergedFileList->Add(f);}    
    void        Init();
    void        Run(Int_t NStart ,Int_t NStop);
    void 	Run(Long64_t entry);
    /** the dummy run does not check the evt header or the parameters!! */
    void 	DummyRun(Int_t NStart ,Int_t NStop);
    TFile*      SetInputFile(TString fname);
    void        SetInputFile(TFile *f);
    TObjArray * GetListOfMergedFile() { return MergedFileList;}
    TObjArray * GetListOfFriendFile() { return FriendFileList;}
    void        SetWildcard(TString Wildcard) {fWildcard = Wildcard;}
    void        DumpInputFileStruct();
    void        AddFile(TString name);
    std::map <TString, std::list<TString> * > GetFileStructure() { return fInputFileStruct;}
    TString     GetCurrentFileName() { return fCurrentFileName;}
    TString     GetNextFileName();
    void        LoadGeometry(){LoadGeo=kTRUE;}
    void   	Reinit(UInt_t runId);
    UInt_t 	getRunId(){return fRunId;}
    std::list <TString>  GetChainList() {return fChainList;}
    /** Get the magnetic field **/
    CbmField*   GetField(){return fField; }
    void 	SetField (CbmField *ffield ) {fField=ffield ;}
    TFile      *GetInputFile(){return InputFile; }
    void SetContainerStatic() {
        fStatic=kTRUE;
        std::cout << "-I- CbmRunAna : Parameter Cont. initialisation is static"
              << std::endl;

    }
 
private:

    CbmRunAna(const CbmRunAna &M);
    CbmRunAna& operator= (const  CbmRunAna&) {return *this;}
    TObjArray*            FriendFileList; 
    TObjArray*            MergedFileList; 
    TFile*                InputFile;
    TString               fCurrentFileName;//!
    TString               fWildcard;//!
    std::list<TString>         fChainList;//!
    std::list<TString>::iterator current;//!
    std::map<TString, std::list<TString>* > fInputFileStruct; //!
    static CbmRunAna*        fgRinstance;
    Bool_t                LoadGeo;
    CbmEventHeader *      fEvtHeader;//!
    CbmRuntimeDb*         fRtdb;//!
    UInt_t                 fRunId;//!
     /** true for static initialisation of parameters */
    Bool_t                fStatic;//!
    CbmField*   fField;
    ClassDef(CbmRunAna ,1)

};
#endif //CBMRUNANA_H
