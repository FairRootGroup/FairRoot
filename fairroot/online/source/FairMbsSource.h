/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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

#include "FairOnlineSource.h"

#include <Rtypes.h>

class FairMbsSource : public FairOnlineSource
{
  public:
    FairMbsSource() = default;
    FairMbsSource(const FairMbsSource& source) = default;
    ~FairMbsSource() override = default;

    Bool_t Init() override = 0;
    Int_t ReadEvent(UInt_t = 0) override = 0;
    void Close() override = 0;

  protected:
    Bool_t Unpack(Int_t* data,
                  Int_t size,
                  Short_t type,
                  Short_t subType,
                  Short_t procId,
                  Short_t subCrate,
                  Short_t control);

    ClassDefOverride(FairMbsSource, 0);
};

#endif
