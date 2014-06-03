/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*************************************************************************/
/* +++ GSI Darmstadt                                                 +++ */
/* +++                                                               +++ */
/*************************************************************************/
/*+File name        S_CLNTBUF.H                                          */
/*                                                                       */
/*************************************************************************/
/*+    Update       Date          Purpose                                */
/*-                 10-Dec-1993 : Define testbit and low or high endian  */
/*                                and some types changed and 2LW added   */
/*-                 27-Jan-1994 : CLNT_BUFH_LW changed to  11  (RSM)     */
/*-                 02-Feb-1994 : definitions in CLNT_BUF_DEF.H ,        */
/*                                def. names changed. (RSM)              */
/*************************************************************************/

/* RSM 19-MAR-1993      */
/* is a part of s_clntoutbuf */

struct s_clntbuf {
  /* ------ first part of s_clntoutbuf omitted ----------- */
  /* --- control byte ordering and machine type (2LW) ---- */
  unsigned int   l_testbit;              /* bit pattern                */
  unsigned int   l_endian;               /* endian of sender           */
  /* ----------------------------------------------------- */
  /* ----- length is CLNT__BUFHEAD ----------------------- */
  int            l_dlen;                 /* data length [bytes]        */
  int            l_free;                 /* free  length [bytes]       */
  int            l_events;               /* events in buffer           */
  int            l_maxbufsiz;            /* maximum buffer size        */
  int            l_bytestosnd;           /* sent bytes                 */
  int            l_numbuftosnd;          /* number of buffers to send  */
  int            l_client_con;           /* currently connect clients  */
  int  unsigned  l_buffertype;           /* type: data:1 msg:2 flush:4 */
  /*       last:8 1stBUF:16     */
  /* (inclusive) (mask)         */
  int  unsigned  l_msgtyp;               /* I:1 W:2 E:4 F:8 (exclusive)*/
  char            c_message[CLNT__MSGLEN]; /* error msg and other        */
  /* ----- part of s_control structure ------------------- */
  /* ----- length is CLNT__INFO_CONTROL ------------------ */
  int unsigned  l_inbuf_read_cnt; /* count read buffer              */
  int unsigned  l_inbuf_rdok_cnt; /* count read buffer that are o.k */
  int unsigned  l_inbuf_skip_cnt; /* count skipped buffer           */
  int unsigned  l_inbuf_byrd_cnt; /* count read bytes               */
  int unsigned  l_inbuf_proc_cnt; /* count processed buffer         */
  int unsigned  l_inbuf_prev_cnt; /* count processed events         */
  /* ----- part of s_client structure -------------------- */
  /* ----- length is CLNT__INFO_CLIENT ------------------- */
  int unsigned          l_clntoutbuf_sdev; /* sent events             */
  int unsigned          l_clntoutbuf_sdby; /* sent bytes              */
  int unsigned          l_clntoutbuf_sdbf; /* sent buffer             */
  int unsigned          l_clntoutbuf_prev; /* processed evt since con */
  int unsigned          l_clntoutbuf_fltm; /* filter matched on evt   */
  /* ----------------------------------------------------------------- */
  char            c_buffer[GPS__OUTBUFSIZ];
};
