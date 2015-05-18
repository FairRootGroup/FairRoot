/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * Fairmemeory.h
 *
 *  Created on: Mai 18, 2015
 *      Author: f.uhlig
 */

#ifndef BASE_FAIRMEMORY_H_
#define BASE_FAIRMEMORY_H_

#include "Rtypes.h"

class FairMemory
{
 public:

  Float_t GetMaxMemory();
  
  ClassDef(FairMemory, 1)
};

#endif  // BASE_FAIRMEMORY_H_
