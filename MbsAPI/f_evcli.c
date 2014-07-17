/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_evcli                                           */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evcli_xxx()                                */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     :  API for GOOSY - Event - Server or    */
/*                 SBS - Event - Server .     */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*2+Description***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Client for test purpose GOOSY - PAW - Server and    */
/*                SBS - Event - Server.                               */
/*                (for detailed information see PC_CLIPAW)            */
/*                                                                    */
/*2+Implementation**********+******************************************/
/*                                                                    */
/*+ PROCEDURES  : see f_evcli_proc                                         */
/*                                                                    */
/*+ File name   : f_evcli.c                                         */
/*                                                                    */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer, H.Essel                                          */
/*+ Last Update : 28-feb-2000                                         */
/*                                                                    */
/*2+Internals***************+******************************************/
/*                                                                    */
/*+ Utility     :                                                     */
/*+ File name   : m_evcli.c                                         */
/*+ Home direct.: LEA$SRC                                         */
/*+ Created     : 28-feb-2000                                         */
/*                                                                    */
/*2+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*1- C Procedure *************+*********************************************/

/* ++++++++++++++ !!!! IMPLEMENTATION !!!! +++++++++++++++++++++++++++++++ */
#include "typedefs.h"

#include <ctype.h>


#define F__SWAP(ps,l,pd) f_swaplw((int *)ps,(int)l,(int *)pd)
#ifdef VMS        /* ++++++++++++++ VMS ++++++++++++++++++++++++++++ */
#define UNIXENV 0                           /* switch UNIX or VMS          */

/* standard headers ----- */
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <types.h>
#include <string.h>
#include <stdlib.h>
#endif /* VMS */

#ifdef Lynx      /* ++++++++++++++++ Lynx +++++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#endif /* Lynx */

#ifdef HPUX      /* +++++++++++++++++ HPUX ++++++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#define _HPUX_SOURCE                    /* this stuff is needed before    */
#define _POSIX_SOURCE                   /*   any include is done          */
#endif /* HPUX */

#ifdef Linux     /* +++++++++++++++++ Linux ++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#endif

#ifdef Solaris    /* +++++++++++++++++ Solaris ++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#endif

#ifdef Darwin     /* +++++++++++++++++ Max OS X ++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#endif


#ifdef GSI__WINNT  /* +++++++++++++++++ Windows NT ++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#define _ALL_SOURCE                     /* for types.h typedef u_char...  */
#define _POSIX_SOURCE                   /*   any include is done          */
#endif


#ifdef _AIX      /* +++++++++++++++++ AIX ++++++++++++++++++++++++++ */
#define UNIXENV 1                           /* switch UNIX or VMS          */
#define _ALL_SOURCE                     /* for types.h typedef u_char...  */
#define _POSIX_SOURCE                   /*   any include is done          */
#define IN_AIX 1
#else
#define IN_AIX 0
#endif /* !_AIX */

/* ++++++++++++++++ include UNIX standard headers +++++++++++++++++++++++++ */
#if UNIXENV == 1
#include <sys/types.h>
#ifdef GSI__WINNT
#include <sys/timeb.h>
#else
#include <sys/time.h>                   /* ?  <time.h> */
#include <netdb.h>
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif                                  /* UNIXENV */

/* ++++++++++++++++++++++ goopaw include files ++++++++++++++++++++++++++ */
#include "gps_sc_def.h"                 /* must be first */
#include "s_filter.h"
#include "clnt_buf_def.h"
#include "s_clntbuf.h"

// DABC
#include "fLmd.h"
// --DABC

#include "f_evcli.h"
#include "f_swaplw.h"

#include "s_filter.h"

#if MBS_ENDIAN == 1
#include "s_flt_descr_swap.h"
#include "s_clnt_filter_swap.h"
#else
#include "s_flt_descr.h"
#include "s_clnt_filter.h"
#endif

#include "s_opc1.h"
#include "s_pat.h"

#include "gps_sc_def.h"

void f_clnup(long [], int*);
void f_clnup_save(long [], int*);
int f_fltdscr(struct s_clnt_filter*);
int f_read_server(s_evt_channel*, int*, int, int);
int f_send_ackn(int, int);

unsigned short* pi_inbuf;
unsigned int* pl_inbuf;
unsigned int l_len_w;
int swapw(unsigned short*, unsigned short*, unsigned int);
int swapl(unsigned int*, unsigned int*, unsigned int);
static int i_debug = 0;                  /* message level (0-3) */

#define EVT_MAX 1000
#define TCP__TIMEOUT 3000                /* TCP timeout reading buffer   */
#define FLUSH__TIME 3                    /* flush time interval for MBS event server */
#define STDOUT_BUFIO_ 1

struct s_clnt_filter*  p_clnt_filter;
struct s_clntbuf*      p_clntbuf;
struct s_opc1*         p_opc1;

static int unsigned  lf_swap = 0;                  /* save swap on RX     */
static int unsigned  l_endian_serv;                /* save endian server  */
//static int           l_len_lw1 = CLNT__BUFH_LW;    /* len for first swap  */
int                  l_len_lw2;                    /* len for 2nd   swap  */
int                   i_channel;                    /* TCP/IP channel      */
int unsigned         l_clnt_sts;                   /* status for ackn.    */
int         l_status, l_sts;
static char           c_modnam[] = "f_evcli";
short         if_typevt, i_sign = 1, i_len;
int                  l_timeout;
int         l_retval;
static struct s_tcpcomm s_tcpcomm_ec = {0,0,0};
static struct {
  int                l_ack_buf;          /* read client buff received  */
  int                l_ack_bytes;        /* read client bytes received */
  int unsigned       l_clnt_sts;         /* client sts 1:o.k. 8:lst buf*/
}  s_ackn;

