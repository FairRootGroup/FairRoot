/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "typedefs.h"
#define COMPR__PATTERN 0x0f0f0f0f
typedef struct {
  INTU4 l_endian;     /* set to 1 by creator */
  INTU4 l_length;     /* total size [bytes] of compressed buffer */
  INTU4 l_masks;      /* number of masks following this header */
  INTU4 l_full_bytes; /* number of bytes needed for uncompressed buffer */
  INTU4 l_comp_bytes; /* number of non zero bytes */
  INTU4 l_pattern;    /* COMPR__PATTERN */
} s_compress;
INTS4 f_ut_compr_size(INTU1*, INTS4);
INTS4 f_ut_compr_zeros(INTU1*, INTS4);
INTS4 f_ut_compr_pack(INTU1*, INTS4, INTU1*, INTS4);
INTS4 f_ut_compr_unpack(INTU1*, INTU1*, INTS4);
