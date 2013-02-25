// $Id: s_filter.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_FILTER
#define S_FILTER

#include "typedefs.h"
/* +++ s_filter.h +++
 * client structure for SBS monitor
 * (see also s_filter.h for GPS-Server on (Open)VMS / clients)
 * R.S. Mayer
 * 18-Feb-1994
*/
struct s_filter {
  INTU4          l_pattern;
  INTS4          l_offset;       /* offset >0: LW  <0: Words     */
  INTU4          l_opcode;
};

#endif
