/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

 #include "FairPropagator.h"
 #include <TGenericClassInfo.h>  // for TGenericClassInfo


FairPropagator::FairPropagator()
    : TNamed("FairPropagator", "Base class for propagators")
{}

FairPropagator::FairPropagator(const TString& name, const TString& title)
    : TNamed(name, title)
{}

FairPropagator::~FairPropagator() {}

ClassImp(FairPropagator);