/* ++ vectors of pointer and devices for cleanup */
long          v_mem_clnup[8];
/***************************************************************************/
int f_evcli_con(s_evt_channel* ps_chan, char* pc_node, int l_aport, int l_aevents, int l_asample)
/***************************************************************************/
{
  short                 /*i,*/ i_h, i_m, i_s;
//  char                  arg[80], c_hms[16], c_help[4];
//  int                  l_evtecho,*pl;
  char                  c_node[32]/*, c_name[32]*/, c_retmsg[256];
  int                  l_port;

  v_mem_clnup[0] = 0;

  /* +++ allocate filter structure +++ */
  p_clnt_filter = (struct s_clnt_filter*) malloc( sizeof(struct s_clnt_filter) );
  if (p_clnt_filter == NULL) {
    printf("E-%s: calloc(,...s_clnt_filter) failed!\n", c_modnam);
    printf("F-%s: aborting program execution!\n",c_modnam);
    f_clnup(v_mem_clnup, NULL);
    return(-1);
  }
  ps_chan->pc_evt_buf=(char*) p_clnt_filter;
  /* save value for clnup */
  f_clnup_save(v_mem_clnup, (int*) p_clnt_filter);
  memset( (void*) p_clnt_filter, 0, sizeof(struct s_clnt_filter) );

  p_clnt_filter->l_testbit = GPS__ENV_TESTBIT;   /* set testbit              */
  p_clnt_filter->l_endian  = GPS__ENV_ENDIAN;    /* set endian               */
  p_clnt_filter->l_numb_of_evt = l_aevents;
  p_opc1 = (struct s_opc1*) &p_clnt_filter->filter[0].l_opcode;
  p_opc1->b1_evtsev = 1;
  p_opc1->b1_selflt = 1;
  p_opc1->b1_selwrt = 1;
  p_opc1->b3_opc    = 0;
  p_opc1->b1_lnkf1  = 0;
  p_opc1->b1_lnkf2  = 0;
  p_opc1->h_fltspec = 0;
  p_opc1->h_next_fltblk = 1;
  p_opc1->h_flt_len     = 1;

  l_status = f_fltdscr(p_clnt_filter);
  /*
  printf("evtsev: %d selflt: %d selwrt: %d opc: %d lnk1: %d lnk2: %d fltspec: %d next: %d len: %d\n"
  ,p_opc1->b1_evtsev
  ,p_opc1->b1_selflt
  ,p_opc1->b1_selwrt
  ,p_opc1->b3_opc
  ,p_opc1->b1_lnkf1
  ,p_opc1->b1_lnkf2
  ,p_opc1->h_fltspec
  ,p_opc1->h_next_fltblk
  ,p_opc1->h_flt_len);
  */
  if ((l_status & 1) == 0) {
    printf("E-%s: Severe Error in f_fltdscr! Status:%d\n",
           c_modnam,
           l_status);
    f_clnup(v_mem_clnup, NULL);
    return(-1);
  }
  p_clnt_filter->l_sample_rate = l_asample;
  p_clnt_filter->l_flush_rate = FLUSH__TIME;

  l_timeout = TCP__TIMEOUT ;
  strcpy(c_node,pc_node);
  l_port = l_aport;

  l_status = (int) f_stc_connectserver(c_node,
                                       l_port,
                                       &i_channel,
                                       &s_tcpcomm_ec);
  if ((l_status & 1) != STC__SUCCESS) {
    printf("E-%s: Error connecting node:%s, port:%d. Msg:\n",
           c_modnam,
           c_node,
           l_port);
    f_stc_disperror((int) l_status,c_retmsg, 0);
    f_stc_close(&s_tcpcomm_ec);
    return(l_status);
  }
  ps_chan->l_channel_no=i_channel;
  /* + buffer flushing time + */
  i_h = p_clnt_filter->l_flush_rate / 3600;      /* hours                 */
  i_s = p_clnt_filter->l_flush_rate - i_h * 3600;
  i_m = i_s / 60;                     /* minutes               */
  i_s = i_s - i_m * 60;             /* seconds               */

  /* +++++++++++++++++++++++++++++++++ */
  /* +++ send these data to server +++ */
  /* +++++++++++++++++++++++++++++++++ */
  /* len to transm [bytes] = 3 LW + filter + 1LW  */
  l_status = (int) f_stc_write( (char*) p_clnt_filter,
                                GPS__CLNT_SNDFLT,
                                i_channel);
  if (l_status != STC__SUCCESS) {
    printf("E-%s: Error in f_write_tcp(p_flt,...)! Status:%d. Msg:\n",
           c_modnam,
           l_status);
    f_stc_disperror((int) l_status,c_retmsg, 0);
    f_stc_close(&s_tcpcomm_ec);
    return(l_status);
  }
  /* + + + + + + + + + + + + + + */
  /* +++ alloc input buffer  +++ */
  /* + + + + + + + + + + + + + + */
  p_clntbuf = (struct s_clntbuf*) malloc(sizeof(struct s_clntbuf));
  if (p_clntbuf == NULL) {
    printf("E-%s: malloc(p_clntbuf) failed!\n", c_modnam);
    printf("F-%s: aborting program execution!\n",c_modnam);
    f_stc_close(&s_tcpcomm_ec);
    return(-1);
  }
  /* save value for clnup */
  f_clnup_save(v_mem_clnup, (int*) p_clntbuf);

  ps_chan->pc_io_buf = (char*) p_clntbuf;
  ps_chan->l_io_buf_size = GPS__OUTBUFSIZ + CLNT__OUTBUFHEAD;
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  /* ++++ first read on server, get machine type & swap  ++++ */
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  memset(p_clntbuf,0, sizeof(struct s_clntbuf));      /* clear memory  */
  l_status = f_read_server(ps_chan,
                           &l_retval,
                           l_timeout,
                           i_channel);
  if (l_status != TRUE) {
    printf("E-%s: Error reading 1st buffer: f_read_server()!\n", c_modnam);
    f_stc_close(&s_tcpcomm_ec);
    return(l_status);
  }

  /* ++++++++++++++++++++++++++++++++++++ */
  /* +++ check if a LW swap is needed +++ */
  /* ++++++++++++++++++++++++++++++++++++ */
  lf_swap       = (p_clntbuf->l_testbit == GPS__ENV_TESTBIT) ? 0 : 1;
  l_endian_serv = p_clntbuf->l_endian;

  if (lf_swap)
    /* + + + + + + + + + + + + + + + + + */
    /* +++ swap after every receive  +++ */
    /* + + + + + + + + + + + + + + + + + */
  {
    l_sts     = F__SWAP(&p_clntbuf->l_testbit,CLNT__BUFH_LW,0);

    l_len_lw2 = CLNT__REST_LW + p_clntbuf->l_dlen/4; /* <N> !!! */
    l_sts     = F__SWAP(&p_clntbuf->l_inbuf_read_cnt, l_len_lw2, 0);

    if (p_clntbuf->l_testbit != GPS__ENV_TESTBIT) { /* <T> */
      printf("F-%s: Error swapping first buffer from client\n",
             c_modnam);
      f_stc_close(&s_tcpcomm_ec);
      return(-1);
    }
  }

  /* + + + + + + + + + + + + + + + + + + + + + + + + + */
  /* +++ first buffer should be a message buffer!  +++ */
  /* + + + + + + + + + + + + + + + + + + + + + + + + + */
  if (p_clntbuf->l_buffertype & 16) {
  }

  if (p_clntbuf->l_buffertype & 2) {
    /* buffer contains message   */
    /*
         switch (p_clntbuf->l_msgtyp & 15)
         {
            case 1:
            case 2:  printf("MSG-type:W:  %s\n", p_clntbuf->c_message);  break;
            case 4:  printf("MSG-type:E:  %s\n", p_clntbuf->c_message);  break;
            case 8:  printf("MSG-type:F:  %s\n", p_clntbuf->c_message);  break;
            default: printf("Unknown MSG-type:%d:\n%s\n",p_clntbuf->l_msgtyp,p_clntbuf->c_message);
         }
    */
  }
  return(STC__SUCCESS);
} /* f_evcli_con */

