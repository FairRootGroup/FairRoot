/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/*
 * N. Kurz 10-Jan-1996
 *
 * within this structure the setup information for one host in the multi-branch
 * multi-layer daq system is specified.
 * for each host in the system which resides in the hierarchy above a
 * branch master (meb) such a set of data must be provided through a
 * parsed user input file.
 */

/* after allocating s_set_ml set in f_ut_set_ml_ini */
/* ps_set_ml->l_endian = 1;        */
/* ps_set_ml->l_version = n;        */
/* ps_set_ml->l_set_ml_lw = sizeof(s_set_ml)/4;  */
/* ps_set_ml->l_fix_lw = ((int)&c_rd_hostname[0][0]-(int)ps_set_ml)/4;  */
/* ps_set_ml->l_ml__n_rd_pipe = ML__N_RD_PIPE;  */
/* ps_set_ml->l_short_len = 16;  */
/* ps_set_ml->l_long_len = 128;  */
typedef struct {
  INTU4 l_endian;        /* set to 1 */
  INTU4 l_version;       /* increment in f_ut_status_ini after changes */
  INTU4 l_set_ml_lw;     /* sizeof(s_set_ml)/4 : total number of lw */
  INTU4 l_fix_lw;       /* (&c_rd_hostname-ps_set_ml)/4 : fixed number of longwords to read */
  INTU4 l_ml__n_rd_pipe; /* set to ML__N_RD_PIPE */
  INTU4 l_short_len;     /* set to length of short strings (16) */
  INTU4 l_long_len;      /* set to length of long strings (128) */

  INTS4 l_n_rd_pipe;
  /* number of pipes to read. this variable must not be specified,    */
  /* instead it will be filled during loading the multi-layer setup   */
  /* for this host                                                    */

  INTS4 l_out_mode;
  /* 1: write data from all read pipes into next layer pipe           */
  /* 2: format events into event buffer streams                       */
  /* 3: 1 + 2                                                         */

  INTS4 l_ev_buf_len;
  /* length of single event buffer. only needed if l_out_mode = 2,3   */

  INTS4 l_n_ev_buf;
  /* number of event buffers in a stream. only if l_out_mode = 2,3    */

  INTS4 l_n_stream;
  /* number of streams. only needed if l_out_mode = 2,3               */

  INTS4 l_wr_pipe_base_addr;
  /* base address of write pipe. only needed if l_out_mode = 1,3      */

  INTS4 l_wr_pipe_len;
  /* size of write pipe (in bytes). only needed if l_out_mode = 1,3   */

  INTS4 l_wr_pipe_n_frag;
  /* number of fragments to reserve in the write pipe. only needed if */
  /* l_out_mode = 1,3                                                 */

  INTS4 l_rd_host_flg[ML__N_RD_PIPE];
  /* 0: not to read from this host                                    */
  /* 1: pipe must be read from this node, node is branchmaster        */
  /* 2: pipe must be read from this node, node is NOT a branchmaster  */

  INTS4 l_rd_pipe_base_addr[ML__N_RD_PIPE];
  /* base address of the pipes to read, seen from this host           */

  INTS4 l_rd_pipe_len[ML__N_RD_PIPE];
  /* size of the pipes to read. this variable must not be specified,  */
  /* instead it will be filled from either a SBS setup file or from   */
  /* the write pipe specification (see below)  of the coresponding    */
  /* host lying below the hierarchy of this host          (in bytes)  */

  INTS4 l_rd_pipe_n_frag[ML__N_RD_PIPE];
  /* number of fragments to reserve in the read pipes. must also not  */
  /* be specified. see comment above for l_rd_pipe_len[]              */
  CHARS c_hostname[16];
  /* net name of this host                                            */

  /* ------------------ end of fixed block --------------------------*/
  CHARS c_rd_hostname [ML__N_RD_PIPE][16];
  /* netname of all hosts where this host have to read pipes          */

  CHARS c_sbs_setup_path [ML__N_RD_PIPE][128];
  /* paths/filenames of the SBS setup file of the hosts to read from. */
  /* only needed if these hosts are SBS branch masters. in this case  */
  /* the read pipes are specified in the SBS setup file. the base     */
  /* address of the read pipes must always be specified nevertheless  */


} s_set_ml;
