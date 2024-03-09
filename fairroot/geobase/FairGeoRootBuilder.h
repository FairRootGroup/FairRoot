/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOROOTBUILDER_H
#define FAIRGEOROOTBUILDER_H

#include "FairGeoBuilder.h"   // for FairGeoBuilder

#include <TGeoManager.h>

class FairGeoMedium;
class FairGeoNode;

/**
 * class to create geometry in ROOT
 * \ingroup geobase
 * @author M. Al-Turany
 */
class FairGeoRootBuilder : public FairGeoBuilder
{
  private:
    FairGeoRootBuilder(const FairGeoRootBuilder&);
    FairGeoRootBuilder& operator=(const FairGeoRootBuilder&);
    std::unique_ptr<TGeoManager> geoManager;   //!< ROOT geometry manager

  public:
    FairGeoRootBuilder();
    FairGeoRootBuilder(const char*, const char*);
    FairGeoRootBuilder(const char*, const char*, std::unique_ptr<TGeoManager>);
    ~FairGeoRootBuilder() override = default;
    [[deprecated]] void setGeoManager(TGeoManager* me) { geoManager.reset(me); }
    Bool_t createNode(FairGeoNode*, Int_t hadFormat = 0) override;
    Int_t createMedium(FairGeoMedium*) override;
    void finalize() override;
    void checkOverlaps(Double_t ovlp = 0.0001);
    ClassDefOverride(FairGeoRootBuilder, 0);   //
};

#endif /* !FAIRGEOROOTBUILDER_H */
