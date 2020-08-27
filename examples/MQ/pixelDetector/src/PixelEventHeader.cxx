/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelEventHeader.h
 *
 *  Created on: 18.03.2016
 *      Author: R. Karabowicz
 */

#include "PixelEventHeader.h"

PixelEventHeader::PixelEventHeader()
    : FairEventHeader()
    , fPartNo(0)
{}

PixelEventHeader::~PixelEventHeader() {}

ClassImp(PixelEventHeader);
