/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef S_EVHE
#define S_EVHE

#include "typedefs.h"

#if MBS_ENDIAN == 1

/*  ================= GSI VME General event header ===============  */
typedef struct
{
    INTS4 l_dlen; /*  Length of data in words */
    INTS2 i_subtype;
    INTS2 i_type;
} s_evhe;
/* ------------------------------------------------------------------ */

#else

typedef struct
{
    INTS4 l_dlen; /*  Length of data in words */
    INTS2 i_type;
    INTS2 i_subtype;
} s_evhe;

#endif

#endif