/***************************************************************************/
int f_evcli_buf(s_evt_channel* ps_chan)
/***************************************************************************/
{
  s_ve10_1* ps_ve10_1;
//  int ii;
  char* ps_buf;
  /* ++++++++++++++++++++++++++++++ */
  /* +++ send acknowledge buffer +++ */
  /* ++++++++++++++++++++++++++++++ */
  l_status = f_send_ackn(1, ps_chan->l_channel_no);
  if (l_status != TRUE) {
    printf("E-%s: Error sending acknowledge: f_send_ackn()!\n", c_modnam);
    f_stc_close(&s_tcpcomm_ec);
    return(l_status);
  }
  /* +++++++++++++++++++++++++ */
  /* +++ read input buffer +++ */
  /* +++++++++++++++++++++++++ */
  p_clntbuf =  (struct s_clntbuf*) ps_chan->pc_io_buf;
  ps_buf=ps_chan->pc_io_buf; /* save for comparison */
  memset(p_clntbuf,0, ps_chan->l_io_buf_size);
  l_status = f_read_server(ps_chan,
                           &l_retval,
                           l_timeout,
                           ps_chan->l_channel_no);
  /* in case pc_io_buf has been reallocated */
  if(ps_buf != ps_chan->pc_io_buf) {
    f_clnup(v_mem_clnup, NULL); /* free all old buffers */
    p_clntbuf =  (struct s_clntbuf*) ps_chan->pc_io_buf;
    f_clnup_save(v_mem_clnup, (int*) p_clntbuf);
  }
  if (l_status != TRUE) {
    printf("E-%s: Error reading buffer: f_read_server()!\n", c_modnam);
    f_stc_close(&s_tcpcomm_ec);
    return(l_status);
  }
  l_clnt_sts = 0;                                                /* reset */

  /* +++++++++++++++++++++++++++++++++ */
  /* +++ swap every buffer in loop +++ */
  /* +++++++++++++++++++++++++++++++++ */
  if (lf_swap) {
    l_sts     = F__SWAP(&p_clntbuf->l_testbit,CLNT__BUFH_LW, 0);
    l_len_lw2 = CLNT__REST_LW + p_clntbuf->l_dlen/4; /* <N> !!! */

    /*  4 byte swap */
    pl_inbuf = &p_clntbuf->l_inbuf_read_cnt;
    l_sts = F__SWAP(pl_inbuf, l_len_lw2, 0);
  }
  /* printf("Buffer %8d bytes, dlen %8d events %6d\n",l_retval,p_clntbuf->l_dlen,p_clntbuf->l_events);
         ps_ve10_1=(s_ve10_1 *)&p_clntbuf->c_buffer[0];
          for(ii=0;ii<p_clntbuf->l_events;ii++)
    {printf("Event %2d, t/s %3d %2d, len %d\n",ii+1,ps_ve10_1->i_type,ps_ve10_1->i_subtype,ps_ve10_1->l_dlen);
    ps_ve10_1 = (s_ve10_1 *) ((short *)ps_ve10_1 + ps_ve10_1->l_dlen + 4); }
  */
  /* ++++++++++++++++++++++++ */
  /* +++ message handling +++ */
  /* ++++++++++++++++++++++++ */
  l_sts=STC__SUCCESS;
  if (p_clntbuf->l_buffertype & 2) {
    /* buffer contains message   */
    switch (p_clntbuf->l_msgtyp & 15) {
    case 1:
    case 2:
      if((strstr(p_clntbuf->c_message,"no event data") == NULL)&
          (strstr(p_clntbuf->c_message,"flushed") == NULL)) {
        printf("MSG-type:W:  %s\n", p_clntbuf->c_message);
      }
      break;
    case 4:
      printf("MSG-type:E:  %s\n", p_clntbuf->c_message);
      break;
    case 8:
      printf("MSG-type:F:  %s\n", p_clntbuf->c_message);
      break;
    default:
      printf("Unknown MSG-type:%d:\n%s\n",p_clntbuf->l_msgtyp,p_clntbuf->c_message);
    }
    l_sts=STC__TIMEOUT; /* buffer without events */
  } else {
    if(p_clntbuf->l_events == 0) {
      l_sts=STC__TIMEOUT;
    }
  }
  ps_chan->pc_evt_buf = (char*)&p_clntbuf->c_buffer[0];
  ps_chan->l_evt_buf_posi = 1; /* number of events */
  ps_ve10_1 = (s_ve10_1*) ps_chan->pc_evt_buf;
  return(l_sts);
}  /*  end f_evcli_buf  */

/***************************************************************************/
int f_evcli_evt(s_evt_channel* ps_chan)
/***************************************************************************/
{
  int* ps_int;
  s_ve10_1* ps_ve10_1;

  p_clntbuf =  (struct s_clntbuf*) ps_chan->pc_io_buf;
  if(ps_chan->l_evt_buf_posi < p_clntbuf->l_events) {
    ps_chan->l_evt_buf_posi++;
    ps_ve10_1 = (s_ve10_1*) ps_chan->pc_evt_buf;
    ps_int   = (int*) ps_chan->pc_evt_buf;
    ps_int += ps_ve10_1->l_dlen/2 + 2;
    ps_chan->pc_evt_buf = (char*) ps_int;
    return(STC__SUCCESS);
  } else { return(-1); }
}
/***************************************************************************/
int f_evcli_close(s_evt_channel* ps_chan)
/***************************************************************************/
{
  /* ++++++++++++++++++++++++++++++ */
  /* +++ send acknowledge buffer +++ */
  /* ++++++++++++++++++++++++++++++ */
  l_status = f_send_ackn(8, ps_chan->l_channel_no);
  if (l_status != TRUE) {
    printf("E-%s: Error sending acknowledge: f_send_ackn()!\n", c_modnam);
    return(l_status);
  }
  f_clnup(v_mem_clnup, NULL);
  f_stc_discclient(ps_chan->l_channel_no);
  f_stc_close(&s_tcpcomm_ec);
  return(STC__SUCCESS);
}


/*2+F_FLTDSCR***+******************************************************/
/*                                                                    */
/*+ Module      : F_FLTDSCR                                           */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_fltdscr(p_clnt_filter)                      */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read and check the event filter and construct the   */
/*                filter descriptor.                                  */
/*                                                                    */
/*+ ARGUMENTS   : p_clnt_filter: Pointer to structure s_clnt_filter   */
/*                                                                    */
/*+ FUNCTION    : Read and check the event filter and construct the   */
/*                filter descriptor.  Output via "printf".            */
/*                See also I$PS_FLTDSC_PRTCL                          */
/*                                                                    */
/*+ Return type : int (32 bit)                                       */
/*+ Status codes: bit 0: success                                      */
/*                bit 1: warning                                      */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
int f_fltdscr(p_clnt_filter)           /* read filter, check and         */
/* constr. flt_descriptor         */
struct s_clnt_filter* p_clnt_filter;
{
  static char               c_modnam[] = "f_fltdscr";
  struct s_filter*    p_filter;
  struct s_opc1*      p_opc1;
  struct s_flt_descr* p_flt_descr;
//  struct s_pat1*      p_pat1;
//  struct s_pat2*      p_pat2;
//  struct s_pat3*      p_pat3;

  short              i_fltdescnt = 0;
  short              i_fltcnt = 0;
  short              i_fltblkcnt = 0;
  short              i, i_flt_len,
                     i_fltblkbeg, i_fltblkend, j;
  short              if_newfltblk = 1;
  short              i_next_fltblk = 0; // SL 16.11.2009 add initialization to 0
  short              i_descr;        /* test */
  int               l_evtdescr, *pl_evtdescr, *pl_sev1descr, *pl_sev2descr;
  short              i_lasevtflt, i_1stsevflt;

//  int unsigned      l_status, l_sts;
  int unsigned      l_retsts = 0;

  /* +++ action +++ */
  if (i_debug == 2) {
    printf("--->D-%s: addr_filter p:%d\n", c_modnam, (int)p_clnt_filter);
  }

  /* init pointer */
  p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[0];

