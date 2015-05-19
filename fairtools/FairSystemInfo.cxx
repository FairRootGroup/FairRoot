/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairSystemInfo.cxx
 *
 *  Created on: Mar 18, 2015
 *      Author: f.uhlig
 */

#include "FairSystemInfo.h"

#include <unistd.h>
#include <sys/resource.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <stdio.h>

#else
#error "Unknown OS."
#endif


Float_t FairSystemInfo::GetMaxMemory()
{
  // Returns the maximal used memory in MB

  struct rusage rusage;
  getrusage( RUSAGE_SELF, &rusage );

#if defined(__APPLE__) && defined(__MACH__)
  return static_cast<Float_t>(rusage.ru_maxrss)/(1024*1024);
#else
  return static_cast<Float_t>(rusage.ru_maxrss)/1024;
#endif
  
}
