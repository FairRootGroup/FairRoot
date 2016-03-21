/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTUT8UNPACK_H
#define FAIRTUT8UNPACK_H

#include "FairUnpack.h"

class TClonesArray;

/**
 * An example unpacker of MBS data.
 */
class FairTut8Unpack : public FairUnpack
{
  public:
    /** Standard Constructor. Input - MBS parameters of the detector. */
    FairTut8Unpack(Short_t type = 94,
                   Short_t subType = 9400,
                   Short_t procId = 10,
                   Short_t subCrate = 1,
                   Short_t control = 3);

    /** Destructor. */
    virtual ~FairTut8Unpack();

    /** Initialization. Called once, before the event loop. */
    virtual Bool_t Init();
    
    /** Process an MBS sub-event. */
    virtual Bool_t DoUnpack(Int_t* data, Int_t size);
    
    /** Clear the output structures. */
    virtual void Reset();

    /** Method for controling the functionality. */
    inline Int_t GetNHitsTotal()
    {
        return fNHitsTotal;
    }

  protected:
    /** Register the output structures. */
    virtual void Register();

  private:
    TClonesArray* fRawData; /**< Array of output raw items. */
    Int_t fNHits;           /**< Number of raw items in current event. */
    Int_t fNHitsTotal;      /**< Total number of raw items. */

    FairTut8Unpack(const FairTut8Unpack&);
    FairTut8Unpack& operator=(const FairTut8Unpack&);
  public:
    // Class definition
    ClassDef(FairTut8Unpack, 1)
};

#endif
