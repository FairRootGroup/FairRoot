/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCList.cxx
 *
 *  Created on: Dec 3, 2009
 *      Author: stockman
 */

#include "FairMCList.h"

FairMCList::FairMCList()
    : TObject()
    , fList()
    , fEntry(-1)
    , fType(-1)
{}

FairMCList::~FairMCList() {}