  /* +++ loop over all filter block descriptors +++ */
  for (i = 0; i < GPS__MAXFLT; i++) {
    p_filter    = (struct s_filter*)    &p_clnt_filter->filter[i];
    p_opc1      = (struct s_opc1*)      &p_filter->l_opcode;

    if (i_debug == 2)
      printf("D-%s: i:%d opc:%x flt_len:%d\n",
             c_modnam,
             i,
             p_filter->l_opcode,
             p_opc1->h_flt_len);

    if (i == i_next_fltblk) {
      if_newfltblk = 1;
    }

    if (p_opc1->h_flt_len == 0) {
      i_fltcnt = i;
      p_opc1->h_next_fltblk    = 0;    /* no next descriptor              */
      p_flt_descr->h_nextdescr = 0;    /* no next descriptor              */
      break;              /* no more filter                  */
    } /* if (p_opc1->h_next_fltblk == 0) */

    /*      if (p_opc1->b3_opc == 0) {
     *        printf("I-%s: b3_opc == 0. Take all events!\n",
     *           c_modnam);
     *        }
     */

    if (if_newfltblk) {
      if_newfltblk = 0;
      i_fltblkcnt++;
      i_flt_len     = p_opc1->h_flt_len;
      i_next_fltblk = i + i_flt_len;
      i_fltblkbeg   = i;
      i_fltblkend   = i_next_fltblk - 1;

      if (p_opc1->b1_selwrt == 1) {
        /* write block               */

        p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[0];
        i_descr = 0;         /* test */

        if (p_flt_descr->hf_wrtdescr == 1 &&
            p_clnt_filter->flt_descr[0].i_descriptors <= 0) {
          printf("W-%s: >1 write blocks, previous one(s) ignored!\n",
                 c_modnam);
          l_retsts = l_retsts | 2;
        }

        p_flt_descr->hf_wrtdescr = 1;
        p_flt_descr->hf_fltdescr = 0;
        p_flt_descr->h_fltblkbeg = i_fltblkbeg;
        p_flt_descr->h_fltblkend = i_fltblkend;
        p_flt_descr->h_nextdescr = 1;

        /* save write block values */
        p_clnt_filter->if_wrtevt = (p_opc1->b1_evtsev == 1) ? 1 : 0;
        p_clnt_filter->if_wrtsev = (p_opc1->b1_evtsev != 1) ? 1 : 0;
      } /* if (p_opc1->b1_selwrt == 1) */

      if (p_opc1->b1_selflt == 1) {
        /* filter block              */
        if (i_fltdescnt == 0) {
          i_fltdescnt++;
        }
        i_descr = i_fltdescnt;              /* test */
        p_flt_descr = (struct s_flt_descr*)
                      &p_clnt_filter->flt_descr[i_fltdescnt];
        p_flt_descr->hf_wrtdescr = 0;
        p_flt_descr->hf_fltdescr = 1;
        p_flt_descr->h_fltblkbeg = i_fltblkbeg;
        p_flt_descr->h_fltblkend = i_fltblkend;
        p_flt_descr->h_nextdescr = ++i_fltdescnt;
        /* save write block values */
        if (p_opc1->b1_evtsev == 1) {
          p_clnt_filter->if_fltevt = 1;
        } else {
          p_clnt_filter->if_fltsev = 1;
        }
      }    /* if (p_opc1->b1_selflt == 1) */

    } /* if (if_newfltblk) */

    /* identical values for the whole flt blk */
    p_opc1->h_flt_len     = i_flt_len;
    p_opc1->h_next_fltblk = i_next_fltblk;

    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    /* ++++ build pattern and offset values from h_fltspec ++++ */
    /* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

    /* ++++ check if Filter specification is valid ++++ */
    if ((p_opc1->h_fltspec > 15) && (p_opc1->b1_evtsev == 1)) {
      printf("E-%s: Filter specification %d invalid for events\n",
             c_modnam,
             p_opc1->h_fltspec);
      return(FALSE);                /* abort with error                */
    }
    if ((p_opc1->h_fltspec < 2) && (p_opc1->b1_evtsev != 1)) {
      printf("E-%s: Filter specification %d invalid for subevents\n",
             c_modnam,
             p_opc1->h_fltspec);
      return(FALSE);                /* abort with error                */
    }



    switch (p_opc1->h_fltspec) {
    case 0:                       /* ++++ take all ++++ */
      if (p_opc1->b3_opc != 0) {
        printf("W-%s: Take all. Set opcode to 0, next time\n",
               c_modnam);
        p_opc1->b3_opc = 0;
        l_retsts = l_retsts | 2;
      }
      break;

    case 1:                       /* ++++ trigger  ++++ */
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = -5; /* trigger = event + 5 W        */
      p_filter->l_pattern = p_filter->l_pattern & 0xFFFF;
      break;

    case 2:                       /* ++++ pattern and offset ++++ */
      break;

    case 4:                /* W ++++ type ++++ */
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = -2; /* type = evt(sev) + 2 W        */
      p_filter->l_pattern = p_filter->l_pattern & 0xFFFF;

      break;

    case 8:                       /* W ++++ subtype ++++ */
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = -3; /* subtype = evt(sev) + 3 W     */
      p_filter->l_pattern = p_filter->l_pattern & 0xFFFF;

      break;

    case 12:                     /* LW ++++ type and subtype ++++ */
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = 1; /* type-subtype = evt(sev) + 1 LW*/

      break;

    case 16:                     /* W ++++ procid ++++ */
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = -4; /* procid = sev + 4 W        */
      p_filter->l_pattern = p_filter->l_pattern & 0xFFFF;

      break;

    case 32:               /* W ++++ subcrate,contr ++++*/
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = -5; /* subcrate,contr = sev + 5 W */
      p_filter->l_pattern = p_filter->l_pattern & 0xFFFF;

      break;

    case 48:               /* LW ++++procid,subcr,contr ++++*/
      /*       if (p_filter->l_offset >= 0)
       */
      p_filter->l_offset = 2; /* procid,subc,ctrl = sev + 2 LW */

      break;

    default:
      printf("W-%s: FLTSPEC %d NOT FOUND\n",
             c_modnam,
             p_opc1->h_fltspec);
      l_retsts = l_retsts | 2;
    }                            /* switch case  */



  }    /* for */

  p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[0];
  if (p_flt_descr->hf_wrtdescr != 1) {
    printf("E-%s: The write filter is missing! Filter is invalid!\n",
           c_modnam);
    return(FALSE);
  }

  if (!(p_clnt_filter->if_fltevt || p_clnt_filter->if_fltsev)) {
    printf("E-%s: The filter itself is missing! Filter is invalid!\n",
           c_modnam);
    return(FALSE);
  }

  /*   printf(
   *     "I-%s: p_clnt:%d: found %d flts in %d blks with %d descript.\n",
   *         c_modnam,
   *         p_clnt_filter,
   *         i_fltcnt,
   *         i_fltblkcnt,
   *         i_fltdescnt);
   */

  if ( (p_clnt_filter->if_fltevt == 1) && (p_clnt_filter->if_fltsev == 1) ) {
m_sort_descr:;                      /* sort event and subevent filter  */
    i_lasevtflt = 0;           /* last event filter     init      */
    i_1stsevflt = i_fltdescnt;     /* first subevent filter init        */
    /* sort filter blocks: flt event should come before flt sev */
    for (i = 1; i < i_fltdescnt; i++) {
      p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[i];
      p_filter    = (struct s_filter*)
                    &p_clnt_filter->filter[(int)p_flt_descr->h_fltblkbeg];
      p_opc1      = (struct s_opc1*)      &p_filter->l_opcode;

      if ( (p_opc1->b1_selflt == 1) && (p_opc1->b1_evtsev == 1) ) {
        i_lasevtflt = i;  /* save last evt flt found         */
      }

      if ( (p_opc1->b1_selflt == 1) &&
           (p_opc1->b1_evtsev == 0) &&
           (i_1stsevflt == i_fltdescnt) ) {
        i_1stsevflt = i;  /* save last evt flt found         */
      }

      if (i_1stsevflt < i_lasevtflt) { /* evt flt after sev flt           */
        printf(
          "W-%s 1stsevflt:%d lastevtflt:%d. Evt flt should come first\n",
          c_modnam,
          i_1stsevflt,
          i_lasevtflt);
        l_retsts = l_retsts | 2;
        /* copy first LW from evt descr */
        pl_evtdescr = (int*) &p_clnt_filter->flt_descr[i_lasevtflt];
        l_evtdescr  = *pl_evtdescr;
        /* shift the subevent descriptors */
        for (j = i_lasevtflt; j > i_1stsevflt; j--) {
          pl_sev1descr  = (int*) &p_clnt_filter->flt_descr[j-1];
          pl_sev2descr  = (int*) &p_clnt_filter->flt_descr[j];
          *pl_sev2descr = *pl_sev1descr;
        }
        pl_evtdescr  = (int*) &p_clnt_filter->flt_descr[i_1stsevflt];
        *pl_evtdescr = l_evtdescr;
        goto m_sort_descr;            /* until descr is in right order   */
      }    /* if */

    }    /* for */

  }    /* if (...if_fltevt... && ...if_fltsev...) */

