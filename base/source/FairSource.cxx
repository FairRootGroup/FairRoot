// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#include <iostream>

#include "FairSource.h"


FairSource::FairSource()
  : TObject()
{
}


FairSource::FairSource(const FairSource& source)
  : TObject(source)
{
}


FairSource::~FairSource()
{
}

ClassImp(FairSource)
