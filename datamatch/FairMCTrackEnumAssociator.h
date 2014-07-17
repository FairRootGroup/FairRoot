/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MCTRACKENUMASSOCIATOR_H
#define MCTRACKENUMASSOCIATOR_H

// *************************************************************************
//  Author: Stefano Spataro            e-mail: spataro@to.infn.it
//
//  take all hits from tracks and create the corresponding PndTrackID object
//
// Created: 27-06-11
// Modified: Stefano Spataro
//
// *************************************************************************

#include "TClonesArray.h"

#include "FairTask.h"

#include "PndTrackID.h"


class PndMCTrackEnumAssociator : public FairTask
{

  public:

    PndMCTrackEnumAssociator(const char* name, const char* title="PND Task");
    PndMCTrackEnumAssociator();
    virtual ~PndMCTrackEnumAssociator();

    virtual InitStatus Init();              //
    virtual void Exec(Option_t* option);    //
    void Register();

    Int_t GetMvdHitPixels(Int_t index);     // from the MVD pixel index retrns the Pndrack index
    Int_t GetMvdHitStrips(Int_t index);     // from the MVD strip hit index retrns the Pndrack index
    Int_t GetSttHits(Int_t index);     // from the STT hit index retrns the Pndrack index
    Int_t GetGemHits(Int_t index);     // from the GEM hit index retrns the Pndrack index
    Int_t GetFtsHits(Int_t index);     // from the FTS hit index retrns the Pndrack index


    // Modifiers -----------------------
    void SetTrackInBranchName(const TString& name)   { fTrackInBranchName = name;  }
    void SetTrackOutBranchName(const TString& name)  { fTrackOutBranchName = name; }

    void SetOption(Option_t* option=" ") {fOption = option;  fOption.ToLower();}

    void SetVerbose(Bool_t verb)                     {  fVerbose       = verb ;};
    void SetPersistence(Bool_t pers)                 {  fPersistence   = pers ;};

  protected:

    TString fTrackInBranchName;      //! Name of the input TCA
    TString fTrackOutBranchName;     //! Name of the output TCA

    TClonesArray*  fTpcInput;             //! pointers to TPC TCA
    TClonesArray*  fSttHitInput;          //! pointers to STT Hit TCA
    TClonesArray*  fMvdMCArray;           //!
    TClonesArray*  fMvdStripHitArray;     //!
    TClonesArray*  fMvdPixelHitArray;     //!
    TClonesArray*  fMvdStripClusterArray; //!
    TClonesArray*  fMvdPixelClusterArray; //!
    TClonesArray*  fMvdStripDigiArray;    //!
    TClonesArray*  fMvdPixelDigiArray;    //!
    TClonesArray*  fGemMCArray;           //! pointers to GEMPoint TCA
    TClonesArray*  fGemInput;             //! pointers to GEMHit TCA
    TClonesArray*  fFtsMCArray;           //! pointers to FtsPoint TCA
    TClonesArray*  fFtsInput;             //! pointers to FtsHit TCA

    TClonesArray*  fTrackIDArray;         //! pointers to PndTrackID (output)
    TClonesArray*  fTrackArray;           //! pointers to PndTrack (input)

    Bool_t fVerbose;             // Switch ON/OFF debug messages        (defaulf OFF)
    Bool_t fPersistence;         // Persistence of LheHit/LheGeantTrack (default ON)

    ClassDef(PndMCTrackEnumAssociator,1)      // PndMCTrackEnumAssociator

};

#endif