  /* + + + Max number of descriptors + + + */
  p_clnt_filter->flt_descr[0].i_descriptors = i_fltdescnt;

  /* ++++ check the subevent filter blocks                       ++++ */
  /*    + the first filter in the sev flt blk identifies the sev +    */
  /*    + normaly Procid or Procid + Subcrate                    +    */
  if (p_clnt_filter->if_fltsev == 1) {
    for (i = 1; i < p_clnt_filter->flt_descr[0].i_descriptors; i++) {
      p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[i];
      /* ++ addr of the first filter in the flt blk ++ */
      p_filter    = (struct s_filter*)
                    &p_clnt_filter->filter[(int)p_flt_descr->h_fltblkbeg];
      p_opc1      = (struct s_opc1*)      &p_filter->l_opcode;

    } /* for */
  } /* if (p_clnt_filter->if_fltsev... */

  return(l_retsts | 1);

} /* end f_fltdscr */





/*2+F_FLTRD***+********************************************************/
/*                                                                    */
/*+ Module      : F_FLTRD                                             */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_fltrd(p_clnt_filter, c_file)                */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Reads filter specification from a file              */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+    p_clnt_filter: Pointer to structure s_clnt_filter              */
/*+    c_file       : Pointer to file name string                     */
/*                                                                    */
/*+ FUNCTION    : Opens the file and reads filter specification       */
/*                                                                    */
/*+ Return type : int (32 bit)                                       */
/*+ Status codes: -                                                   */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*-               25-Jan-1994 : problems with sscanf removed (RSM)    */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
int f_fltrd(p_clnt_filter, c_file)
struct s_clnt_filter* p_clnt_filter;
char*                 c_file;                     /* ptr to file name        */
{

  /* ++++ declaration ++++ */
  FILE*               infile;

  static char        c_modnam[] = "f_fltrd";
  struct s_filter*    p_filter;
  struct s_opc1*      p_opc1;
//  struct s_flt_descr* p_flt_descr;
//  struct s_pat1*      p_pat1;
//  struct s_pat2*      p_pat2;
//  struct s_pat3*      p_pat3;

  char               c_retmsg[256];
  char               c_line[80], c_comment[80], *c_fsts, *p_com, *p_minus;
  short              i_fltblklen = 0;
  short         i_currflt = 0;
  short              i;//, j;
  int               /*l, */l_scan=0;

  int unsigned      l_pattern;
  int               l_offset;

  short              i_evtsev,i_selflt,i_selwrt,i_opc,i_lnkf1,
                     i_lnkf2,i_fltspec;
  short              if_hex, if_comment;

  char*               fgets( char *str, int maxchar, FILE *file_ptr);

  /* +++ action +++ */

  if ( (infile = fopen(c_file,"r"))  == 0) {
    /* open file for data input   */
    sprintf(c_retmsg,"E-%s: fopen(File=%s) ",
            c_modnam,
            c_file);
    perror(c_retmsg);
    fclose(infile);
    return(FALSE);
  }

  printf("Filter definition from file %s\n", c_file);
  printf("=======================================\n");

  while (l_scan != EOF && i_fltblklen < GPS__MAXFLT) {
m_read_nxtblklen:
    ;

    memset(c_line,0,sizeof(c_line));

    if ( (c_fsts = fgets(c_line, sizeof(c_line), infile)) == 0) {
      if (i_debug == 2)
        printf("D-%s: File=%s: Last input line.\n",
               c_modnam,
               c_file);
      break;
    }

    if_comment = 0;                      /* reset flag                    */
    p_com = strpbrk(c_line,"!/*");       /* find position of comment      */
    if (p_com != NULL) {
      /* found a comment               */
      if_comment = 1;                   /* set flag                      */
      strcpy(c_comment,p_com);          /* copy comment                  */
      *p_com = '\0';                    /* mark end of str at beg of comm*/
      if (i_debug == 2) {
        printf(" - D: comment:%s", c_comment);
      }

    }

    l_scan = sscanf(c_line, "%hd", &i_fltblklen);
    if (if_comment && (l_scan < 1) ) {
      goto m_read_nxtblklen;
    }

    if (l_scan == EOF || l_scan == 0 || c_fsts == NULL) {
      if (i_debug == 2) {
        printf("D-%s: Last input line.\n",c_file);
      }
      break;
    }

    if (i_fltblklen + i_currflt >= GPS__MAXFLT) {
      printf("E-%s: too long. Last filter block ignored\n",
             c_modnam);
      fclose(infile);
      return(3);
    }
    if (i_debug == 2) {
      printf("D-%s: Fltblklen:%d\n", c_modnam, i_fltblklen);
    }

    for (i = i_currflt; i < i_fltblklen + i_currflt; i++) {
m_read_nxtline:
      ;

      memset(c_line,0,sizeof(c_line));

      if ( (c_fsts = fgets(c_line, sizeof(c_line), infile)) == 0) {
        sprintf(c_retmsg,"E-%s: Error reading:fgets(File=%s) ",
                c_modnam,
                c_file);
        perror(c_retmsg);
        fclose(infile);
        return(FALSE);
      }

      if (i_debug == 2) {
        printf("D-%s: line:%s", c_modnam, c_line);
      }

      if_comment = 0;                   /* reset flag                    */
      p_com = strpbrk(c_line,"!/*");    /* find position of comment      */
      if (p_com != NULL) {
        /* found a comment               */
        if_comment = 1;                /* set flag                      */
        strcpy(c_comment,p_com);       /* copy comment                  */
        *p_com = '\0';                 /* mark end of str at beg of comm*/
        if (i_debug == 2) {
          printf(" - D: comment:%s", c_comment);
        }

      }

      l_scan = sscanf(c_line,"%hd %hd %hd %hd %hd %hd %hd %d %d",
                      &i_evtsev,
                      &i_selflt,
                      &i_selwrt,
                      &i_opc,
                      &i_lnkf1,
                      &i_lnkf2,
                      &i_fltspec,
                      &l_pattern,
                      &l_offset);
      if_hex = 0;                           /* set flag null             */
      if (l_scan == 9) {
        goto m_ok_assign;
      }

      if_hex = 1;                           /* set flag null             */
      p_minus = strchr(c_line,'-');         /* find minus sign in offset */

      if (p_minus != 0) {                   /* found minus sign          */
        *p_minus = ' ';  /* replace minus with blank  */
      }

      l_scan = sscanf(c_line,"%hd %hd %hd %hd %hd %hd %hd %d %d",
                      &i_evtsev,
                      &i_selflt,
                      &i_selwrt,
                      &i_opc,
                      &i_lnkf1,
                      &i_lnkf2,
                      &i_fltspec,
                      &l_pattern,
                      &l_offset);

      l_offset = (p_minus != NULL) ? -l_offset : l_offset;

      if (l_scan < 9) {
        if (if_comment) {
          goto m_read_nxtline;
        }

        printf(
          "E-%s: scanned only %d(of 9) var., last 2 must be dec or hexa\n",
          c_modnam,
          l_scan);
        fclose(infile);
        return(FALSE);
      }

m_ok_assign:
      if (i_debug == 2) {
        sprintf( c_retmsg,
                 "%s es:%d f:%d w:%d opc:%d lf1:%d lf2:%d flt:%d p:%x o:%x",
                 (if_hex) ? "HEX:" : "DEC:",
                 i_evtsev,
                 i_selflt,
                 i_selwrt,
                 i_opc,
                 i_lnkf1,
                 i_lnkf2,
                 i_fltspec,
                 l_pattern,
                 l_offset);
        printf("D-%s: %s\n", c_modnam, c_retmsg);
      }

      p_filter    = (struct s_filter*)    &p_clnt_filter->filter[i];
      p_opc1      = (struct s_opc1*)      &p_filter->l_opcode;

      p_opc1->h_next_fltblk = (char) i_fltblklen + i_currflt;
      p_opc1->h_flt_len     = (char) i_fltblklen;

      p_filter->l_pattern   = l_pattern;
      p_filter->l_offset    = l_offset;

      p_opc1->b1_evtsev =        i_evtsev;
      p_opc1->b1_selflt =        i_selflt;
      p_opc1->b1_selwrt =        i_selwrt;
      p_opc1->b3_opc    =        i_opc;
      p_opc1->b1_lnkf1  =        i_lnkf1;
      p_opc1->b1_lnkf2  =        i_lnkf2;
      p_opc1->h_fltspec = (char) i_fltspec;

    } /* for */

    i_currflt = (short) p_opc1->h_next_fltblk;

  } /* while */

  fclose(infile);

  return(TRUE);
}



