/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----            FairRecoEventHeader source file                    -----
// -----            Created 20/09/13                 R.Karabowicz      -----
// -------------------------------------------------------------------------

#include "FairRecoEventHeader.h"

FairRecoEventHeader::FairRecoEventHeader()
    : fRunId(0)
    , fIdentifier(0)
    , fEventTime(-1.)
    , fEventTimeError(-1.)
{}

FairRecoEventHeader::~FairRecoEventHeader() {}
