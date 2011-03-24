// $Id: s_filhe.h 478 2009-10-29 12:26:09Z linev $
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

#ifndef S_FILHE
#define S_FILHE

#include "typedefs.h"

struct cv_string {
  INTS2 string_l;
  CHARS string[78];
} ;


#if MBS_ENDIAN == 1

typedef struct {
  INTS4 filhe_dlen;         /* length of data in words */
  INTS2 filhe_subtype;      /* = 1 */
  INTS2 filhe_type;         /* = 2000 */
  INTS2 filhe_frag;
  INTS2 filhe_used;
  INTS4  filhe_buf;
  INTS4  filhe_evt;
  INTS4  filhe_current_i;
  INTS4  filhe_stime[2];
  INTS4  filhe_free[4];   /* free[0] = 1 -> swap */
  INTS2 filhe_label_l;      /* length of tape label string */
  CHARS  filhe_label[30];       /* tape label */
  INTS2 filhe_file_l;         /* length of file name */
  CHARS  filhe_file[86];      /* file name */
  INTS2 filhe_user_l;         /* length of user name */
  CHARS  filhe_user[30];      /* user name */
  CHARS  filhe_time[24];      /* date and time string */
  INTS2 filhe_run_l;         /* length of run id */
  CHARS  filhe_run[66];      /* run id */
  INTS2 filhe_exp_l;         /* length of explanation */
  CHARS  filhe_exp[66];      /* explanation */
  INTS4  filhe_lines;         /* # of comment lines */
  struct cv_string s_strings[30];  /* max 30 comment lines */
} s_filhe;

#else

typedef struct {
  INTS4 filhe_dlen;         /* length of data in words */
  INTS2 filhe_type;         /* = 2000 */
  INTS2 filhe_subtype;      /* = 1 */
  INTS2 filhe_used;
  INTS2 filhe_frag;
  INTS4  filhe_buf;
  INTS4  filhe_evt;
  INTS4  filhe_current_i;
  INTS4  filhe_stime[2];
  INTS4  filhe_free[4];   /* free[0] = 1 -> swap */
  INTS2 filhe_label_l;      /* length of tape label string */
  CHARS  filhe_label[30];       /* tape label */
  INTS2 filhe_file_l;         /* length of file name */
  CHARS  filhe_file[86];      /* file name */
  INTS2 filhe_user_l;         /* length of user name */
  CHARS  filhe_user[30];      /* user name */
  CHARS  filhe_time[24];      /* date and time string */
  INTS2 filhe_run_l;         /* length of run id */
  CHARS  filhe_run[66];      /* run id */
  INTS2 filhe_exp_l;         /* length of explanation */
  CHARS  filhe_exp[66];      /* explanation */
  INTS4  filhe_lines;         /* # of comment lines */
  struct cv_string s_strings[30];  /* max 30 comment lines */
} s_filhe;

#endif

#endif
