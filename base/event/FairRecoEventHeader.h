/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----          FairRecoEventHeader header file                      -----
// -----          Created 20/09/13                 R.Karabowicz        -----
// -------------------------------------------------------------------------

#ifndef FAIRRECOEVENTHEADER_H
#define FAIRRECOEVENTHEADER_H

#include <TNamed.h>

/**
 *  Event Header Class
 **@author D.Bertini <d.bertini@gsi.de>
 **@author M.Al-Turany <m.al-turany@gsi.de>
 **@author R.Karabowicz <r.karabowicz@gsi.de>
 */
class FairRecoEventHeader : public TNamed
{
  public:
    /** Default constructor */
    FairRecoEventHeader();

    /** Get the run ID for this run*/
    UInt_t GetRunId() const { return fRunId; }

    /** Get the MC time for this event*/
    Double_t GetEventTime() const { return fEventTime; }

    /** Get the error of MC time for this event*/
    Double_t GetEventTimeError() const { return fEventTimeError; }

    /** Get identifier*/
    Int_t GetIdentifier() const { return fIdentifier; }

    /** Set the run ID for this run
     * @param runid : unique run id
     */
    void SetRunId(UInt_t runid) { fRunId = runid; }

    /** Set the MC time for this event
     * @param time : time in ns
     * @param terr : time error in ns
     */
    void SetEventTime(Double_t time, Double_t terr)
    {
        fEventTime = time;
        fEventTimeError = terr;
    }

    /** Set the run ID for this run
     * @param ident : identifier
     */
    void SetIdentifier(Int_t ident) { fIdentifier = ident; }

    virtual bool operator<(const FairRecoEventHeader& tempObj) const
    {
        if (fEventTime < tempObj.GetEventTime()) {
            return true;
        } else if (fEventTime > tempObj.GetEventTime()) {
            return false;
        }
        return false;
    }

    virtual bool operator>(const FairRecoEventHeader& tempObj) const
    {
        if (fEventTime > tempObj.GetEventTime()) {
            return true;
        } else if (fEventTime < tempObj.GetEventTime()) {
            return false;
        }
        return false;
    }

    virtual bool operator==(const FairRecoEventHeader& tempObj) const { return fEventTime == tempObj.GetEventTime(); }

    /**
     * Destructor
     */
    virtual ~FairRecoEventHeader();

  protected:
    /** Run Id */
    UInt_t fRunId;
    /** Identifier */
    Int_t fIdentifier;
    /** Event Time **/
    Double_t fEventTime;
    /** Event Time Error **/
    Double_t fEventTimeError;

    ClassDef(FairRecoEventHeader, 1);
};

#endif
