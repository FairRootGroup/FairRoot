/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
typedef struct {
  CHARS c_name[32];
  CHARS c_desc[80];
  INTU4 lu_used;
  INTU4 lu_checked;
  INTS4 l_freezed;
  INTU4 lu_true;
  REAL4 r_xmin;
  REAL4 r_xmax;
  REAL4 r_ymin;
  REAL4 r_ymax;
} s_win;