/*2+F_TYPFLT***+*******************************************************/
/*                                                                    */
/*+ Module      : F_TYPFLT                                            */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_typflt(p_clnt_filter)                       */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Type the filter conditions.                         */
/*                                                                    */
/*+ ARGUMENTS   : p_clnt_filter: Pointer to s__clnt_filter            */
/*                                                                    */
/*+ FUNCTION    : Type the filter conditions. Output via "printf".    */
/*                See also I$PS_TYPFLT_PRTCL.                         */
/*                                                                    */
/*+ Return type : int (32 bit) 1: success   0: fault                 */
/*+ Status codes: -                                                   */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*-               12-Jan-1994 : Bug removed in subcrate,control (RSM) */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
int f_typflt(p_clnt_filter)
struct s_clnt_filter* p_clnt_filter;
{
  static char               c_modnam[] = "f_typflt";
  struct s_filter*    p_filter;
  struct s_opc1*      p_opc1;
  struct s_flt_descr* p_flt_descr;
  struct s_pat1*      p_pat1;
  struct s_pat2*      p_pat2;
  struct s_pat3*      p_pat3;

  short              i_fltdescnt, j, i;

  /* +++ action +++ */

  /* + + + Max number of descriptors + + + */
  i_fltdescnt = p_clnt_filter->flt_descr[0].i_descriptors;

  /* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + */
  /* + + + Output filter conditions for Write and Filter     + + + */
  /* + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + */
  /*   printf("Explanation: object OPCODE mask\n===========\n");
   */
  if ( (i_debug == 1) || (i_debug == 2) )
    printf(
      "Write:%s %s   Filter:%s %s         object OPCODE mask",
      (p_clnt_filter->if_wrtevt > 0) ? "EVENT" : "",
      (p_clnt_filter->if_wrtsev > 0) ? "SUBEVENT" : "",
      (p_clnt_filter->if_fltevt > 0) ? "EVENT" : "",
      (p_clnt_filter->if_fltsev > 0) ? "SUBEVENT" : "");
  for (i = 0; i < i_fltdescnt; i++) {
    p_flt_descr = (struct s_flt_descr*) &p_clnt_filter->flt_descr[i];
    p_filter    = (struct s_filter*)
                  &p_clnt_filter->filter[(int)p_flt_descr->h_fltblkbeg];
    p_opc1      = (struct s_opc1*)      &p_filter->l_opcode;

    if ( (i_debug == 1) || (i_debug == 2) ) {
      if (i > 1) {
        printf("\n<<%s>>\n", (p_opc1->b1_lnkf2 == 1) ? "A_N_D" : "O_R" );
      }
      printf("\n=>>FILTER set %d :",i);
      printf(" Select:%s Filter:%s Write:%s    Filter[%d:%d]:\n",
             (p_opc1->b1_evtsev == 1) ? "EVENT" : "SUBEVENT",
             (p_opc1->b1_selflt == 1) ? "ON" : "OFF",
             (p_opc1->b1_selwrt == 1) ? "ON" : "OFF",
             p_flt_descr->h_fltblkbeg,
             p_flt_descr->h_fltblkend );
    }

    /* +++ subevt flt blk id +++ */
    if (p_opc1->b1_evtsev == 0 && p_opc1->b1_selflt == 1) {
      p_filter = (struct s_filter*)
                 &p_clnt_filter->filter[(int)p_flt_descr->h_fltblkbeg];
      if ( (i_debug == 1) || (i_debug == 2) )
        printf(
          "   Filter set id is fltspec:%d == mask:H%x  (see 1st filt. below)\n",
          p_opc1->h_fltspec,
          p_filter->l_pattern);
    }


    /* +++ loop over all filters in this filter block +++ */
    for (j =  p_flt_descr->h_fltblkbeg;
         j <= p_flt_descr->h_fltblkend;
         j++) {
      p_filter = (struct s_filter*) &p_clnt_filter->filter[j];
      p_opc1 = (struct s_opc1*) &p_filter->l_opcode;
      if ( (j > p_flt_descr->h_fltblkbeg) &&
           (p_opc1->b1_selflt == 1)       &&
           ( (i_debug == 1) || (i_debug == 2) ) ) {
        printf("  <%s>\n", (p_opc1->b1_lnkf1 == 1) ? "A_N_D" : "O_R" );
      }
      if ( (i_debug == 1) || (i_debug == 2) ) {
        printf("  =>%2d: opcode: ", i + 1);
      }

      switch (p_opc1->b3_opc) {
      case 0:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("!! (ALL)   ");
        }
        break;
      case 1:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("== (IDENT) ");
        }
        break;

      case 2:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("&& (ANY)   ");
        }
        break;

