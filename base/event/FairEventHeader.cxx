/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                         FairEventHeader source file           -----
// -----            Created 08/09/04                 D. Bertini        -----
// -------------------------------------------------------------------------

#include "FairEventHeader.h"

#include "FairRootManager.h"

void FairEventHeader::Register(Bool_t Persistence)
{
    FairRootManager::Instance()->Register("EventHeader.", "EvtHeader", this, Persistence);
}

ClassImp(FairEventHeader);
