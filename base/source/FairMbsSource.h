/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairMbsSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRMBSSOURCE_H
#define FAIRMBSSOURCE_H

#include "FairSource.h"
#include "TObjArray.h"

#include "FairUnpack.h"


class FairMbsSource : public FairSource
{
  public:
    FairMbsSource();
    FairMbsSource(const FairMbsSource& source);
    virtual ~FairMbsSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }
    inline const TObjArray* GetUnpackers() const { return fUnpackers; }

    virtual Bool_t Init();
    virtual Int_t ReadEvent() = 0;
    virtual void Close() = 0;

    void Reset();

  protected:
    Bool_t Unpack(Int_t* data, Int_t size,
                  Short_t type, Short_t subType,
                  Short_t procId, Short_t subCrate, Short_t control);

  private:
    TObjArray* fUnpackers;

  public:
    ClassDef(FairMbsSource, 0)
};


#endif
