/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairEventHeader header file                      -----
// -----          Created 08/09/04                 D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef FAIREVENTHEADER_H
#define FAIREVENTHEADER_H

#include <Rtypes.h>   // for Int_t, Double_t, UInt_t, ClassDef, etc
#include <TNamed.h>   // for TNamed

/**
 *  Event Header Class
 **@author D.Bertini <d.bertini@gsi.de>
 **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairEventHeader : public TNamed
{
  public:
    /** Default constructor */
    FairEventHeader() = default;

    /**
     * Destructor
     */
    ~FairEventHeader() override = default;

    /** Get the run ID for this run*/
    UInt_t GetRunId() const { return fRunId; }

    /** Get the MC time for this event*/
    Double_t GetEventTime() const { return fEventTime; }

    /** Get the MC input file Id for this event*/
    Int_t GetInputFileId() const { return fInputFileId; }

    /**The entry number in the original MC chain */
    Int_t GetMCEntryNumber() const { return fMCEntryNo; }

    /** Set the run ID for this run
     * @param runid : unique run id
     */
    void SetRunId(UInt_t runid) { fRunId = runid; }

    /** Set the MC time for this event
     * @param time : time in ns
     */
    void SetEventTime(Double_t time) { fEventTime = time; }

    /** Set the Signal file Id for this event*/
    void SetInputFileId(Int_t id) { fInputFileId = id; }

    /**The entry number in the original MC chain */
    void SetMCEntryNumber(Int_t id) { fMCEntryNo = id; }

    virtual void Register(Bool_t Persistance = kTRUE);

  protected:
    /** Run Id */
    UInt_t fRunId{0};
    /** Event Time **/
    Double_t fEventTime{-1.};
    /** Input file identifier, the file description is in the File header*/
    Int_t fInputFileId{0};
    /**MC entry number from input chain*/
    Int_t fMCEntryNo{0};

    ClassDefOverride(FairEventHeader, 3);
};

#endif
