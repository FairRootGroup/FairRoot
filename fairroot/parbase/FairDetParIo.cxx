/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 20/10/2004
#include "FairDetParIo.h"
/////////////////////////////////////////////////////////////
//  FairDetParIo
//
//  Abstract class for parameter input/output needed by a
//  detector
/////////////////////////////////////////////////////////////
FairDetParIo::FairDetParIo()
    : TNamed()
    , inputNumber(0)
{}
