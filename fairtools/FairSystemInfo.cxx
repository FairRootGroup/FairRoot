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

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t FairSystemInfo::GetCurrentMemory( )
{
#if defined(__APPLE__) && defined(__MACH__)
    /* OSX ------------------------------------------------------ */
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if ( task_info( mach_task_self( ), MACH_TASK_BASIC_INFO,
        reinterpret_cast<task_info_t>(&info), &infoCount ) != KERN_SUCCESS )
//        (task_info_t)&info, &infoCount ) != KERN_SUCCESS )
        return static_cast<size_t>(0L);      /* Can't access? */
    return static_cast<size_t>(info.resident_size);

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    /* Linux ---------------------------------------------------- */
    long rss = 0L;
    FILE* fp = NULL;
    if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
        return (size_t)0L;      /* Can't open? */
    if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
    {
        fclose( fp );
        return (size_t)0L;      /* Can't read? */
    }
    fclose( fp );
    return (size_t)rss * (size_t)sysconf( _SC_PAGESIZE);

#else
    /* AIX, BSD, Solaris, and Unknown OS ------------------------ */
    return (size_t)0L;          /* Unsupported. */
#endif
}
