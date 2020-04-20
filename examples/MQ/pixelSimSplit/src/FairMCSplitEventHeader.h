/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/** FairMCSplitEventHeader.h **/

#ifndef FAIRMCSPLITEVENTHEADER_H
#define FAIRMCSPLITEVENTHEADER_H 1

#include "FairMCEventHeader.h"

#include <Rtypes.h>

class FairMCSplitEventHeader : public FairMCEventHeader
{
  public:
    FairMCSplitEventHeader();
    FairMCSplitEventHeader(UInt_t runID, UInt_t eventID, UInt_t nofChunks, UInt_t chunkStart);

    virtual ~FairMCSplitEventHeader();

    void SetRECC(UInt_t i1, UInt_t i2, UInt_t i3, UInt_t i4)
    {
        SetRunID(i1);
        SetEventID(i2);
        SetNofChunks(i3);
        SetChunkStart(i4);
    }
    void SetNofChunks(UInt_t ti) { fNofChunks = ti; }
    void SetChunkStart(UInt_t ti) { fChunkStart = ti; }

    UInt_t GetNofChunks() { return fNofChunks; }
    UInt_t GetChunkStart() { return fChunkStart; }

    virtual void Register();

  protected:
    UInt_t fNofChunks;
    UInt_t fChunkStart;

    ClassDef(FairMCSplitEventHeader, 1);
};

#endif /* FAIRMCSPLITEVENTHEADER_H_ */
