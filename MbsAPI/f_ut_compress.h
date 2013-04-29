// $Id: f_ut_compress.h 478 2009-10-29 12:26:09Z linev $
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