      case 3:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("&= (INCL)  ");
        }
        break;

      case 4:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("^= (EXCL)  ");
        }
        break;

      case 5:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("<  (LT)    ");
        }
        break;

      case 6:
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf(">= (GE)    ");
        }
        break;

      default:
        printf("W-OPCODE %d NOT FOUND\n",p_opc1->b3_opc);
      }

      switch (p_opc1->h_fltspec) {
      case 0:                       /* ++++ take all ++++ */
        if (p_opc1->b3_opc != 0) {
          p_opc1->b3_opc = 0;
          printf("W-%s: Take all. Opcode is %d\n",
                 c_modnam,
                 p_opc1->b3_opc);
        }
        break;

      case 1:                       /* ++++ trigger  ++++ */
        p_pat1 = (struct s_pat1*) &p_filter->l_pattern;
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("trigger:%2d",p_pat1->i_trigger);
          printf(" (mask:%d offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 2:                       /* ++++ pattern and offset ++++ */
        if ( (i_debug == 1) || (i_debug == 2) )
          printf("mask:H%x offset:%d %s\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ?
                 "LW" : "W" );
        break;

      case 4:                /* W ++++ type ++++ */
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("type:%d ",
                 p_filter->l_pattern);
          printf(" (mask:%d offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 8:                       /* W ++++ subtype ++++ */
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("subtype:%d ",
                 p_filter->l_pattern);
          printf(" (mask:%d offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 12:                     /* W ++++ type and subtype ++++ */
        p_pat3 = (struct s_pat3*) &p_filter->l_pattern;
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("type:%d subtype:%d",
                 p_pat3->i_type,
                 p_pat3->i_subtype);
          printf(" (mask:H%x offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 16:               /* ++++ procid ++++*/
        p_pat2 = (struct s_pat2*) &p_filter->l_pattern;
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("procid:%d ",
                 p_pat2->i_procid);
          printf(" (mask:%d offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 32:               /* W ++++ subcrate,contr ++++*/
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("subcrate:%d control:%d",
                 p_filter->l_pattern & 0x00FF,
                 ((unsigned) (p_filter->l_pattern & 0xFF00)) >> 8);
          printf(" (mask:H%x offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      case 48:               /* LW ++++procid,subcr,contr ++++*/
        p_pat2 = (struct s_pat2*) &p_filter->l_pattern;
        if ( (i_debug == 1) || (i_debug == 2) ) {
          printf("procid:%2d subcr:%d contr:%d",
                 p_pat2->i_procid,
                 p_pat2->h_subcrate,
                 p_pat2->h_control);
          printf(" (mask:H%x offs:%d %s)\n",
                 p_filter->l_pattern,
                 (p_filter->l_offset >= 0) ?
                 p_filter->l_offset : -p_filter->l_offset,
                 (p_filter->l_offset >= 0) ? "LW" : "W");
        }
        break;

      default:
        printf("W-FLTSPEC %d NOT FOUND\n",p_opc1->h_fltspec);
      }                            /* switch case  */

      /* ++++ check if Filter specification is valid ++++ */
      if ((p_opc1->h_fltspec > 15) && (p_opc1->b1_evtsev == 1)) {
        printf("E-%s: Filter specification %d invalid for events\n",
               c_modnam,
               p_opc1->h_fltspec);
        return(FALSE);                /* abort with error                */
      }
      if ((p_opc1->h_fltspec < 2) && (p_opc1->b1_evtsev != 1)) {
        printf("E-%s: Filter specification %d invalid for subevents\n",
               c_modnam,
               p_opc1->h_fltspec);
        return(FALSE);                /* abort with error                */
      }

    } /* for (j... */

  } /* for (i... */
  if ( (i_debug == 1) || (i_debug == 2) ) {
    printf("\n\n");
  }

  return(TRUE);
} /* end f_typflt */




/*2+F_READ_SERVER***+**************************************************/
/*                                                                    */
/*+ Module      : F_READ_SERVER                                       */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_read_server(p_clntbuf,                      */
/*                                       p_bytrd,                     */
/*                                       l_timeout,                   */
/*                                       i_chan)                      */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read a buffer from the server                       */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+    p_clntbuf: Pointer to structure s_clntbuf                      */
/*+    p_bytrd  : Pointer to (int) Number of read bytes              */
/*+    l_timeout: (int) Timeout in seconds                           */
/*+    i_chan   : (int) channel number                                */
/*                                                                    */
/*+ FUNCTION    : Read a buffer of the type s_clntbuf from the        */
/*                server.                                             */
/*                                                                    */
/*+ Return type : int (32 bit)                                       */
/*+ Status codes: 1: success                                          */
/*                0: fault                                            */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*-               26-Jan-1994 : Swap inserted (RSM)                   */
/*-               24-Feb-1994 : Bug removed (RSM)                     */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
int        f_read_server(ps_chan, p_bytrd, l_timeout, i_chan)
s_evt_channel* ps_chan;
int*             p_bytrd;
int             l_timeout;
int              i_chan;
{
  /* ++++ declarations ++++ */
  int             l_maxbytes;
  int            l_status,ii,im,*pl;                              /* !!! */
  int           l_bytrec, l_2ndbuf_byt;
  int           l_buftord, l_buffertype;
  static char    c_modnam[] = "f_read_server";
  char           c_retmsg[256];
  char* pc;
  int* pl_d,*pl_s;
//  s_ve10_1* ps_ve10_1;

  /* ++++ action       ++++ */

  p_clntbuf =  (struct s_clntbuf*) ps_chan->pc_io_buf;
  l_maxbytes=ps_chan->l_io_buf_size;
  /* + + + + + + + + + + + + + + + */
  /* + + + read first buffer + + + */
  /* + + + + + + + + + + + + + + + */
  if (i_debug == 2)
    printf(
      "D-%s: **Rd 1st Buf: at %8x to %8x = %d bytes\n",
      c_modnam,
      (int)(char*) p_clntbuf,
      (int)(((char*) p_clntbuf) + (CLNT__SMALLBUF - 1)),
      CLNT__SMALLBUF);


  *p_bytrd = CLNT__SMALLBUF;
  l_status = f_stc_read( (char*) p_clntbuf,
                         (int) CLNT__SMALLBUF,
                         i_chan,
                         l_timeout);

  if (l_status != STC__SUCCESS) {
    printf("E-%s: Error reading first buffer. Msg follows:",c_modnam);
    f_stc_disperror(l_status,c_retmsg, 0);
    return(FALSE);
  }

  /* +++ copy the relevant length values +++ */
  l_buftord    = p_clntbuf->l_numbuftosnd;
  l_bytrec     = p_clntbuf->l_bytestosnd;
  l_buffertype = p_clntbuf->l_buffertype;

  /* +++ test for byte swap +++ */
  if (p_clntbuf->l_testbit != GPS__ENV_TESTBIT) {
    if (i_debug == 2)
      printf("D-%s: Need swap to receive from %s to %s ENDIAN\n",
             c_modnam,
             (p_clntbuf->l_endian == 0) ? "LITTLE" : "BIG",
             (GPS__ENV_ENDIAN     == 0) ? "LITTLE" : "BIG");

    l_status = F__SWAP(&l_buftord, 1, 0);
    if (l_status != 0) { printf("E-%s: Error swapping l_buftord. l_sts:%d\n", c_modnam,l_status); }
    l_status = F__SWAP(&l_bytrec , 1, 0);
    if (l_status != 0) { printf("E-%s: Error swapping l_bytrec l_sts:%d\n", c_modnam,l_status); }
    l_status = F__SWAP(&l_buffertype, 1, 0);
    if (l_status != 0) { printf("E-%s: Error swapping l_buffertype l_sts:%d\n", c_modnam,l_status); }
    if (i_debug == 2)
      printf("D-%s: buffers:%d, bytes:%d, buffertype:%d\n",
             c_modnam,
             l_buftord,
             l_bytrec,
             l_buffertype);

  }
  if (l_buftord == 1) {
    if (l_bytrec  > CLNT__SMALLBUF) {
      printf("E-%s: Buffer sent:%d Bytes_to_rd:%d > %d\n",
             c_modnam,
             l_buftord,
             l_bytrec,
             CLNT__SMALLBUF);
      return(FALSE);
    }
    goto m_snd_ackn;
  }

  l_2ndbuf_byt = l_bytrec - CLNT__SMALLBUF;     /* rest of bytes in 2nd buffer*/

  /* + + + + + + + + + + + + + + */
  /* + + + read 2nd buffer + + + */
  /* + + + + + + + + + + + + + + */
  if (i_debug == 2) {
    short  j;
    int*  pl;
    printf("D-%s: begin of c_buffer[148] in LW (all hex)\n", c_modnam);
    pl = (int*) &p_clntbuf->c_buffer[148];
    for (j=0; j<5; j++) {
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;

      printf("\n");
    }
    printf("D-%s: **Rd 2nd Buf: at %8x (buf[%d]) to %8x = %d b\n",
           c_modnam,
           (int)(char*) &p_clntbuf->c_buffer[CLNT__RESTBUF],
           CLNT__RESTBUF,
           (int)(((char*) &p_clntbuf->c_buffer[CLNT__RESTBUF]) + (l_2ndbuf_byt - 1)),
           l_2ndbuf_byt);
  }
  *p_bytrd += l_2ndbuf_byt;
  l_buftord = 2;
  /* check if buffer if big enough, reallocate if not */
  /* old buffer is freed by caller */
  if(l_bytrec > l_maxbytes) {
    im=l_bytrec;
    l_bytrec=(int)(1.2*(float)l_bytrec);
    l_bytrec=((l_bytrec>>12)+1);
    l_bytrec=(l_bytrec<<12);
    /*      printf("reallocate for %d (%d) bytes\n",im,l_bytrec);fflush(stdout);*/
    pc =  (char*) malloc(l_bytrec);
    pl_d=(int*)pc;
    for(ii=0; ii<l_bytrec/4; ii++) { *pl_d++ = 0; }
    pl_d=(int*)pc;
    pl_s=(int*)ps_chan->pc_io_buf;
    for(ii=0; ii<CLNT__SMALLBUF/4; ii++) { *pl_d++ = *pl_s++; }
    ps_chan->pc_io_buf = pc;
    ps_chan->l_io_buf_size = l_bytrec;
    p_clntbuf = (struct s_clntbuf*) pc;
  }
  pl = (int*) &p_clntbuf->c_buffer[CLNT__RESTBUF];
  im=l_2ndbuf_byt/16384;
  l_2ndbuf_byt=l_2ndbuf_byt%16384;
  for(ii=0; ii<im; ii++) {
    l_status = f_stc_read( pl,16384,i_chan,l_timeout);
    pl+=4096;
    if(l_status != STC__SUCCESS) { break; }
  }
  if(l_2ndbuf_byt > 0) {
    l_status = f_stc_read( pl,l_2ndbuf_byt,i_chan,l_timeout);
  }
  if (l_status != STC__SUCCESS) {
    printf("E-%s: Error reading second buffer. Msg follows:",c_modnam);
    f_stc_disperror(l_status,c_retmsg, 0);
    return(FALSE);
  }

  if (i_debug == 2) {
    short  j;
    int*  pl;
    printf("D-%s: begin of c_buffer[148] in LW (all hex)\n", c_modnam);
    pl = (int*) &p_clntbuf->c_buffer[148];
    for (j=0; j<5; j++) {
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;
      printf("%8x:%8x ",(int)pl,*(pl));
      pl++;

      printf("\n");
    }
  }

m_snd_ackn:;                             /* +++ set and send 12 bytes ackn */
  /* ++++++++++++++++++++++++++++++++++ */
  /* + + + send acknowledge buffer + + + */
  /* ++++++++++++++++++++++++++++++++++ */
  s_ackn.l_ack_buf   = l_buftord;
  s_ackn.l_ack_bytes = *p_bytrd;
  s_ackn.l_clnt_sts  = 1;                    /* success                      */

  if ((l_buffertype & 8) != 0) {
    s_ackn.l_clnt_sts = s_ackn.l_clnt_sts | 8;  /* set bit for last buffer  */
  }

  return(TRUE);
}


/*2+F_SEND_ACKN*****+**************************************************/
/*                                                                    */
/*+ Module      : F_SEND_ACKN                                         */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_send_ackn(l_clnt_sts, i_chan)               */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Send acknowledge buffer to the server                */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+   l_clnt_sts: Status. Status bits will be set in addition to the  */
/*                status  bits set by f_read_server in s_ackn struct. */
/*+    i_chan   : (int) channel number                                */
/*                                                                    */
/*+ FUNCTION    : Send the acknowledge buffer. Set additional bits in  */
/*                the status word, i.e. "last buffer" etc.            */
/*                                                                    */
/*+ Return type : int (32 bit)                                       */
/*+ Status codes: 1: success                                          */
/*                0: fault                                            */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 11-Apr-1994                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
int        f_send_ackn(l_clnt_sts, i_chan)
int             l_clnt_sts;
int              i_chan;
{
  /* ++++ declarations ++++ */
  int            l_status;                              /* !!! */
  static char    c_modnam[] = "f_send_ackn";
  char           c_retmsg[256];

  if (i_debug == 2)
    printf("I-%s s_ackn.l_clnt_sts:%d l_clnt_sts:%d\n",
           c_modnam,
           s_ackn.l_clnt_sts,
           l_clnt_sts);

  /* +++++++++++++++++++++++++++++++ */
  /* +++ set status of ackn buf  +++ */
  /* +++++++++++++++++++++++++++++++ */
  s_ackn.l_clnt_sts  = s_ackn.l_clnt_sts | l_clnt_sts; /* success            */

  /* ++++++++++++++++++++++++++++++ */
  /* +++ send acknowledge buffer +++ */
  /* ++++++++++++++++++++++++++++++ */
  l_status = f_stc_write( (char*) &s_ackn,
                          12,
                          i_chan);

  if (l_status != STC__SUCCESS) {
    printf("E-%s: Error in f_stc_write(&s_ackn,...)! Msg follows:",
           c_modnam);
    f_stc_disperror(l_status,c_retmsg, 0);
    return(FALSE);
  }

  return(TRUE);
}


/*2+F_STRTOUPPER***+***************************************************/
/*                                                                    */
/*+ Module      : F_STRTOUPPER                                        */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_strtoupper(u, l)                            */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Converts a '\0' terminated string to upper case.    */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+    u        : Pointer to upper case string (result)               */
/*+    l        : Pointer to lower case string (argument)             */
/*                                                                    */
/*+ FUNCTION    : Converts a '\0' terminated string to upper case.    */
/*                                                                    */
/*+ Return type : int (32 bit)                                       */
/*+ Status codes: -                                                   */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
void f_strtoupper(u, l)
char* u, *l;
{
  for ( ; *l != '\0'; ++l, ++u) {
    *u = (char)toupper((int)*l);
  }

  *u = '\0';
  return;
}


/*2+F_CLNUP ***+*******************************************************/
/*                                                                    */
/*+ Module      : F_CLNUP                                             */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_clnup(v_mem, p_keyb)                              */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Cleanup allocated memory and dealloc devices        */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+    v_mem[]  : (int) [0]:maxidx=n [1:n]:ptr to allocated memory   */
/*+    p_keyb   : Pointer to s_keyb or NULL.                          */
/*                                                                    */
/*+ FUNCTION    : Cleanup allocated memory and dealloc devices        */
/*                Calls free(v_mem[i]) and f_ttydass(p_keyb)          */
/*                                                                    */
/*                                                                    */
/*+ Return type : void                                                */
/*+ Status codes: -                                                   */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 14-JUN-1993                                         */
/*+ Object libr.: GOOSHRLIB                                           */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*-               14-Jan-94 : prototype TTYSTUFF(f_ttydass()) (RSM)   */
/*-               08-Apr-94 : Accept NULL pointer for p_keyb. /HE     */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void f_clnup(v_mem, p_keyb)
long v_mem[];
int* p_keyb;
/* cleanup: free allocated memory and dealloc allocated device(s) */
{
  /* ++++ declaration ++++ */
//  static char     c_modnam[] = "f_clnup";
  short    i;
//  int     l_status;

  for (i = 1; i <= v_mem[0]; i++) {
    /*    printf("free %d of %d: %8x",i,v_mem[0],v_mem[i]);fflush(stdout);*/
    if(v_mem[i] != 0) { free((int*) v_mem[i]); }
    /*     printf(" done\n");fflush(stdout);*/
    v_mem[i]=0;
  }
  v_mem[0]=0;
}
/*******************************************************************/
void f_clnup_save(v_mem, p_keyb)
long v_mem[];
int* p_keyb;
/* cleanup: free allocated memory and dealloc allocated device(s) */
{
  /* ++++ declaration ++++ */
//  static char     c_modnam[] = "f_clnup";
//  short    i;
//  int     l_status;

  /*  printf("all  %d:",v_mem[0]);fflush(stdout);*/
  v_mem[++v_mem[0]] = (long) p_keyb; /* was (int) before JA */

  /*  printf("  %d: %8x\n",v_mem[0],(int)p_keyb);fflush(stdout);*/
}
/* ------------------------------------------------------------------------- */
