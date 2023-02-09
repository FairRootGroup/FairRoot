/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * MyRingSorter.cxx
 *
 *  Created on: Mar 7, 2012
 *      Author: uhlig
 */

#include "MyDataClass.h"

#include <MyRingSorter.h>

MyRingSorter::~MyRingSorter() {}

FairTimeStamp* MyRingSorter::CreateElement(FairTimeStamp* data)
{
    return new MyDataClass(*(MyDataClass*)data);
}
