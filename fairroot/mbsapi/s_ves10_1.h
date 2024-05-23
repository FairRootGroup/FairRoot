/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef S_VES10_1
#define S_VES10_1

#include "typedefs.h"
/*  ================= GSI VME Subevent header =======================  */

#if MBS_ENDIAN == 1

typedef struct
{
    INTS4 l_dlen; /*  Data length +2 in words */
    INTS2 i_subtype;
    INTS2 i_type;
    CHARS h_control;  /*  Processor type code */
    CHARS h_subcrate; /*  Subcrate number */
    INTS2 i_procid;   /*  Processor ID [as loaded from VAX] */
} s_ves10_1;
/* ------------------------------------------------------------------ */

#else

typedef struct
{
    INTS4 l_dlen; /*  Data length +2 in words */
    INTS2 i_type;
    INTS2 i_subtype;
    INTS2 i_procid;   /*  Processor ID [as loaded from VAX] */
    CHARS h_subcrate; /*  Subcrate number */
    CHARS h_control;  /*  Processor type code */
} s_ves10_1;

#endif

#endif
