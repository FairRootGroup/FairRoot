/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSink                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#include <iostream>

#include "FairSink.h"
#include "FairEventHeader.h"


FairSink::FairSink()
  : TObject()
  , fRunId(0)
  , fOutFolder(0)
{
}


FairSink::FairSink(const FairSink& sink)
  : TObject(sink)
  , fRunId(sink.fRunId)
  , fOutFolder(0)
{
}


FairSink::~FairSink()
{
}

ClassImp(FairSink)
