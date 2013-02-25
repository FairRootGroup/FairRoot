// $Id: s_stdint.h 595 2010-03-09 06:51:15Z adamczew $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef S_STDINT_H
#define S_STDINT_H

// this is minimum types set for fixed-size integers

#ifdef WIN32

#if _MSC_VER > 1000
#pragma once
#endif

#include <limits.h>
#include <wchar.h>

typedef __int8            int8_t;
typedef __int16           int16_t;
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

#endif

#ifdef Lynx

typedef char           int8_t;
typedef unsigned char  uint8_t;
typedef short          int16_t;
typedef unsigned short uint16_t;
typedef int            int32_t;
typedef unsigned int   uint32_t;
typedef long           int64_t;
typedef unsigned long  uint64_t;

#endif

#ifdef Linux
#include <stdint.h>
#endif

#ifdef Solaris
#include <stdint.h>
#endif

#ifdef Darwin
#include <stdint.h>
#endif


#endif
