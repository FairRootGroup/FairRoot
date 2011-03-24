// $Id: s_pol_cond.h 478 2009-10-29 12:26:09Z linev $
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
  INTS4 l_points;
  REAL4 ra_x[32];
  REAL4 ra_y[32];
  REAL4 ra_x1[32];
  REAL4 ra_y1[32];
  REAL4 ra_x2[32];
  REAL4 ra_y2[32];
  REAL4 ra_f[32];
  REAL4 ra_o[32];
} s_pol;
