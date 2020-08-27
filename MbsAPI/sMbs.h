/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MbsStruct
#define MbsStruct

#define LMD__TYPE_FILE_HEADER_101_1 0x00010065
#define LMD__TYPE_EVENT_HEADER_10_1 0x0001000a
#define LMD__TYPE_FILE_INDEX_101_2 0x00020065
#define LMD__TYPE_BUFFER_HEADER_10_1 0x0001000a
#define LMD__TYPE_BUFFER_HEADER_100_1 0x00010064
#define LMD__TYPE_TIME_STAMP_11_1 0x0001000b
#define LMD__GET_EVENTS NULL
#define LMD__STANDARD_HEADER NULL
#define LMD__INTERNAL_HEADER NULL
#define LMD__INDEX 1
#define LMD__OVERWRITE 1
#define LMD__LARGE_FILE 1
#define LMD__MIN_BUFFER 0
#define LMD__BUFFER 1
#define LMD__VERBOSE 1
#define LMD__NO_VERBOSE 0
#define LMD__NO_BUFFER 0
#define LMD__NO_INDEX 0
#define LMD__NO_OVERWRITE 0
#define LMD__NO_LARGE_FILE 0
#define LMD__NO_VERBOSE 0
#define LMD__VERBOSE 1
#define LMD__ENDIAN_LITTLE 1
#define LMD__ENDIAN_BIG 2
#define LMD__ENDIAN_UNKNOWN 0

#include "s_stdint.h"

typedef uint64_t lmdoff_t;

// must #include <stdint.h>
// on Lynx, define int32_t, uint32_t, int16_t
// structure used to talk between client and server
// Client connects to server (MBS) and reads this structure first

//--------------------------------------------------
// Structure maps the MBS transport info buffer
typedef struct
{
    uint32_t iEndian;     // byte order. Set to 1 by sender
    uint32_t iMaxBytes;   // maximum buffer size
    uint32_t iBuffers;    // buffers per stream
    uint32_t iStreams;    // number of streams
} sMbsTransportInfo;

//--------------------------------------------------
// Buffer header, maps s_bufhe, some fields used in different way
typedef struct
{
    uint32_t iMaxWords;          // compatible with s_bufhe (total buffer size - header)
    uint32_t iType;              // compatible with s_bufhe, low=type (=100), high=subtype
    uint32_t iUsed;              // not used for iMaxWords>MAX__DLEN (16360), low 16bits only
    uint32_t iBuffer;            // compatible with s_bufhe
    uint32_t iElements;          // compatible with s_bufhe
    uint32_t iTemp;              // Used volatile
    uint32_t iTimeSpecSec;       // compatible with s_bufhe (2*32bit)
    uint32_t iTimeSpecNanoSec;   // compatible with s_bufhe (2*32bit)
    //  struct timespec TimeSpec;
    uint32_t iEndian;          // compatible with s_bufhe free[0]
    uint32_t iWrittenEndian;   // one of LMD__ENDIAN_x
    uint32_t iUsedWords;       // total words without header to read for type=100, free[2]
    uint32_t iFree3;           // free[3]
} sMbsBufferHeader;

//--------------------------------------------------
// Buffer header, maps s_bufhe
typedef struct
{
    uint32_t iMaxWords;          // compatible with s_bufhe (total buffer size - header)
    uint32_t iType;              // compatible with s_bufhe, low=type (=100), high=subtype
    lmdoff_t iTableOffset;       // optional offset to element offset table in file
    uint32_t iElements;          // compatible with s_bufhe
    uint32_t iOffsetSize;        // Offset size, 4 or 8 [bytes]
    uint32_t iTimeSpecSec;       // compatible with s_bufhe (2*32bit)
    uint32_t iTimeSpecNanoSec;   // compatible with s_bufhe (2*32bit)
    //  struct timespec TimeSpec;
    uint32_t iEndian;          // compatible with s_bufhe free[0]
    uint32_t iWrittenEndian;   // one of LMD__ENDIAN_x
    uint32_t iUsedWords;       // total words without header to read for type=100, free[2]
    uint32_t iFree3;           // free[3]
} sMbsFileHeader;

//--------------------------------------------------
typedef struct
{
    uint32_t iMaxWords;
    uint32_t iType;
    uint32_t iTimeSpecSec;
    uint32_t iTimeSpecNanoSec;
} sMbsTimeStamp;

//--------------------------------------------------
// maps s_evhe
typedef struct
{
    uint32_t iWords;   // following data words
    uint32_t iType;    // compatible with s_ve10_1, low=type (=10), high=subtype
} sMbsHeader;

//--------------------------------------------------
// maps s_ve10_1
typedef struct
{
    uint32_t iWords;   // data words + 4
    uint32_t iType;    // compatible with s_ve10_1, low=type (=10), high=subtype
    uint32_t iTrigger;
    uint32_t iEventNumber;
} sMbsEventHeader;

//--------------------------------------------------
// maps s_ves10_1
typedef struct
{
    uint32_t iWords;        // data words + 2
    uint32_t iType;         // compatible with s_ves10_1, low=type (=10), high=subtype
    uint32_t iSubeventID;   // 2 low bytes=procid, next byte=subcrate, high byte control
} sMbsSubeventHeader;
#endif
