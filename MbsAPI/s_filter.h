/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
