/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*****************  f_evt.h ******************************/
#ifndef F_EVT
#define F_EVT

#include "typedefs.h"

/* ++++++++++++++++ include UNIX standard headers +++++++++++++++++++++++++ */

#if MBS_ENDIAN == 1
#include "s_bufhe.h"
#include "s_evhe.h"
#include "s_ve10_1.h"
#include "s_ves10_1.h"
#else
#include "s_bufhe_swap.h"
#include "s_evhe_swap.h"
#include "s_ve10_1_swap.h"
#include "s_ves10_1_swap.h"
#endif

#define MAX_BUF_LGTH 32768
#define MIN_BUF_LGTH 512
#define MAX_BUFS_IN_STREAM 100 /* at a maximum, 100 buffers per stream */
#define MAX_LONG 99999999      /* maximum long data */

typedef struct
{
    INTS4 l_endian;
    INTS4 l_version;
    INTS4 l_bufsize;
    INTS4 l_buffers;
    INTS4 l_events;
    INTS4 l_filesize;
    INTS4 l_first;
    INTS4 l_last;
    INTS4 l_linear;
} s_taghe;

typedef struct
{
    INTS4 l_event;
    INTS4 l_offset;
} s_tag;

struct sLmdControl;

typedef struct
{
    INTS4 l_server_type; /* number specifying input source */
    INTS4 l_buf_type;    /* buffer type number               */
    INTS4 l_buf_subtype; /* buffer subtype number            */
    INTS4 l_channel_no;  /* file descripter or server No.    */
    INTS4 l_buf_size;    /* buffer size                      */
    INTS4 l_buf_no;
    INTS4 l_buf_posi;
    INTS4 l_buf_lmt;
    INTS4 l_bufs_in_stream; /* # of buffers per stream          */
    INTS4 l_stream_bufs;
    INTS4 l_io_buf_size; /* I/O buffer size=l_buf_size*l_bufs_in_stream */
    INTS4 l_io_buf_posi;
    INTS4 l_evt_buf_size; /* internal buffer size             */
    INTS4 l_evt_buf_posi;
    INTS4 l_evt_size;
    INTS4 l_timeout; /* -1 (default) no timeout */
    INTS4 l_events;  /* events since open             */
    INTS4 l_buffers; /* buffers since open             */
    INTS4 l_kbytes;  /* kbytes since open             */
    INTS4 l_first_get;
    INTS4 l_first_put;
    INTS4 l_first_buf;
    INTS4 l_frag_len;
    CHARS* pc_io_buf;  /* pointer to I/O buffer to server  */
    CHARS* pc_evt_buf; /* pointer to internal event buffer */
    s_bufhe* ps_bufhe;
    s_bufhe s_bufhe_1; /* keep buffer header of 1st buffer for spanned event */
    s_ve10_1* ps_ve10_1;
    CHARS c_channel[128]; /* channel name */
    INTS4 l_tagfile_no;   /* file descripter or server No.    */
    INTS4 l_tagswap;
    INTS4 l_lmdswap;
    s_taghe* ps_taghe;
    s_tag* ps_tag;
    sLmdControl* pLmd;
} s_evt_channel;

INTS4 f_evt_cre_tagfile(CHARS*, CHARS*, INTS4 (*)());
INTS4 f_evt_get_tagopen(s_evt_channel*, CHARS*, CHARS*, CHARS**, INTS4);
INTS4 f_evt_get_tagevent(s_evt_channel*, INTS4, INTS4, INTS4**);
INTS4 f_evt_get_tagnext(s_evt_channel*, INTS4, INTS4**);
INTS4 f_evt_get_tagclose(s_evt_channel*);
INTS4 f_evt_get_open(INTS4, CHARS*, s_evt_channel*, CHARS**, INTS4, INTS4);
INTS4 f_evt_get_event(s_evt_channel*, INTS4**, INTS4**);
INTS4 f_evt_get_subevent(s_ve10_1*, INTS4, INTS4**, INTS4**, INTS4*);
INTS4 f_evt_get_buffer(s_evt_channel*, INTS4*);
INTS4 f_evt_get_close(s_evt_channel*);
CHARS* f_evt_get_buffer_ptr(s_evt_channel*);
INTS4 f_evt_skip_buffer(s_evt_channel*, INTS4);
INTS4 f_evt_put_open(CHARS*, INTS4, INTS4, INTS4, INTS4, s_evt_channel*, CHARS*);
INTS4 f_evt_put_event(s_evt_channel*, INTS4*);
INTS4 f_evt_put_buffer(s_evt_channel*, s_bufhe*);
INTS4 f_evt_put_close(s_evt_channel*);
INTS4 f_evt_type(s_bufhe*, s_evhe*, INTS4, INTS4, INTS4, INTS4);
INTS4 f_evt_error(INTS4, CHARS*, INTS4);
INTS4 f_evt_timeout(s_evt_channel*, INTS4);
INTS4 f_evt_rev_port(INTS4);
INTS4 f_evt_swap(CHARS*, INTS4);
s_evt_channel* f_evt_control();

/* ******************************/
/*  Input selector              */
/* ******************************/
#define GETEVT__FILE 1
#define GETEVT__STREAM 2
#define GETEVT__TRANS 3
#define GETEVT__EVENT 4
#define GETEVT__REVSERV 5
#define GETEVT__RFIO 6
#define GETEVT__TAGINDEX 10
#define GETEVT__TAGNUMBER 11
/* ********************************************************************** */
/*                   error messages                                       */
/* ********************************************************************** */
#define GETEVT__SUCCESS 0
#define GETEVT__FAILURE 1
#define GETEVT__FRAGMENT 2
#define GETEVT__NOMORE 3
#define GETEVT__NOFILE 4
#define GETEVT__NOSERVER 5
#define GETEVT__RDERR 6
#define GETEVT__CLOSE_ERR 7
#define GETEVT__NOCHANNEL 8
#define GETEVT__TIMEOUT 9
#define GETEVT__NOTAGFILE 10
#define GETEVT__NOTAG 11
#define GETEVT__TAGRDERR 12
#define GETEVT__TAGWRERR 13
#define GETEVT__NOLMDFILE 14

#define PUTEVT__SUCCESS 0
#define PUTEVT__FILE_EXIST 101
#define PUTEVT__FAILURE 102
#define PUTEVT__TOOBIG 103
#define PUTEVT__TOO_SMALLS 104
#define PUTEVT__CLOSE_ERR 105
#define PUTEVT__WRERR 106
#define PUTEVT__NOCHANNEL 107

#endif
/*****************  End f_evt.h ******************************/
