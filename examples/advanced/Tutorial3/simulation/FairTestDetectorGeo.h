/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORGEO_H_
#define FAIRTESTDETECTORGEO_H_

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for Int_t, etc

class FairTestDetectorGeo : public FairGeoSet
{
  public:
    FairTestDetectorGeo();
    ~FairTestDetectorGeo() override = default;
    ClassDefOverride(FairTestDetectorGeo, 1);
};

#endif /* FAIRTESTDETECTORGEO_H_ */
