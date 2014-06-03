/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef S_PAT
#define S_PAT

#include "typedefs.h"

#if MBS_ENDIAN == 1

/* identities for filter patterns                */
struct s_pat1 {
  short         i_dummy;
  short         i_trigger;
};

struct s_pat2 {
  char          h_control;
  char          h_subcrate;
  short         i_procid;
};

struct s_pat3 {
  short         i_subtype;
  short         i_type;
};

#else

/* identities for filter patterns                */
struct s_pat1 {
  short         i_trigger;
  short         i_dummy;
};

struct s_pat2 {
  short         i_procid;
  char          h_subcrate;
  char          h_control;
};

struct s_pat3 {
  short         i_type;
  short         i_subtype;
};

#endif

#endif
