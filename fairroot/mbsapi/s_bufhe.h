/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef S_BUFHE
#define S_BUFHE

#include "typedefs.h"
/* Generated from SA$BUFHE.TXT  */
/* Swapping enabled           */
/*  ================= GSI Buffer header =======================  */
#define MAX__DLEN 16360

#if MBS_ENDIAN == 1

typedef struct
{
    INTS4 l_dlen; /*  Length of data field in words */
    INTS2 i_subtype;
    INTS2 i_type;
    CHARS h_begin;     /*  Fragment at end of buffer */
    CHARS h_end;       /*  Fragment at begin of buffer */
    INTS2 i_used;      /*  Used length of data field in words */
    INTS4 l_buf;       /*  Current buffer number */
    INTS4 l_evt;       /*  Number of fragments */
    INTS4 l_current_i; /*  Index, temporarily used */
    INTS4 l_time[2];
    INTS4 l_free[4];
} s_bufhe;

#else

typedef struct
{
    INTS4 l_dlen; /*  Length of data field in words */
    INTS2 i_type;
    INTS2 i_subtype;
    INTS2 i_used;      /*  Used length of data field in words */
    CHARS h_end;       /*  Fragment at begin of buffer */
    CHARS h_begin;     /*  Fragment at end of buffer */
    INTS4 l_buf;       /*  Current buffer number */
    INTS4 l_evt;       /*  Number of fragments */
    INTS4 l_current_i; /*  Index, temporarily used */
    INTS4 l_time[2];
    INTS4 l_free[4];
} s_bufhe;

#endif

#endif
