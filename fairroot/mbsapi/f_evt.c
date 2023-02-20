/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "f_stccomm.h"
#include "typedefs.h"

#ifdef RFIO
#define RFIO_open rfio_open
#define RFIO_close rfio_close
#define RFIO_read rfio_read
#define RFIO_lseek rfio_lseek
#include "rawapin.h" /* RFIO stuff */
#else
#define RFIO_open open
#define RFIO_close close
#define RFIO_read read
#define RFIO_lseek lseek
#endif

#ifdef GSI__LYNX
#undef unix
#endif

#ifdef GSI__LINUX /* Linux */
#undef unix
#endif

#ifdef GSI__SOLARIS /* Solaris */
#undef unix
#endif

#ifdef GSI__WINNT /* Windows NT */
#endif

#ifdef GSI__AIX
#define AIX_DEC
#endif

#ifdef unix /* DEC OSF/1 */
#define AIX_DEC
#endif

#ifdef GSI__WINNT
#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>
#define DEF_FILE_ACCE S_IREAD | S_IWRITE /* rw */
#define GET__OPEN_FLAG O_RDONLY | O_BINARY
#define PUT__OPEN_APD_FLAG O_RDWR | O_APPEND
#define PUT__CRT_FLAG O_CREAT | O_RDWR
#define PUT__CRT_OPT ""

#include <winsock.h>
#define WS_VERSION_REQD 0x0101
#define WS_VERSION_MAJOR HIBYTE(WS_VERSION_REQD)
#define WS_VERSION_MINOR LOBYTE(WS_VERSION_REQD)
#define MIN_SOCKETS_REQD 6
// WSADATA    wsaData;
#endif

#ifdef Linux /* Linux */
#include <fcntl.h>
#include <memory.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <unistd.h>
#define DEF_FILE_ACCE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH /* rw-r--r-- */
#define GET__OPEN_FLAG O_RDONLY
#define PUT__OPEN_APD_FLAG O_RDWR | O_APPEND
#define PUT__CRT_FLAG O_CREAT | O_RDWR
#define PUT__CRT_OPT ""
#endif

#ifdef Solaris /* Linux */
#include <fcntl.h>
#include <memory.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <unistd.h>
#define DEF_FILE_ACCE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH /* rw-r--r-- */
#define GET__OPEN_FLAG O_RDONLY
#define PUT__OPEN_APD_FLAG O_RDWR | O_APPEND
#define PUT__CRT_FLAG O_CREAT | O_RDWR
#define PUT__CRT_OPT ""
#endif

#ifdef Darwin /* MaxOS X */
#include <fcntl.h>
#include <memory.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <unistd.h>
#define DEF_FILE_ACCE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH /* rw-r--r-- */
#define GET__OPEN_FLAG O_RDONLY
#define PUT__OPEN_APD_FLAG O_RDWR | O_APPEND
#define PUT__CRT_FLAG O_CREAT | O_RDWR
#define PUT__CRT_OPT ""
#endif

#ifdef _AIX
#include <fcntl.h>
#include <memory.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mode.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <unistd.h>
#define DEF_FILE_ACCE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH /* rw-r--r-- */
#define GET__OPEN_FLAG O_RDONLY
#define PUT__OPEN_APD_FLAG O_RDWR | O_APPEND
#define PUT__CRT_FLAG O_CREAT | O_RDWR
#define PUT__CRT_OPT ""
#endif

#if MBS_ENDIAN == 1
#include "s_filhe_swap.h"
#else
#include "s_filhe.h"
#endif

// DABC
#include "fLmd.h"
// -- DABC

//#include "gps_sc_def.h"
#include "f_evt.h"
//#include "f_evcli.h"
#include "portnum_def.h"

INTS4 f_evt_get_newbuf(s_evt_channel*);
INTS4 f_evt_check_buf(CHARS*, INTS4*, INTS4*, INTS4*, INTS4*);
INTS4 f_evt_ini_bufhe(s_evt_channel* ps_chan);
INTS4 f_evt_swap_filhe(s_bufhe*);
INTS4 f_ut_utime(INTS4, INTS4, CHARS*);

static struct s_tcpcomm s_tcpcomm_st_evt;
static CHARS c_temp[MAX_BUF_LGTH];
static int l_gl_rev_port = PORT__EVENT_SERV;
// static int l_gl_evt_check = 0;

/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_evt__example                                  */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : Examples for calling event API */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : See f_evt_examples.c                    */
/*                                                                    */
/*                                                             */
/*2+Implementation************+****************************************/
/*+ User Example : In m_lea_user.c                                    */
/*+ Channel structure : defined in f_evt.h                            */
/*+ File name   : f_evt.c                                             */
/*+ Version     : 1.01                                                */
/*+ Author      : H.Essel                                             */
/*+ Created     : 16-Feb-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*1- C Procedure *************+****************************************/

/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 52                                                */
/*   D-64220 Darmstadt                                               */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_evt_get_subevent                                  */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_sts = f_evt_get_subevent(ve10_1 *,subevent,**head,**data,*lwords) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : get subevent pointer                                */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   ve10_1    : (s_ve10_1 *) event header pointer                   */
/*+  subevent   : subevent number (1,2,3...)                          */
/*                If = 0, f_evt_get_subevent returns the number of    */
/*                subevents. In this case the following arguments     */
/*                might be NULL.                                      */
/*+   head      : Address of s_ves10_1 subevent header pointer        */
/*+   data      : Address of INTS4 event data pointer                 */
/*+   lwords    : Address of INTS4 to get number of data longwords    */
/*                                                                    */
/*+ Return type : int                                                 */
/*-               GETEVT__SUCCESS   : Found subevent.                 */
/*-               GETEVT__NOMORE    : No more subevents.              */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_subevent( */
/*                   s_ve10_1 *, INTS4, INTS4 **, INTS4 **, INTS4 *); */
/*1- C Procedure *************+****************************************/
INTS4 f_evt_get_subevent(s_ve10_1* ps_ve10_1, INTS4 l_subevent, INTS4** pl_se, INTS4** pl_d, INTS4* pl_lwords)
{
    s_ves10_1* ps_ves10_1;
    INTS4 l_total, l_sub, l_sum;
    INTS4 /*l,*/ ll, /*l_status,*/ *pl_next;

    if (ps_ve10_1 == NULL) {
        return (GETEVT__FAILURE);
    }
    pl_next = (INTS4*)(ps_ve10_1 + 1);
    l_total = ps_ve10_1->l_dlen - 4; /* total words in subevents */
    l_sum = 0;
    ll = 0;
    while (l_sum < l_total) {
        ps_ves10_1 = (s_ves10_1*)pl_next;
        ll++;
        if (ll == l_subevent) {
            if (pl_lwords != NULL) {
                *pl_lwords = ps_ves10_1->l_dlen / 2 - 1;
            }
            if (pl_se != NULL) {
                *pl_se = (INTS4*)ps_ves10_1;
            }
            if (pl_d != NULL) {
                *pl_d = (INTS4*)(ps_ves10_1 + 1);
            }
            return (GETEVT__SUCCESS);
        }
        l_sub = ps_ves10_1->l_dlen + 4; /* total words of subevent */
        l_sum += l_sub;
        pl_next = (INTS4*)(ps_ves10_1);
        pl_next += l_sub / 2;
    }
    if (pl_lwords != NULL) {
        *pl_lwords = ll;
    }
    if (pl_se != NULL) {
        *pl_se = NULL;
    }
    if (pl_d != NULL) {
        *pl_d = NULL;
    }
    if (l_subevent == 0) {
        return (ll);
    } else {
        return (GETEVT__NOMORE);
    }
}
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 52                                                */
/*   D-64220 Darmstadt                                               */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_evt_type                                          */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status = f_evt_type(bufhe,evhe,sid,long,hex,data) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : print event                                         */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   bufhe     : (s_bufhe *) buffer header pointer (=NULL no output) */
/*+   evhe      : (s_evhe *) event header pointer (=NULL no output)   */
/*+    sid      :  subevent ID (-1 is all)                            */
/*+   long      :  output longwords                                   */
/*+   hex       :  output hex longwords                               */
/*+   data      :  output data                                        */
/*                                                                    */
/*+ Return type : int                                                 */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_type( */
/*                      s_bufhe *,s_evhe *, INTS4, INTS4, INTS4, INTS4); */
/*1- C Procedure *************+****************************************/
INTS4 f_evt_type(s_bufhe* ps_bufhe, s_evhe* ps_evhe, INTS4 l_subid, INTS4 l_long, INTS4 l_hex, INTS4 l_data)
{
    s_ves10_1* ps_ves10_1;
    s_ve10_1* ps_ve10_1;
    s_filhe* ps_filhe;
    //  INTS2*     pi_data;
    INTS4* pl_data;
    INTS4 /*l_mode,*/ l_s;
    INTS4 l, ll, l_status, l_ldata, l_used;
    CHARS c_line[132];
    CHARS c_full[132];
    CHARS c_time[32];

    strcpy(c_full, "  ");
    l_ldata = l_data;
    if ((l_hex + l_long) > 0) {
        l_ldata = 1;
    }

    /* Print buffer header (file header) */
    if (ps_bufhe != NULL) {
        sprintf(c_line, "--------------------------------------------------------");
        printf("%s\n", c_line);
        /* calculate real buffer size */
        ll = ps_bufhe->l_dlen * 2;
        if (ll % 512 > 0) {
            ll += 512 - ll % 512;
        }
        /* file header */
        l_status = f_ut_utime(ps_bufhe->l_time[0], ps_bufhe->l_time[1], c_time);

#ifdef VMS
        if (1 != l_status)
            printf("f_evt_type: error in f_ut_utime!");
#else
        if (0 != l_status)
            printf("f_evt_type: error in f_ut_utime!");
#endif

        if (ps_bufhe->i_type == 2000) {
            ps_filhe = (s_filhe*)ps_bufhe;
            sprintf(c_line, "File header info:");
            printf("%s\n", c_line);
            sprintf(c_line, "Size:    %d [%d b], used %d [b]", ps_filhe->filhe_dlen, ll, ps_filhe->filhe_used * 2);
            printf("%s\n", c_line);
            sprintf(c_line, "Label:   %s", ps_filhe->filhe_label);
            printf("%s\n", c_line);
            sprintf(c_line, "File:    %s", ps_filhe->filhe_file);
            printf("%s\n", c_line);
            sprintf(c_line, "User:    %s", ps_filhe->filhe_user);
            printf("%s\n", c_line);
            sprintf(c_line, "Time:    %s", ps_filhe->filhe_time);
            printf("%s\n", c_line);
            sprintf(c_line, "Run:     %s", ps_filhe->filhe_run);
            printf("%s\n", c_line);
            sprintf(c_line, "Exp:     %s", ps_filhe->filhe_exp);
            printf("%s\n", c_line);
            for (ll = 0; ll < ps_filhe->filhe_lines; ll++) {
                sprintf(c_line, "comment: %s", ps_filhe->s_strings[ll].string);
                printf("%s\n", c_line);
            }
        } else {
            l_used = ps_bufhe->i_used;
            if (ps_bufhe->l_dlen > MAX__DLEN) {
                l_used = ps_bufhe->l_free[2];
            }
            sprintf(c_line,
                    "Buffer  %9d, Length %5d[w] Size %5d[b] used %5d[w] %s",
                    ps_bufhe->l_buf,
                    ps_bufhe->l_dlen,
                    ll,
                    l_used,
                    c_time);
            printf("%s\n", c_line);
            sprintf(c_line,
                    "       Events %3d Type/Subtype %5d %5d FragEnd=%d FragBegin=%d Total %5d[w]",
                    ps_bufhe->l_evt,
                    ps_bufhe->i_type,
                    ps_bufhe->i_subtype,
                    ps_bufhe->h_end,
                    ps_bufhe->h_begin,
                    ps_bufhe->l_free[1]);
            printf("%s\n", c_line);
        }
        sprintf(c_line, "--------------------------------------------------------");
        printf("%s\n", c_line);
    }

    if (ps_evhe == NULL) {
        return (0);
    }

    /* print event 4,x or 6,x */
    if (ps_evhe->i_type != 10) {
        sprintf(c_line,
                "Event type %d, subtype %d, data longwords %d",
                ps_evhe->i_type,
                ps_evhe->i_subtype,
                ps_evhe->l_dlen / 2);
        printf("%s\n", c_line);
        if ((l_ldata != 0) & ((ps_evhe->i_type == 4) | (ps_evhe->i_type == 6))) {
            /* output data, assume data as longword */
            pl_data = (INTS4*)ps_evhe;
            pl_data += 2;
            for (l = 0; l < ps_evhe->l_dlen / 2; l++) {
                sprintf(c_line, "%08x ", *pl_data);
                strcat(c_full, c_line);
                pl_data++;
                if (l % 8 == 7) {
                    printf("%s\n", c_full);
                    strcpy(c_full, "  ");
                }
            }
            if (strlen(c_full) > 2) {
                printf("%s\n", c_full);
            }
        }
        return (0);
    }

    /* Print event 10,1 */
    ps_ve10_1 = (s_ve10_1*)ps_evhe;
    /* Print event header */
    sprintf(c_line,
            "Event   %9d Type/Subtype %5d %5d Length %5d[w] Trigger %2d",
            ps_ve10_1->l_count,
            ps_ve10_1->i_type,
            ps_ve10_1->i_subtype,
            ps_ve10_1->l_dlen,
            ps_ve10_1->i_trigger);
    printf("%s\n", c_line);

    /********************/
    l_s = 0;
    l_status = 0;
    while (l_status == 0) {
        l_s++;
        l_status = f_evt_get_subevent(ps_ve10_1, l_s, (INTS4**)&ps_ves10_1, (INTS4**)&pl_data, (INTS4*)&ll);
        if (l_status == 0) {
            if ((l_subid < 0) | (l_subid == ps_ves10_1->i_procid)) {
                sprintf(c_line,
                        "  SubEv ID %6d Type/Subtype %5d %5d Length %5d[w] Control %2d Subcrate %2d",
                        ps_ves10_1->i_procid,
                        ps_ves10_1->i_type,
                        ps_ves10_1->i_subtype,
                        ps_ves10_1->l_dlen,
                        ps_ves10_1->h_control,
                        ps_ves10_1->h_subcrate);
                printf("%s\n", c_line);
                if (l_ldata != 0) {
                    /* output data  */
                    if ((l_long != 0) | (l_hex != 0)) {
                        /* In this case we assume data as one longword per channel */
                        for (l = 0; l < ll; l++) {
                            if (l_hex != 0) {
                                sprintf(c_line, "%04x.%04x ", (*pl_data >> 16) & 0xffff, *pl_data & 0xffff);
                            } else {
                                sprintf(c_line, "%8d ", *pl_data);
                            }
                            strcat(c_full, c_line);
                            pl_data++;
                            if (l % 8 == 7) {
                                printf("%s\n", c_full);
                                strcpy(c_full, "  ");
                            }
                        }
                        if (strlen(c_full) > 2) {
                            printf("%s\n", c_full);
                        }
                        strcpy(c_full, "  ");
                    } else {
                        /* In this case we assume data as two words per channel */
                        for (l = 0; l < ll; l++) {
                            sprintf(c_line, "%8d%8d", *pl_data & 0xffff, (*pl_data >> 16) & 0xffff);
                            strcat(c_full, c_line);
                            pl_data++;
                            if (l % 4 == 3) {
                                printf("%s\n", c_full);
                                strcpy(c_full, "  ");
                            }
                        }
                        if (strlen(c_full) > 2) {
                            printf("%s\n", c_full);
                        }
                        strcpy(c_full, "  ");
                    }
                }
            }
        }
    }
    return (0);
}
/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_rev_port                                      */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_rev_port(long l_port)                         */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_rev_port sets port number for event server    */
/*+ ARGUMENTS   :                                                     */
/*+   l_port    : Port number:                                        */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_rev_port(INTS4); */
/*1- C Main ****************+******************************************/
INTS4 f_evt_rev_port(INTS4 l_port)
{
    l_gl_rev_port = l_port;
    printf("Use remote event server port %d\n", l_port);
    return 0;
}
/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_open                                      */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_open(long l_mode, char &c_server[], s_evt_channel &s_chan, */
/*                               char **ps_info, long l_sample,l_para)*/
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_open  opens an event stream from specified*/
/*                channel.                                            */
/*+ ARGUMENTS   :                                                     */
/*+   l_mode    : Type of server:                                     */
/*-               GETEVT__FILE   : Input from file                    */
/*-               GETEVT__STREAM : Input from MBS stream server       */
/*-               GETEVT__TRANS  : Input from MBS transport           */
/*-               GETEVT__EVENT  : Input from MBS event server        */
/*-               GETEVT__REVSERV: Input from remote event server     */
/*+   c_server  : Node of server or file name.                        */
/*+   s_chan    : structure s_evt_channel, must be allocated.         */
/*+   ps_info   : address of pointer. If it is not NULL, then         */
/*                try to return file header or other information      */
/*                about server. If it is NULL, then returns nothing.  */
/*+   l_sample  : used by event server to send only every             */
/*                'l_sample' event.                                   */
/*+   l_para    : currently not used                                  */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__NOFILE    : file does not exist.            */
/*-               GETEVT__RDERR     : read server error.              */
/*-               GETEVT__NOSERVER  : can not connect server.         */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_open( */
/*                INTS4, CHARS *, s_evt_channel *, CHARS **, INTS4, INTS4); */
/*+ FUNCTION    : Opens the input channel and save context in s_chan. */
/*+ NOTE        : Up to four input channels can be opened.            */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_open(INTS4 l_mode,
                     CHARS* pc_server,
                     s_evt_channel* ps_chan,
                     CHARS** ps_info,
                     INTS4 l_sample,
                     INTS4 l_param)
{

    INTS4 l_swap, l_swap_head, l_is_goosybuf, l_filehead = 0, l_size, l_size_head, l_dummy, l_header_size;
    //  INTS2* pi;
    CHARS c_file[256], *pc_temp;
    s_filhe* ps_filhe;
    struct s_varstr
    {
        INTS2 i_varstr;
        CHARS c_varstr[128];
    } /* s_varstr_file*/;
    INTS4 l_status;   //,ll;
    int val;

    // P.-A. Loizeau, 2015/11/26:
    //    In case of STREAM mode, catch the case where the user provided
    //    a nonstandard stream port, extract the value and clean the server
    //    name. Usefull with DABC MBS streams where the port can be user set.
    INTS4 i_streamport = PORT__STREAM_SERV;
    if ((GETEVT__STREAM == l_mode) && ((pc_temp = strchr(pc_server, ':')) != NULL)) {
        //      printf("input string: %s!\n", pc_server);
        pc_server = strtok(pc_server, ":");
        CHARS* pc_streamport = strtok(NULL, ":");

        i_streamport = atoi(pc_streamport);
        //      printf("output string: %s! Port: %s %i\n", pc_server, pc_streamport, i_streamport);
    }

#ifndef GSI__WINNT
    // disable automatic detection of RFIO on Windows while file name can contain ":"
    if ((pc_temp = strchr(pc_server, ':')) != NULL) {
        l_mode = GETEVT__RFIO;
        /*       printf("rfio file %s\n",pc_server);*/
    }
#endif

#ifndef RFIO
    if (l_mode == GETEVT__RFIO) {
        printf("rfio not supported!\n");
        return (GETEVT__NOFILE);
    }
#endif

    if (ps_info != NULL) {
        *ps_info = NULL;
    }
    // when timeout is already set by f_evt_timeout(), do not overwrite
    if (ps_chan->l_timeout == 0) {
        ps_chan->l_timeout = -1;
    } /* no timeout */

    if (strlen(pc_server) < sizeof(ps_chan->c_channel)) {   // length of pc_server < 128
        strncpy(ps_chan->c_channel, pc_server, sizeof(ps_chan->c_channel) - 1);
    } else {
        printf("file name to long!\n");
        return (GETEVT__NOFILE);
    }

    switch (l_mode) {
        case GETEVT__FILE:

            if (strlen(pc_server) < sizeof(c_file)) {   // length of pc_server < 256
                strncpy(c_file, pc_server, sizeof(c_file) - 1);
            } else {
                printf("file name to long!\n");
                return (GETEVT__NOFILE);
            }

            if (strlen(c_file) < 5) {
                strcat(c_file, ".lmd");
            } else {
                pc_temp = (CHARS*)&c_file[strlen(c_file) - 4];
                if ((strcmp(pc_temp, ".LMD") != 0) && (strcmp(pc_temp, ".lmd") != 0)) {
                    strcat(c_file, ".lmd");
                }
            }

            if ((ps_chan->l_channel_no = open(c_file, GET__OPEN_FLAG)) == -1) {
                return (GETEVT__NOFILE);
            }
            /* read first 512 bytes */
            if (read(ps_chan->l_channel_no, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
                printf("LMD format error: no LMD file: %s\n", c_file);
                close(ps_chan->l_channel_no);
                ps_chan->l_channel_no = -1;
                return (GETEVT__NOLMDFILE);
            }
            // DABC
            ps_chan->pLmd = NULL;
            if ((*((INTS4*)(c_temp + 4)) == LMD__TYPE_FILE_HEADER_101_1) || (*((INTS4*)(c_temp + 4)) == 0x65000100)) {
                close(ps_chan->l_channel_no);
                ps_chan->pLmd = fLmdAllocateControl();
                fLmdGetOpen(ps_chan->pLmd, c_file, NULL, LMD__BUFFER, LMD__NO_INDEX);
                ps_chan->l_server_type = l_mode;
                return GETEVT__SUCCESS;
            }
            // -- DABC
            /* check for file header, return size and swap */
            f_evt_check_buf(c_temp, &l_size_head, &l_is_goosybuf, &l_swap_head, &l_filehead);
            if (((l_is_goosybuf == 0) & (l_filehead == 0)) | (l_size_head == 0)) {
                printf("LMD format error: swap=%d, header=%d, isLMD=%d, size=%d\n",
                       l_swap_head,
                       l_filehead,
                       l_is_goosybuf,
                       l_size_head);
                close(ps_chan->l_channel_no);
                ps_chan->l_channel_no = -1;
                return (GETEVT__NOLMDFILE);
            }

            /* read file header and first buffer and check for goosy header */
            if (l_filehead == 1) {
                val = lseek(ps_chan->l_channel_no, 0, SEEK_SET); /* rewind file */
                if (-1 == val) {
                    return (GETEVT__FAILURE);
                }
                l_header_size = l_size_head;
                if (((s_filhe*)c_temp)->filhe_dlen > MAX__DLEN) {
                    l_header_size = ((s_filhe*)c_temp)->filhe_used * 2 + 48;
                    //  printf("Large buffer, read short header %d bytes\n",l_header_size);
                }
                if (read(ps_chan->l_channel_no, c_temp, l_header_size) != l_header_size) {
                    printf("LMD format error: no LMD file: %s\n", c_file);
                    close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
                if (read(ps_chan->l_channel_no, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
                    close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__RDERR);
                }
                f_evt_check_buf(c_temp, &l_size, &l_is_goosybuf, &l_swap, &l_dummy);
                if ((l_is_goosybuf == 0) | (l_size != l_size_head) | (l_swap != l_swap_head)) {
                    printf("LMD format error: swap=%d, isLMD=%d, size=%d\n", l_swap, l_is_goosybuf, l_size);
                    close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
            } /* check buffer behind header */
            ps_chan->l_buf_size = l_size_head;
            val = lseek(ps_chan->l_channel_no, 0, SEEK_SET); /* rewind file */
            if (-1 == val) {
                return (GETEVT__FAILURE);
            }
            if (ps_info != NULL) {
                *ps_info = NULL;
            }
            /* found file header */
            if (l_filehead == 1) {
                if (read(ps_chan->l_channel_no, c_temp, l_header_size) != l_header_size) {
                    printf("LMD format error: no LMD file: %s\n", c_file);
                    close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
                ps_filhe = (s_filhe*)c_temp;
                if (ps_info != NULL) { /* if user want file header be returned */
                    if (l_swap_head == 1) {
                        f_evt_swap_filhe((s_bufhe*)ps_filhe);
                    }
                    *ps_info = c_temp; /* now , get file header and return */
                }
                /*
      printf("type %d, subtype %d\n",ps_filhe->filhe_type,ps_filhe->filhe_subtype);
      printf("strings %d %d %d %d %d %x\n",
      ps_filhe->filhe_label_l,
      ps_filhe->filhe_file_l,
      ps_filhe->filhe_user_l,
      ps_filhe->filhe_run_l,
      ps_filhe->filhe_exp_l,
      ps_filhe->filhe_lines);
      pi=(INTS2 *)&ps_filhe->s_strings;
      for(l_dummy=0;l_dummy<ps_filhe->filhe_lines;l_dummy++)
      {
        printf("comment %d, %s\n",*pi,(c_temp+366+l_dummy*80));
        pi += 40;
      }
      */
            } /* file header */

            /* points to a real buffer start */
            /* and read header buffer, if there */
            ps_chan->l_io_buf_size = ps_chan->l_buf_size;
            /* may larger, but must multiplexed */
            break;
        case GETEVT__STREAM:
            /* initialize connection with stream server                  */
            // P.-A. Loizeau, 2015/11/26:
            //    In case of STREAM mode, catch the case where the user provided
            //    a nonstandard stream port, extract the value and clean the server
            //    name. Usefull with DABC MBS streams where the port can be user set.
            //    if(f_stc_connectserver(pc_server,PORT__STREAM_SERV,&ps_chan->l_channel_no,
            if (f_stc_connectserver(pc_server, i_streamport, &ps_chan->l_channel_no, &s_tcpcomm_st_evt)
                != STC__SUCCESS) {
                return (GETEVT__NOSERVER);
            }

            l_status = f_stc_read(c_temp, 16, ps_chan->l_channel_no, ps_chan->l_timeout);
            if (l_status == STC__TIMEOUT) {
                return (GETEVT__TIMEOUT);
            }
            if (l_status != STC__SUCCESS) {
                return (GETEVT__RDERR);
            }

            if (*((INTS4*)(c_temp)) != 1) {
                f_evt_swap(c_temp, 16);
            }
            ps_chan->l_buf_size = *((INTS4*)(c_temp + 4)); /* buffer size */
            ps_chan->l_bufs_in_stream = *((INTS4*)(c_temp + 8));
            /* # buffers per stream */
            ps_chan->l_stream_bufs = 0; /* counter */

            ps_chan->l_io_buf_size = (ps_chan->l_buf_size) * (ps_chan->l_bufs_in_stream);
            // DABC
            ps_chan->pLmd = NULL;
            if (*((INTS4*)(c_temp + 12)) == 0) {
                ps_chan->pLmd = fLmdAllocateControl();
                ps_chan->pLmd->pTCP = &s_tcpcomm_st_evt;
                fLmdInitMbs(ps_chan->pLmd,
                            pc_server,
                            ps_chan->l_buf_size,
                            ps_chan->l_bufs_in_stream,
                            0,
                            PORT__STREAM_SERV,
                            ps_chan->l_timeout);
                printf("f_evt_get_open for STREAM: setting timeout=%d  n", ps_chan->l_timeout);

                ps_chan->l_server_type = l_mode;
                return GETEVT__SUCCESS;
            }
            // -- DABC
            break;
        case GETEVT__TRANS:
            /* initialize connection with stream server                  */
            if (f_stc_connectserver(pc_server, PORT__TRANSPORT, &ps_chan->l_channel_no, &s_tcpcomm_st_evt)
                != STC__SUCCESS) {
                return (GETEVT__NOSERVER);
            }

            l_status = f_stc_read(c_temp, 16, ps_chan->l_channel_no, ps_chan->l_timeout);
            if (l_status == STC__TIMEOUT) {
                return (GETEVT__TIMEOUT);
            }
            if (l_status != STC__SUCCESS) {
                return (GETEVT__RDERR);
            }

            if (*((INTS4*)(c_temp)) != 1) {
                f_evt_swap(c_temp, 16);
            }
            ps_chan->l_buf_size = *((INTS4*)(c_temp + 4)); /* buffer size */
            ps_chan->l_bufs_in_stream = *((INTS4*)(c_temp + 8));
            /* # buffers per stream */
            ps_chan->l_io_buf_size = ps_chan->l_buf_size;
            // DABC
            ps_chan->pLmd = NULL;
            if (*((INTS4*)(c_temp + 12)) == 0) {
                ps_chan->pLmd = fLmdAllocateControl();
                ps_chan->pLmd->pTCP = &s_tcpcomm_st_evt;
                fLmdInitMbs(ps_chan->pLmd,
                            pc_server,
                            ps_chan->l_buf_size,
                            ps_chan->l_bufs_in_stream,
                            0,
                            PORT__TRANSPORT,
                            ps_chan->l_timeout);
                ps_chan->l_server_type = l_mode;
                return GETEVT__SUCCESS;
            }
            // -- DABC
            break;
        case GETEVT__REVSERV:
            //    if(f_evcli_con(ps_chan, pc_server, l_gl_rev_port, -1, l_sample)!=STC__SUCCESS) {
            //      return(GETEVT__NOSERVER);
            //    }
            break;
        case GETEVT__EVENT:
            //    if(f_evcli_con(ps_chan, pc_server, l_gl_rev_port, -1, l_sample)!=STC__SUCCESS) {
            //      return(GETEVT__NOSERVER);
            //    }
            break;
#ifdef RFIO
        case GETEVT__RFIO:
            ps_chan->l_channel_no = -1;
            ps_chan->l_channel_no = RFIO_open(pc_server, GET__OPEN_FLAG, 0);
            if (ps_chan->l_channel_no < 0) {
                return (GETEVT__NOSERVER);
            }
            /* read first 512 bytes */
            if (RFIO_read(ps_chan->l_channel_no, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
                printf("LMD format error: no LMD file: %s\n", pc_server);
                RFIO_close(ps_chan->l_channel_no);
                ps_chan->l_channel_no = -1;
                return (GETEVT__NOLMDFILE);
            }
            /* check for file header, return size and swap */
            f_evt_check_buf(c_temp, &l_size_head, &l_is_goosybuf, &l_swap_head, &l_filehead);
            if (((l_is_goosybuf == 0) & (l_filehead == 0)) | (l_size_head == 0)) {
                printf("LMD format error: swap=%d, header=%d, isLMD=%d, size=%d\n",
                       l_swap_head,
                       l_filehead,
                       l_is_goosybuf,
                       l_size_head);
                RFIO_close(ps_chan->l_channel_no);
                ps_chan->l_channel_no = -1;
                return (GETEVT__NOLMDFILE);
            }
            /* read file header and first buffer and check for goosy header */
            if (l_filehead == 1) {
                val = RFIO_lseek(ps_chan->l_channel_no, 0, SEEK_SET); /* rewind file */
                if (-1 == val) {
                    return (GETEVT__FAILURE);
                }
                if (RFIO_read(ps_chan->l_channel_no, c_temp, l_size_head) != l_size_head) {
                    printf("LMD format error: no LMD file: %s\n", pc_server);
                    RFIO_close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
                if (RFIO_read(ps_chan->l_channel_no, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
                    RFIO_close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__RDERR);
                }
                f_evt_check_buf(c_temp, &l_size, &l_is_goosybuf, &l_swap, &l_dummy);
                if ((l_is_goosybuf == 0) | (l_size != l_size_head) | (l_swap != l_swap_head)) {
                    printf("LMD format error: swap=%d, isLMD=%d, size=%d\n", l_swap, l_is_goosybuf, l_size);
                    RFIO_close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
            } /* check buffer behind header */
            ps_chan->l_buf_size = l_size_head;
            val = RFIO_lseek(ps_chan->l_channel_no, 0, SEEK_SET); /* rewind file */
            if (-1 == val) {
                return (GETEVT__FAILURE);
            }
            if (ps_info != NULL) {
                *ps_info = NULL;
            }
            /* found file header */
            if (l_filehead == 1) {
                if (RFIO_read(ps_chan->l_channel_no, c_temp, l_size_head) != l_size_head) {
                    printf("LMD format error: no LMD file: %s\n", pc_server);
                    RFIO_close(ps_chan->l_channel_no);
                    ps_chan->l_channel_no = -1;
                    return (GETEVT__NOLMDFILE);
                }
                ps_filhe = (s_filhe*)c_temp;
                if (ps_info != NULL) { /* if user want file header be returned */
                    if (l_swap_head == 1) {
                        f_evt_swap_filhe((s_bufhe*)ps_filhe);
                    }
                    *ps_info = c_temp; /* now , get file header and return */
                }
                /*
      printf("type %d, subtype %d\n",ps_filhe->filhe_type,ps_filhe->filhe_subtype);
      printf("strings %d %d %d %d %d %x\n",
      ps_filhe->filhe_label_l,
      ps_filhe->filhe_file_l,
      ps_filhe->filhe_user_l,
      ps_filhe->filhe_run_l,
      ps_filhe->filhe_exp_l,
      ps_filhe->filhe_lines);
      pi=(INTS2 *)&ps_filhe->s_strings;
      for(l_dummy=0;l_dummy<ps_filhe->filhe_lines;l_dummy++)
      {
        printf("comment %d, %s\n",*pi,(c_temp+366+l_dummy*80));
        pi += 40;
      }
      */
            } /* file header */
            ps_chan->l_io_buf_size = ps_chan->l_buf_size;
            break;
#endif
        default:
            if (ps_info != NULL) {
                *ps_info = NULL;
            }
            return (GETEVT__NOSERVER);
    } /* end of switch */

    if ((l_mode != GETEVT__EVENT) & (l_mode != GETEVT__REVSERV)) {
        if ((ps_chan->pc_io_buf = malloc(ps_chan->l_io_buf_size)) == NULL) {
            printf("Memory allocation error\n");
            exit(2);
        }
        ps_chan->l_evt_buf_size = ps_chan->l_io_buf_size;
        if ((ps_chan->pc_evt_buf = malloc(ps_chan->l_evt_buf_size)) == NULL) {
            printf("Memory allocation error\n");
            exit(2);
        }
    } /* l_mode != GETEVT__EVENT */
    ps_chan->l_server_type = l_mode;
    ps_chan->l_first_get = 1; /* so we will first call f_getvet_get */
    return GETEVT__SUCCESS;
} /* end of f_evt_get_open */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_event                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_event(s_evt_channel &s_chan, long **ppl_buffer, long **ppl_goobuf) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_event  returnes address of event          */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : Input channel from open.                            */
/*+   ppl_buffer: Address of pointer. Returns address of event.       */
/*+   ppl_goobuf: Address of pointer. Returns address of buffer.      */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__FRAGMENT  : Event fragment found.           */
/*-               GETEVT__NOMORE    : No more events.                 */
/*-               GETEVT__RDERR     : read server or file error       */
/*-               GETEVT__TIMEOUT   : when enabled by f_evt_timeout   */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_event(  */
/*                     s_evt_channel *, INTS4 **, INTS4 **); */
/*+ FUNCTION    : Get next event and returnes pointer. The pointer    */
/*                may point to the event in the buffer or internal    */
/*                event buffer (spanned events). The content of the   */
/*                pointer may be destroyed by next call.              */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_event(s_evt_channel* ps_chan, INTS4** ppl_buffer, INTS4** ppl_goobuf)
{
    INTS4 l_temp, l_prev_ok = 1, l_stat = LMD__SUCCESS, l_used;
    s_bufhe* ps_bufhe_cur;
    //  s_ve10_1* ps_ve10_1;
    sMbsHeader* pevt;

    // DABC
    if (ps_chan->pLmd != NULL) {
        if (ps_chan->l_server_type == GETEVT__TRANS) {
            l_stat = fLmdGetMbsEvent(ps_chan->pLmd, &pevt);
        } else if (ps_chan->l_server_type == GETEVT__STREAM) {
            l_stat = fLmdGetMbsEvent(ps_chan->pLmd, &pevt);
        } else if (ps_chan->l_server_type == GETEVT__FILE) {
            l_stat = fLmdGetElement(ps_chan->pLmd, LMD__NO_INDEX, &pevt);
        } else {
            pevt = NULL;
        }

        // any error, then pointer is null
        if (pevt == NULL) {
            if (ps_chan->l_server_type == GETEVT__FILE) {
                if (l_stat == GETLMD__NOMORE) {
                    return (GETEVT__NOMORE);
                }
                if (l_stat == GETLMD__EOFILE) {
                    return (GETEVT__NOMORE);
                }
                if (l_stat == GETLMD__NOBUFFER) {
                    return (GETEVT__FAILURE);
                }
                return (GETEVT__RDERR);
            } else {
                if (l_stat == LMD__TIMEOUT) {
                    return (GETEVT__TIMEOUT);
                } else {
                    return (GETEVT__RDERR);
                }
            }
        }
        // OK
        if (ppl_goobuf) {
            *ppl_goobuf = NULL;
        }
        *ppl_buffer = (INTS4*)pevt;
        return (GETEVT__SUCCESS);
    }
    // -- DABC
    //  if((ps_chan->l_server_type == GETEVT__EVENT)|(ps_chan->l_server_type == GETEVT__REVSERV)) {
    //    *ppl_goobuf = NULL;
    //    if(f_evcli_evt(ps_chan) != STC__SUCCESS) { /* no more event, get new buffer */
    //      l_stat=f_evcli_buf(ps_chan);
    //      if(l_stat == STC__TIMEOUT) { return(GETEVT__TIMEOUT); }
    //      if(l_stat != STC__SUCCESS) { return(GETEVT__FAILURE); }
    //    }
    //    *ppl_buffer = (INTS4*) ps_chan->pc_evt_buf;
    //    return(GETEVT__SUCCESS);
    //  }

    /* e.g. read_buffer is 16384, GOOSY buffer may be only 2048,   *
     * this ps_chan->l_io_buf_posi indicats when the read_buffer is finished */

    if (ps_chan->l_first_get == 1) {
        ps_chan->l_buf_posi = 0;           /* goosy buffer position */
        ps_chan->l_buf_lmt = 0;            /* end of this goosy buffer */
        ps_chan->l_io_buf_posi = MAX_LONG; /* Iuput buffer(for read file) position */
        ps_chan->l_first_buf = 1;          /* boolean */
        ps_chan->l_first_get = 0;          /* boolean */
    }
    /* why we need this part codes? beacause we may (open, get, close) *
     * and (open, get, close) again!!! Especially when we use m-histo  *
     * so the second or later (open,get,close) should reset these      *
     * static value                                                    */

    ps_chan->l_evt_buf_posi = 0;
    /* above, internal event buffer position, internal buffer will be returned */

    while (1) {
        /* if previous goosy buffer has finished, read a new buffer from i/o buffer,
      or from file if i/o buffer is all readout */
        while (ps_chan->l_buf_posi >= ps_chan->l_buf_lmt) {
            /* if this i/o buffer is read to end */
            /* end of this read_buffer which may contain several GOOSY buffers*/
            if (ps_chan->l_io_buf_posi >= ps_chan->l_io_buf_size) {
                if ((l_temp = f_evt_get_newbuf(ps_chan)) != GETEVT__SUCCESS) {
                    return (l_temp);
                }
                ps_chan->l_io_buf_posi = 0;
            } /* end of real read server */
            ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + ps_chan->l_io_buf_posi);
            l_prev_ok = (ps_chan->l_buf_no == (ps_chan->ps_bufhe->l_buf - 1));
            ps_chan->l_buf_no = ps_chan->ps_bufhe->l_buf;
            if (ps_chan->ps_bufhe->i_type == 2000) { /* file header */
                printf("Unsolicited file header found!\n");
                ps_chan->l_io_buf_posi += ps_chan->l_buf_size;
                ps_chan->l_buf_posi = ps_chan->l_io_buf_posi;
                ps_chan->l_buf_lmt = ps_chan->l_io_buf_posi;
            } else {
                l_used = ps_chan->ps_bufhe->l_free[2];   // large buffers HE, Oct 2007
                if (ps_chan->ps_bufhe->l_dlen <= MAX__DLEN) {
                    l_used = ps_chan->ps_bufhe->i_used;
                }
                ps_chan->l_buf_posi = ps_chan->l_io_buf_posi + sizeof(s_bufhe);
                ps_chan->l_buf_lmt = ps_chan->l_buf_posi + l_used * 2;
                ps_chan->l_io_buf_posi += ps_chan->l_buf_size;
            }
        } /* end of read file while loop */

        /* now, ps_chan->l_buf_posi points to start of an event or spanned event */
        ps_chan->ps_ve10_1 = (s_ve10_1*)(ps_chan->pc_io_buf + ps_chan->l_buf_posi);
        if ((ps_chan->l_evt_buf_posi != 0)
            || ((ps_chan->ps_bufhe->h_end == 1)
                && (ps_chan->l_first_buf == 1))) { /* if this is a spanned part of an event */
            ps_chan->l_buf_posi += sizeof(s_evhe);
            ps_chan->l_frag_len = ps_chan->ps_ve10_1->l_dlen * 2;
        } else { /* if this is a real start of an event */
            ps_chan->l_frag_len = (ps_chan->ps_ve10_1->l_dlen - 4) * 2 + sizeof(s_ve10_1);
        }

        if (ps_chan->l_frag_len + ps_chan->l_buf_posi > ps_chan->l_buf_lmt) {
            return (GETEVT__FRAGMENT);
        }

        /* if ps_chan->l_buf_posi is not start of an event and ps_chan->l_first_buf =1  *
         * then skip to next event                                   */
        if ((ps_chan->ps_bufhe->h_end == 1) && ((ps_chan->l_first_buf == 1) || (l_prev_ok == 0))) {
            /* if the first buffer is spanned at begin, then skip */
            ps_chan->l_first_buf = 0;    /* 24-Apr-1996 */
            l_prev_ok = 1;               /* 2001 HE */
            ps_chan->l_evt_buf_posi = 0; /* 2001 HE stuff in event buffer obsolete */
            ps_chan->l_buf_posi += ps_chan->l_frag_len;
            /* now,ps_chan->l_buf_posi points to start of an event or spanned event */
            continue; /* continue "while" loop */
        }

        ps_chan->l_first_buf = 0;

        /* if ps_chan->l_buf_posi is start of an event and the event is not *
         * spanned, then return pointer                           */
        if ((ps_chan->l_evt_buf_posi == 0)
            && ((ps_chan->ps_bufhe->h_begin == 0)
                || ((ps_chan->l_buf_posi + ps_chan->l_frag_len) < ps_chan->l_buf_lmt))) {
            *ppl_buffer = (INTS4*)(ps_chan->pc_io_buf + ps_chan->l_buf_posi);
            ps_chan->l_buf_posi += ps_chan->l_frag_len;
            ps_chan->l_evt_buf_posi = 0;
            if (ppl_goobuf) {
                *ppl_goobuf = (INTS4*)(ps_chan->ps_bufhe);
            }
            return (GETEVT__SUCCESS);
        }

        /* 2001 HE if we start a spanned event, save buffer header of first buffer */
        if (ps_chan->l_evt_buf_posi == 0) {
            memcpy((CHARS*)&ps_chan->s_bufhe_1, (CHARS*)ps_chan->ps_bufhe, sizeof(s_bufhe));
            ps_bufhe_cur = (s_bufhe*)&ps_chan->s_bufhe_1;
        }
        /* copy the part of this event which in this buffer into     *
         * internal buffer, data will be moved by realloc  function  */
        if (ps_chan->l_evt_buf_size < ps_chan->l_evt_buf_posi + ps_chan->l_frag_len) {
            ps_chan->l_evt_buf_size = ps_chan->l_evt_buf_posi + ps_chan->l_frag_len;
            if ((ps_chan->pc_evt_buf = realloc(ps_chan->pc_evt_buf, ps_chan->l_evt_buf_size)) == NULL) {
                printf("Memory allocation error\n");
                exit(2);
            }
        }
        memcpy(ps_chan->pc_evt_buf + ps_chan->l_evt_buf_posi,
               ps_chan->pc_io_buf + ps_chan->l_buf_posi,
               ps_chan->l_frag_len);
        ps_chan->l_buf_posi += ps_chan->l_frag_len;
        if (ps_chan->l_evt_buf_posi == 0) {}
        ps_chan->l_evt_buf_posi += ps_chan->l_frag_len;

        if ((ps_chan->ps_bufhe->h_begin != 1) || (ps_chan->l_buf_posi < ps_chan->l_buf_lmt)) {
            /* change event header's l_dlen */
            ((s_ve10_1*)(ps_chan->pc_evt_buf))->l_dlen = ps_chan->l_evt_buf_posi / 2 - 4;
            *ppl_buffer = (INTS4*)(ps_chan->pc_evt_buf);
            if (ppl_goobuf) {
                *ppl_goobuf = (INTS4*)(ps_bufhe_cur);
            }
            return (GETEVT__SUCCESS);
        }
    } /* if this event spanned to next buffer, then loop */
} /* end of f_evt_get_event */

/*1+ C Main ******************+****************************************/
/*+ Module      : f_evt_get_close                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_close( s_evt_channel &s_chan)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_close  closes event stream of specified   */
/*                channel.                                            */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : Input channel from open.                            */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__CLOSE_ERR : close server or file error      */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_close(s_evt_channel *);  */
/*+ FUNCTION    : Closes the specified input channel.                 */
/*1- C Main ******************+****************************************/
INTS4 f_evt_get_close(s_evt_channel* ps_chan)
{
    INTS4 l_close_failure;
    //  INTS4 l_status;

    // DABC
    if (ps_chan->pLmd != NULL) {
        if (ps_chan->l_server_type == GETEVT__TRANS) {
            fLmdCloseMbs(ps_chan->pLmd);
        } else if (ps_chan->l_server_type == GETEVT__STREAM) {
            fLmdCloseMbs(ps_chan->pLmd);
        } else if (ps_chan->l_server_type == GETEVT__FILE) {
            fLmdGetClose(ps_chan->pLmd);
        }
        free(ps_chan->pLmd);
        ps_chan->pLmd = NULL;
        return GETEVT__SUCCESS;
    }
    // -- DABC
    l_close_failure = 0;
    if (ps_chan->l_channel_no >= 0) {
        switch (ps_chan->l_server_type) {
            case GETEVT__FILE:
                if (close(ps_chan->l_channel_no) == -1) {
                    l_close_failure = 1;
                }
                if (ps_chan->pc_io_buf != NULL) {
                    free(ps_chan->pc_io_buf);
                }
                if (ps_chan->pc_evt_buf != NULL) {
                    free(ps_chan->pc_evt_buf);
                }
                break;
            case GETEVT__STREAM:
                /* disconnect with stream server                              */
                f_stc_write("CLOSE", 6, ps_chan->l_channel_no);
                if (f_stc_discclient(ps_chan->l_channel_no) != STC__SUCCESS) {
                    l_close_failure = 1;
                }
                if (f_stc_close(&s_tcpcomm_st_evt) != STC__SUCCESS) {
                    l_close_failure = 1;
                }
                if (ps_chan->pc_io_buf != NULL) {
                    free(ps_chan->pc_io_buf);
                }
                if (ps_chan->pc_evt_buf != NULL) {
                    free(ps_chan->pc_evt_buf);
                }
                break;
            case GETEVT__TRANS:
                /* disconnect with stream server                              */
                if (f_stc_discclient(ps_chan->l_channel_no) != STC__SUCCESS) {
                    l_close_failure = 1;
                }
                if (f_stc_close(&s_tcpcomm_st_evt) != STC__SUCCESS) {
                    l_close_failure = 1;
                }
                if (ps_chan->pc_io_buf != NULL) {
                    free(ps_chan->pc_io_buf);
                }
                if (ps_chan->pc_evt_buf != NULL) {
                    free(ps_chan->pc_evt_buf);
                }
                break;
            case GETEVT__REVSERV:
            case GETEVT__EVENT:
                //      if(f_evcli_close(ps_chan)!=STC__SUCCESS) { l_close_failure=1; }
                break;
            case GETEVT__RFIO:
                RFIO_close(ps_chan->l_channel_no);
                ps_chan->l_channel_no = -1;
                if (ps_chan->pc_io_buf != NULL) {
                    free(ps_chan->pc_io_buf);
                }
                if (ps_chan->pc_evt_buf != NULL) {
                    free(ps_chan->pc_evt_buf);
                }
                break;
            default:
                l_close_failure = 1;
        } /* end of switch */
        ps_chan->pc_io_buf = NULL;
        ps_chan->l_channel_no = -1;
        if (l_close_failure == 1) {
            return (GETEVT__CLOSE_ERR);
        }
        return GETEVT__SUCCESS;
    }
    return GETEVT__SUCCESS;

} /* end of f_evt_get_close */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_put_open                                      */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_put_open(char *c_file[], long l_size, long l_stream, long l_type, */
/*                         long l_subtype, s_evt_channel *ps_chan, char *ps_filhe) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_put_open  opens an event output stream.       */
/*+ ARGUMENTS   :                                                     */
/*+  c_file     : Name of file.                                       */
/*+  l_size     : Size of output buffers in bytes.                    */
/*+  l_stream   : Number of buffers with spanning events.             */
/*+  l_type     : Buffer type number                                  */
/*+  l_subtype  : Buffer subtype number                               */
/*+  ps_chan    : Address of channel structure which will be returned.*/
/*+  ps_filhe   : Address of user specified file header               */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               PUTEVT__SUCCESS   : success.                        */
/*-               PUTEVT__FILE_EXIST: file already exists.            */
/*-               PUTEVT__FAILURE   : failure.                        */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_put_open(  */
/*                 CHARS *,INTS4,INTS4,INTS4,INTS4,s_evt_channel *,CHARS *); */
/*+ FUNCTION    : Opens the output channel and save context in        */
/*                s_evt_channel structure.                            */
/*+ NOTE        : Up to four output channels can be opened.           */
/* User Example : In m_lea_user.c                                     */
/*1- C Main ****************+******************************************/
INTS4 f_evt_put_open(CHARS* pc_file,
                     INTS4 l_size,
                     INTS4 l_stream,
                     INTS4 l_type,
                     INTS4 l_subtype,
                     s_evt_channel* ps_chan,
                     CHARS* ps_filhe)
{
    s_filhe* ps_file_head;
    INTS4 l_write_size;
    INTS4 l_status;   //,ll;
    time_t s_timet;
    struct timeb s_timeb;
    /* because "timeb" is not "typedef", so we must use "struct" */
    CHARS c_mode[80];
    CHARS c_file[256], *pc_temp;
    struct s_varstr
    {
        INTS2 i_varstr;
        CHARS c_varstr[128];
    } /* s_varstr_file*/;

    // DABC
    ps_chan->pLmd = NULL;
    if (l_stream == 0) {
        ps_chan->pLmd = fLmdAllocateControl();
        l_status = fLmdPutOpen(ps_chan->pLmd, pc_file, NULL, l_size, LMD__NO_OVERWRITE, LMD__INDEX, LMD__LARGE_FILE);
        return (l_status);
    }
    // -- DABC

    ps_chan->l_first_put = 1;

    ps_chan->l_buf_size = l_size;
    ps_chan->l_bufs_in_stream = l_stream;
    ps_chan->l_buf_type = l_type;
    ps_chan->l_buf_subtype = l_subtype;
    ps_chan->l_io_buf_size = ps_chan->l_buf_size * ps_chan->l_bufs_in_stream;
    if ((ps_chan->pc_io_buf = malloc(ps_chan->l_io_buf_size)) == NULL) {
        printf("Memory allocation error\n");
        exit(2);
    }

    snprintf(c_file, sizeof(c_file), "%s", pc_file);
    if (strlen(c_file) < 5) {
        strcat(c_file, ".lmd");
    } else {
        pc_temp = (CHARS*)&c_file[strlen(c_file) - 4];
        if ((strcmp(pc_temp, ".LMD") != 0) && (strcmp(pc_temp, ".lmd") != 0)) {
            strcat(c_file, ".lmd");
        }
    }
    if ((ps_chan->l_channel_no = open(c_file, PUT__OPEN_APD_FLAG)) != -1) {
        return (PUTEVT__FILE_EXIST);
    } else {
        if ((ps_chan->l_channel_no = open(c_file, PUT__CRT_FLAG, DEF_FILE_ACCE)) == -1) {
            return (PUTEVT__FAILURE);
        }
        /* open OK */
        else {
            /* output file header */
            ps_file_head = (s_filhe*)ps_chan->pc_io_buf;
            /* if user specify file header */
            if (ps_filhe != NULL) {
                memcpy(ps_file_head, ps_filhe, ps_chan->l_buf_size);
            } else {
                memset(ps_file_head, '\0', ps_chan->l_buf_size);
                sprintf(ps_file_head->filhe_run, "Pid %d", getpid());
                ps_file_head->filhe_run_l = strlen(ps_file_head->filhe_run);
            }
            ps_file_head->filhe_dlen = ps_chan->l_buf_size / 2;
            ps_file_head->filhe_subtype = 1;
            ps_file_head->filhe_type = 2000;
            ftime(&s_timeb);
            ps_file_head->filhe_stime[0] = (INTS4)s_timeb.time;
            ps_file_head->filhe_stime[1] = (INTS4)s_timeb.millitm;
            ps_file_head->filhe_free[0] = 1;
            ps_file_head->filhe_file_l = strlen(c_file); /* not include \0 */
            strcpy(ps_file_head->filhe_file, c_file);
            char* username = getenv("USER");
            if (username) {
                snprintf(ps_file_head->filhe_user, sizeof(ps_file_head->filhe_user), "%s", username);
            }
            ps_file_head->filhe_user_l = strlen(ps_file_head->filhe_user);

            /* get calendar time
       The returned string from ctime is of the format
       Www Mmm dd hh:mm:ss yyyy
       The string is followed by a new-line character ('\n') and terminated with a null-character.
       The strinh has a length of 25 characters
      */
            time(&s_timet);
            char* temptime = ctime(&s_timet);

            if (strlen(temptime) < sizeof(c_mode)) {
                strncpy(c_mode, temptime, sizeof(c_mode) - 1);
            } else {
                return (PUTEVT__FAILURE);
            }

            if (strlen(&c_mode[4]) < sizeof(ps_file_head->filhe_time)) {
                strncpy(ps_file_head->filhe_time, &c_mode[4], sizeof(ps_file_head->filhe_time) - 1);
            } else {
                return (PUTEVT__FAILURE);
            }

            // Remove the terminating new-line character
            ps_file_head->filhe_time[20] = ' ';
            l_write_size = write(ps_chan->l_channel_no, (CHARS*)ps_file_head, ps_chan->l_buf_size);
            if (l_write_size == -1) {
                return (PUTEVT__WRERR);
            }
            if (l_write_size != ps_chan->l_buf_size) {
                return (PUTEVT__TOOBIG);
            }
            return (PUTEVT__SUCCESS);
        }
    }
} /* end of f_evt_put_open */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_put_event                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_put_event(s_evt_channel *ps_chan, long &la_evt_buf[]) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_put_event outputs event                       */
/*+ ARGUMENTS   :                                                     */
/*+  ps_chan    : Address of channel structure as returned from       */
/*                f_evt_put_open.                                     */
/*+  la_evt_buf  : event data array. Standard GSI event structure.    */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               PUTEVT__SUCCESS   : success.                        */
/*-               PUTEVT__WRERR     : read server or file error       */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_put_event(s_evt_channel *, INTS4 *); */
/*+ FUNCTION    : Copies current event into output buffer. Writes     */
/*                buffer to file, when full.                          */
/*1- C Main ****************+******************************************/

INTS4 f_evt_put_event(s_evt_channel* ps_chan, INTS4* pl_evt_buf)
{
    INTS4 l_evt_buf_posi;
    INTS4 l_buf_remain_size; /* net free space of I/O buffer       */
    INTS4 l_write_size, l_temp, l_free;
    INTS4 l_status;
    CHARS* pc_addr;
    s_bufhe* ps_bufhe;

    // DABC
    if (ps_chan->pLmd != NULL) {
        l_status = fLmdPutElement(ps_chan->pLmd, (sMbsHeader*)pl_evt_buf);
        return (l_status);
    }
    // -- DABC
    if (ps_chan->l_first_put == 1) {
        ps_chan->l_first_put = 0;
        ps_chan->l_io_buf_posi = 0;
        ps_chan->l_buf_no = 1;
    }
    l_evt_buf_posi = 0;
    ps_chan->l_evt_size = (((s_ve10_1*)(pl_evt_buf))->l_dlen) * 2 + sizeof(s_evhe);

    /* get l_buf_remain_size is available size in stream */
    l_buf_remain_size = ps_chan->l_io_buf_size - ps_chan->l_io_buf_posi;
    l_temp = (l_buf_remain_size / ps_chan->l_buf_size) * (sizeof(s_bufhe) + sizeof(s_evhe));
    l_buf_remain_size -= l_temp; /* minus space occupied by buffer header and spanned event header */

    if (ps_chan->l_evt_size > l_buf_remain_size) { /* output this i/o buffer    */
        memset(ps_chan->pc_io_buf + ps_chan->l_io_buf_posi, '\0', ps_chan->l_io_buf_size - ps_chan->l_io_buf_posi);
        /* clear rest of this GOOSY buffer */
        l_temp = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size) * ps_chan->l_buf_size;
        if (ps_chan->l_io_buf_posi % ps_chan->l_buf_size == 0) {
            l_temp -= ps_chan->l_buf_size;
        }
        /* l_temp points to start of last GOOSY buf in i/o buf area  */
        ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + l_temp);
        if (l_temp == 0) {
            ps_chan->ps_bufhe->h_end = 0;
        } /* first buf in stream, no end */
        else {
            ps_chan->ps_bufhe->h_end = ((s_bufhe*)((CHARS*)ps_chan->ps_bufhe - ps_chan->l_buf_size))->h_begin;
        }
        ps_chan->ps_bufhe->h_begin = 0; /* evt has end, so not spanned to next buf */
        for (l_temp = 0; l_temp < ps_chan->l_io_buf_size; l_temp += ps_chan->l_buf_size) {
            pc_addr = ps_chan->pc_io_buf + l_temp;
            ps_bufhe = (s_bufhe*)pc_addr;
            if (ps_bufhe->l_evt > 0) { /* do not write empty buffers */
                l_write_size = write(ps_chan->l_channel_no, pc_addr, ps_chan->l_buf_size);
                if (l_write_size == -1) {
                    return (PUTEVT__WRERR);
                }
                if (l_write_size != ps_chan->l_buf_size) {
                    return (PUTEVT__TOOBIG);
                }
            } else {
                ps_chan->l_buf_no--;
            } /* decrement buffer number for not written buffer */
        }     /* buffer output loop */
        ps_chan->l_io_buf_posi = 0;
        ps_chan->ps_bufhe = (s_bufhe*)ps_chan->pc_io_buf;
        /* get l_buf_remain_size of new stream */
        l_buf_remain_size = ps_chan->l_io_buf_size;
        l_temp = (l_buf_remain_size / ps_chan->l_buf_size) * (sizeof(s_bufhe) + sizeof(s_evhe));
        l_buf_remain_size -= l_temp;         /* minus space occupied by buf header and spanned event header */
        l_buf_remain_size += sizeof(s_evhe); /* 1st buf always no span */
        /* if event can not fit in a new stream, then error */
        if (ps_chan->l_evt_size > l_buf_remain_size) {
            return (PUTEVT__TOO_SMALLS);
        }
    }

    if (ps_chan->l_io_buf_posi == 0) {
        f_evt_ini_bufhe(ps_chan);
    } /* init all buffer headers */

    /* write event into i/o buf till end of event, change ps_chan->l_io_buf_posi   */
    while (l_evt_buf_posi < ps_chan->l_evt_size) {
        ps_chan->ps_ve10_1 = (s_ve10_1*)(ps_chan->pc_io_buf + ps_chan->l_io_buf_posi);
        if ((ps_chan->l_io_buf_posi % ps_chan->l_buf_size) == 0) {
            ps_chan->l_io_buf_posi += sizeof(s_bufhe);
            ps_chan->ps_ve10_1 = (s_ve10_1*)(ps_chan->pc_io_buf + ps_chan->l_io_buf_posi); /* behind header */
            if (l_evt_buf_posi != 0) {
                ps_chan->l_io_buf_posi += sizeof(s_evhe); /* behind element header */
                l_write_size = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size) * ps_chan->l_buf_size;
                /* l_write_size points to start of this GOOSY buf in i/o buf area  */
                ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + l_write_size);
                ps_chan->ps_bufhe->i_used += sizeof(s_evhe) / 2;
            }
        }
        l_write_size = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size) * ps_chan->l_buf_size;
        /* l_write_size points to start of this GOOSY buf in i/o buf area  */
        ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + l_write_size);
        l_write_size = l_write_size + ps_chan->l_buf_size - ps_chan->l_io_buf_posi;
        /* l_write_size is remain free space in this GOOSY buf */
        if (l_write_size > (ps_chan->l_evt_size - l_evt_buf_posi)) {
            l_write_size = (ps_chan->l_evt_size - l_evt_buf_posi);
        }
        memcpy(ps_chan->pc_io_buf + ps_chan->l_io_buf_posi, (CHARS*)pl_evt_buf + l_evt_buf_posi, l_write_size);
        ps_chan->ps_bufhe->l_evt++; /* number of fragments */
        ps_chan->l_io_buf_posi += l_write_size;
        l_evt_buf_posi += l_write_size;
        ps_chan->ps_bufhe->i_used += l_write_size / 2;
        /* if the remain free space of GOOSY buffer does not large enough  *
         * to hold even a event header, then turn to next GOOSY buffer and *
         * fill buffer header. or 8 long words aligned ????????            */
        l_free = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size) * ps_chan->l_buf_size;
        /* l_free points to start of this GOOSY buf in i/o buf area  */
        l_free = l_free + ps_chan->l_buf_size - ps_chan->l_io_buf_posi;
        if (l_free == ps_chan->l_buf_size) {
            l_free = 0;
        }
        /* l_free is remain free space in this GOOSY buf */
        if (l_free < sizeof(s_ve10_1)) {
            ps_chan->l_io_buf_posi += l_free;
        }
        /* change spanned evt header l_dlen */
        if (l_evt_buf_posi != l_write_size) {
            ps_chan->ps_ve10_1->l_dlen = l_write_size / 2;
            ps_chan->ps_ve10_1->i_subtype = ps_chan->l_buf_subtype;
            ps_chan->ps_ve10_1->i_type = ps_chan->l_buf_type;
        } else {
            ps_chan->ps_ve10_1->l_dlen = (l_write_size - sizeof(s_evhe)) / 2;
        } /* header of first frag */
        if ((ps_chan->l_io_buf_posi % ps_chan->l_buf_size) == 0) {
            if (l_evt_buf_posi < ps_chan->l_evt_size) {
                ps_chan->ps_bufhe->h_begin = 1;
            }
            if (ps_chan->l_io_buf_posi > ps_chan->l_buf_size) { /* so first buf in stream */
                ps_chan->ps_bufhe->h_end = ((s_bufhe*)((CHARS*)ps_chan->ps_bufhe - ps_chan->l_buf_size))->h_begin;
            }
            ps_chan->ps_bufhe->l_free[1] = ((s_ve10_1*)(pl_evt_buf))->l_dlen; /* lgth of last event in buf */
        } /* end of processs prev buffer head and ... */

    } /* end of write event into i/o buf till end of event */
    return (PUTEVT__SUCCESS);
} /* end of f_evt_put_event */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_put_buffer                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_put_buffer(s_evt_channel *ps_chan, s_bufhe *ps_bufhe) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_put_buffer outputs buffer                     */
/*+ ARGUMENTS   :                                                     */
/*+  ps_chan    : Address of channel structure as returned from       */
/*                f_evt_put_open.                                     */
/*+  ps_bufhe   : Buffer.                                             */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               PUTEVT__SUCCESS   : success.                        */
/*-               PUTEVT__WRERR     : read server or file error       */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_put_buffer(s_evt_channel *, s_bufhe *); */
/*+ FUNCTION    : Writes buffer to file.                              */
/*1- C Main ****************+******************************************/

INTS4 f_evt_put_buffer(s_evt_channel* ps_chan, s_bufhe* ps_bufhe)
{
    INTS4 l_write_size;   //, l_temp, l_free;
    INTS4 l_status;
    //  CHARS* pc_addr;

    // DABC
    if (ps_chan->pLmd != NULL) {
        l_status = fLmdPutBuffer(ps_chan->pLmd, (sMbsHeader*)(ps_bufhe + 1), ps_bufhe->l_evt);
        return (l_status);
    }
    // -- DABC
    ps_chan->l_io_buf_posi = ps_chan->l_buf_size;
    ps_chan->l_io_buf_size = ps_chan->l_buf_size;
    l_write_size = write(ps_chan->l_channel_no, (CHARS*)ps_bufhe, ps_chan->l_buf_size);
    if (l_write_size == -1) {
        return (PUTEVT__WRERR);
    }
    if (l_write_size != ps_chan->l_buf_size) {
        return (PUTEVT__TOOBIG);
    }
    return PUTEVT__SUCCESS;
} /* end of f_evt_put_buffer */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_put_close                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_put_close(s_evt_channel *ps_chan)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_put_close  closes specified channel.          */
/*+ ARGUMENTS   :                                                     */
/*+   channel   : Channel number.                                     */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               PUTEVT__SUCCESS   : success.                        */
/*-               PUTEVT__FAILURE   : failure.                        */
/*-               PUTEVT__CLOSE_ERR : close server or file error      */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_put_close(s_evt_channel *); */
/*+ FUNCTION    : Closes the specified output channel after writing   */
/*                last buffer.                                        */
/*1- C Main ****************+******************************************/

INTS4 f_evt_put_close(s_evt_channel* ps_chan)
{
    INTS4 l_write_size, l_temp, l_temp2;
    INTS4 l_status;
    //  CHARS* pc_addr;

    // DABC
    if (ps_chan->pLmd != NULL) {
        l_status = fLmdPutClose(ps_chan->pLmd);
        return (l_status);
    }
    // -- DABC
    if (ps_chan->l_first_put == 1) {
        goto g_close;
    }

    /* if not the end of GOOSY buf, fill buffer header  */
    if ((ps_chan->l_io_buf_posi % ps_chan->l_buf_size) != 0) {
        l_temp = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size) * ps_chan->l_buf_size;
        /* l_temp points to start of this GOOSY buf in i/o buf area  */
        memset(
            ps_chan->pc_io_buf + ps_chan->l_io_buf_posi, '\0', l_temp + ps_chan->l_buf_size - ps_chan->l_io_buf_posi);
        /* clear rest of this GOOSY buffer */
        ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + l_temp);

        ps_chan->ps_bufhe->l_dlen = (ps_chan->l_buf_size - sizeof(s_bufhe)) / 2;
        ps_chan->ps_bufhe->h_begin = 0; /* evt has end, so not spanned to next buf */
        if (l_temp == 0) {              /* so fisrt buf in stream */
            ps_chan->ps_bufhe->h_end = 0;
        } else
            ps_chan->ps_bufhe->h_end = ((s_bufhe*)((CHARS*)ps_chan->ps_bufhe - ps_chan->l_buf_size))->h_begin;
        ps_chan->ps_bufhe->i_used = (ps_chan->l_io_buf_posi % ps_chan->l_buf_size - sizeof(s_bufhe)) / 2;
    } /* end of process of infilished buffer header */

    /* if at the end of io buf, need not flush                */
    if (ps_chan->l_io_buf_posi != ps_chan->l_io_buf_size) {
        if ((ps_chan->l_io_buf_posi % ps_chan->l_buf_size) != 0)
            l_write_size = (ps_chan->l_io_buf_posi / ps_chan->l_buf_size + 1) * ps_chan->l_buf_size;
        else {
            l_write_size = ps_chan->l_io_buf_posi;
        }

        for (l_temp = 0; l_temp < l_write_size; l_temp += ps_chan->l_buf_size) {
            /* why use this loop instead of write the whole io_buf out? because in
         VMS side, the record can only be l_buf_size big, not l_write_size big */
            l_temp2 = write(ps_chan->l_channel_no, ps_chan->pc_io_buf + l_temp, ps_chan->l_buf_size);
            if (l_temp2 == -1) {
                return (PUTEVT__WRERR);
            }
            if (l_temp2 != ps_chan->l_buf_size) {
                return (PUTEVT__TOOBIG);
            }
        }
    } /* end of flush */

g_close:
    free(ps_chan->pc_io_buf);
    /* free io buffer Memory */

    l_status = close(ps_chan->l_channel_no);
    ps_chan->l_channel_no = -1;
    if (l_status == -1) {
        return (PUTEVT__CLOSE_ERR);
    } else {
        return PUTEVT__SUCCESS;
    }
} /* end of f_evt_put_close */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_error                                         */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_error( long l_error , char &c_string[], long l_out ) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_error displays error messages.                */
/*+ ARGUMENTS   :                                                     */
/*+   l_error   : The error id as returned from other calls           */
/*+   c_string  : The string into f_evt_error() copies the message....*/
/*+    l_out    : specifies the output device for the error message.  */
/*-                 out = 1 : error message is copied to string.      */
/*-                 out = 0 : error message is printed on terminal.   */
/*+ Return type : int (longword).                                     */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__FAILURE   : failure                         */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_error( INTS4 , CHARS * , INTS4 ); */
/*+ FUNCTION    : f_evt_error  displays the error message for the     */
/*                error id ( l_error ). If out = 1  the error         */
/*                message is copied into string, else                 */
/*                f_evt_error prints the message on terminal.         */
/*1- C Main ******************+****************************************/
INTS4 f_evt_error(INTS4 l_error, CHARS* pc_dest, INTS4 l_out)
{
    CHARS c_line[80];

    switch (l_error) {
        case GETEVT__NOFILE:
            sprintf(c_line, "-I-f_evt: no such input file");
            break;
        case GETEVT__NOTAGFILE:
            sprintf(c_line, "-I-f_evt: no such tag file");
            break;
        case GETEVT__NOTAG:
            sprintf(c_line, "-I-f_evt: no such event tag");
            break;
        case GETEVT__TIMEOUT:
            sprintf(c_line, "-I-f_evt: time out");
            break;
        case GETEVT__NOSERVER:
            sprintf(c_line, "-I-f_evt: no such server");
            break;
        case GETEVT__RDERR:
            sprintf(c_line, "-I-f_evt: read server error");
            break;
        case GETEVT__TAGRDERR:
            sprintf(c_line, "-I-f_evt: read tag file error");
            break;
        case GETEVT__TAGWRERR:
            sprintf(c_line, "-I-f_evt: write tag file error");
            break;
        case GETEVT__FRAGMENT:
            sprintf(c_line, "-I-f_evt: data format error");
            break;
        case GETEVT__NOMORE:
            sprintf(c_line, "-I-f_evt: no more event");
            break;
        case GETEVT__CLOSE_ERR:
            sprintf(c_line, "-I-f_evt: close server error");
            break;
        case GETEVT__FAILURE:
            sprintf(c_line, "-I-f_evt: failure");
            break;
        case GETEVT__NOCHANNEL:
            sprintf(c_line, "-I-f_evt: too many channels");
            break;
        case GETEVT__NOLMDFILE:
            sprintf(c_line, "-I-f_evt: input file is no LMD file");
            break;
        case GETEVT__SUCCESS:
            sprintf(c_line, "-I-f_evt: success");
            break;
        case PUTEVT__FILE_EXIST:
            sprintf(c_line, "-I-f_evt: output file already exist");
            break;
        case PUTEVT__WRERR:
            sprintf(c_line, "-I-f_evt: write file error");
            break;
        case PUTEVT__TOOBIG:
            sprintf(c_line, "-I-f_evt: output file too large");
            break;
        case PUTEVT__TOO_SMALLS:
            sprintf(c_line, "-I-f_evt: event can not fit in a stream");
            break;
        case PUTEVT__CLOSE_ERR:
            sprintf(c_line, "-I-f_evt: close output error");
            break;
        case PUTEVT__FAILURE:
            sprintf(c_line, "-I-f_evt: output failure");
            break;
        case PUTEVT__NOCHANNEL:
            sprintf(c_line, "-I-f_evt: too many channels");
            break;
        default:
            sprintf(c_line, "-I-f_evt: unknown message id %d", l_error);
            if (l_out == 0) {
                printf("%s\n", c_line);
            }
            if (l_out == 1) {
                strcpy(pc_dest, c_line);
            }
            return GETEVT__FAILURE;
    } /* end switch( l_error )   */

    if (l_out == 0) {
        printf("%s\n", c_line);
    }
    if (l_out == 1) {
        strcpy(pc_dest, c_line);
    }

    return GETEVT__SUCCESS;
} /* end of f_evt_error */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_buffer                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_buffer(s_evt_channel &s_chan, INTS4 *pl_buffer) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_buffer  read one buffer from server into  */
/*                user buffer.                                        */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : structure s_evt_channel.                            */
/*+   pl_buffer : Address of user buffer                              */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__FAILURE   : failure                         */
/*-               GETEVT__RDERR     : read server or file error       */
/*-               GETEVT__NOMORE    : No more events.                 */
/*-               GETEVT__TIMEOUT   : when enabled by f_evt_timeout   */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_buffer(s_evt_channel *, INTS4 *); */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_buffer(s_evt_channel* ps_chan, INTS4* ps_buffer)
{
    INTS4 l_temp;
    CHARS* pc_temp;
    INTS4 l_status;

    pc_temp = (CHARS*)ps_chan->pc_io_buf;
    switch (ps_chan->l_server_type) {
        case GETEVT__FILE:
            l_temp = read(ps_chan->l_channel_no, ps_buffer, ps_chan->l_buf_size);
            if (l_temp == 0)
            /* if end of file, then exit */
            {
                ps_chan->l_io_buf_size = 0;
                return (GETEVT__NOMORE);
            } else if (l_temp == -1) {
                ps_chan->l_io_buf_size = 0;
                return (GETEVT__RDERR);
            }
            break;
        case GETEVT__RFIO:
            l_temp = RFIO_read(ps_chan->l_channel_no, (CHARS*)ps_buffer, ps_chan->l_buf_size);
            if (l_temp == 0) {
                ps_chan->l_io_buf_size = 0;
                return (GETEVT__NOMORE);
            } else if (l_temp == -1) {
                ps_chan->l_io_buf_size = 0;
                return (GETEVT__RDERR);
            }
            break;
        case GETEVT__STREAM:
            if (ps_chan->l_stream_bufs == 0)
                if (f_stc_write("GETEVT", 7, ps_chan->l_channel_no) != STC__SUCCESS) {
                    return (GETEVT__FAILURE);
                }

            l_status = f_stc_read(ps_buffer, ps_chan->l_buf_size, ps_chan->l_channel_no, ps_chan->l_timeout);
            if (l_status == STC__TIMEOUT) {
                return (GETEVT__TIMEOUT);
            }
            if (l_status != STC__SUCCESS) {
                return (GETEVT__RDERR);
            }
            ps_chan->l_stream_bufs++;
            if (ps_chan->l_stream_bufs == ps_chan->l_bufs_in_stream) {
                ps_chan->l_stream_bufs = 0;
            }
            break;
        case GETEVT__TRANS:
            l_status = f_stc_read(ps_buffer, ps_chan->l_buf_size, ps_chan->l_channel_no, ps_chan->l_timeout);
            if (l_status == STC__TIMEOUT) {
                return (GETEVT__TIMEOUT);
            }
            if (l_status != STC__SUCCESS) {
                return (GETEVT__RDERR);
            }
            break;
        case GETEVT__REVSERV:
        case GETEVT__EVENT:
        default:
            return (GETEVT__FAILURE);
    } /* end of switch */

    /* swap */
    if (((s_bufhe*)(ps_buffer))->l_free[0] != 1) {
        f_evt_swap((CHARS*)ps_buffer, ps_chan->l_buf_size);
    }

    return (GETEVT__SUCCESS);
} /* end of f_evt_get_buffer */
/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_skip_buffer                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_skip_buffer(s_evt_channel &s_chan, INTS4 l_buffer) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Skip buffers in file.     */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : structure s_evt_channel.                            */
/*+   l_buffer  : buffers to skip                                     */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__FAILURE   : failure                         */
/*-               GETEVT__RDERR     : read server or file error       */
/*-               GETEVT__NOMORE    : No more events.                 */
/*-               GETEVT__TIMEOUT   : when enabled by f_evt_timeout   */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_skip_buffer(s_evt_channel *, INTS4); */
/*1- C Main ****************+******************************************/
INTS4 f_evt_skip_buffer(s_evt_channel* ps_chan, INTS4 l_buffer)
{
    INTS4 l_temp;
    CHARS* pc_temp;
    //  INTS4 l_status,ii;

    pc_temp = (CHARS*)ps_chan->pc_io_buf;
    switch (ps_chan->l_server_type) {
        case GETEVT__FILE:
            l_temp = lseek(ps_chan->l_channel_no, l_buffer * ps_chan->l_buf_size, SEEK_CUR);
            if (l_temp == -1)
            /* if end of file, then exit */
            {
                return (GETEVT__NOMORE);
            }
            break;
        case GETEVT__RFIO:
            l_temp = RFIO_lseek(ps_chan->l_channel_no, l_buffer * ps_chan->l_buf_size, SEEK_CUR);
            if (l_temp == -1) {
                return (GETEVT__NOMORE);
            }
            break;
        case GETEVT__STREAM:
        case GETEVT__TRANS:
        case GETEVT__REVSERV:
        case GETEVT__EVENT:
        default:
            return (GETEVT__FAILURE);
    } /* end of switch */

    ps_chan->l_first_get = 1; /* so we will first call f_getevt_get */
    return (GETEVT__SUCCESS);
} /* end of f_evt_skip_buffer */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_timeout                                       */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_timeout(s_evt_channel *ps_chan, seconds)      */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Set a timeout for TCP read operations               */
/*+ ARGUMENTS   :                                                     */
/*+  ps_chan    : Address of channel structure.                       */
/*+  seconds    :  -1: wait (default)                                 */
/*                 >0: if after n seconds no data arrived,            */
/*                 read functions return GETEVT__TIMEOUT.             */
/*+ Return type : INTS4                                               */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_timeout(s_evt_channel *, INTS4 ); */
/*+ FUNCTION    : Set a timeout for TCP read operations.              */
/*                The calls of f_evt_get_event, f_evt_get_buffer      */
/*               will return GETEVT__TIMEOUT when seconds have been   */
/*               set to positive value.                               */
/*1- C Main ****************+******************************************/
INTS4 f_evt_timeout(s_evt_channel* ps_chan, INTS4 l_sec)
{
    ps_chan->l_timeout = l_sec;
    return (GETEVT__SUCCESS);
} /* end of f_evt_timeout */

/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_swap                                          */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_evt_swap(char &c_source[], long l_length)   */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Long word byte swap.                                */
/*+ ARGUMENTS   :                                                     */
/*+    c_source    : source data array.                               */
/*+    l_length    : length (in bytes)                                */
/*+ FUNCTION    : Long word byte swap. Works on the source field.     */
/*+ Return type : int                                                 */
/*+ Status codes: bit 0: success                                      */
/*1- C Procedure ***********+******************************************/
INTS4 f_evt_swap(CHARS* pc_source, INTS4 l_length)
{
    CHARS *p_s, *p_d;
    INTS4 l_save;
    CHARS ch_temp;

    if (l_length % 4 == 2) {
        ch_temp = *(pc_source + l_length - 2);
        *(pc_source + l_length - 2) = *(pc_source + l_length - 1);
        *(pc_source + l_length - 1) = ch_temp;
    }
    l_length = (l_length / 4) * 4; /* aligned */
    for (p_d = pc_source, p_s = (CHARS*)&l_save; p_d < pc_source + l_length;) {
        l_save = *((INTS4*)p_d);
        p_s += 4; /* increment source               */
        *(p_d++) = *(--p_s);
        *(p_d++) = *(--p_s);
        *(p_d++) = *(--p_s);
        *(p_d++) = *(--p_s);
    }
    return (0);
} /* end of f_evt_swap */
/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_swap                                          */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_evt_swap_filhe(s_filhe *)   */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Swap file header.                                */
/*+ ARGUMENTS   :                                                     */
/*+    c_source    : source data array.                               */
/*+    l_length    : length (in bytes)                                */
/*+ FUNCTION    : Long word byte swap. Works on the source field.     */
/*+ Return type : int                                                 */
/*+ Status codes: bit 0: success                                      */
/*1- C Procedure ***********+******************************************/
INTS4 f_evt_swap_filhe(s_bufhe* ps_bufhe)
{
    //  CHARS* p_s, * p_d;
    INTS4 ii;
    INTS2* pi;
    s_filhe* ps_filhe;

    f_evt_swap((CHARS*)ps_bufhe, 48);
    if (ps_bufhe->i_type == 2000) {
        ps_filhe = (s_filhe*)ps_bufhe;
        f_evt_swap((CHARS*)&ps_filhe->filhe_lines, 4); /* number of comment lines ps_filhe->filhe_lines*/
        ps_filhe->filhe_label_l = ps_filhe->filhe_label_l >> 8;
        ps_filhe->filhe_file_l = ps_filhe->filhe_file_l >> 8;
        ps_filhe->filhe_user_l = ps_filhe->filhe_user_l >> 8;
        ps_filhe->filhe_run_l = ps_filhe->filhe_run_l >> 8;
        ps_filhe->filhe_exp_l = ps_filhe->filhe_exp_l >> 8;
        pi = (INTS2*)&ps_filhe->s_strings;
        for (ii = 0; ii < ps_filhe->filhe_lines; ii++) {
            *pi = *pi >> 8;
            pi += 40;
        }
    }

    return (0);
} /* end of f_evt_swap */

/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_get_buffer_ptr                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_buffer_ptr(s_evt_channel &s_chan)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_buffer_ptr returns buffer pointer         */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : structure s_evt_channel.                            */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*1- C Main ****************+******************************************/
CHARS* f_evt_get_buffer_ptr(s_evt_channel* ps_chan) { return (ps_chan->pc_io_buf); }
/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_get_newbuf                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_newbuf(s_evt_channel &s_chan)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_evt_get_newbuf  read a buffer from server         */
/*+ ARGUMENTS   :                                                     */
/*+   s_chan    : structure s_evt_channel.                            */
/*+ Return type : int.                                                */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__FAILURE   : failure                         */
/*-               GETEVT__RDERR     : read server or file error       */
/*-               GETEVT__NOMORE    : No more events.                 */
/*-               GETEVT__TIMEOUT   : when enabled by f_evt_timeout   */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_newbuf(s_evt_channel* ps_chan)
{
    INTS4 l_temp;
    CHARS* pc_temp;
    INTS4 l_status;

    pc_temp = (CHARS*)ps_chan->pc_io_buf;
    switch (ps_chan->l_server_type) {
        case GETEVT__FILE:
            while (1) {
                l_temp = read(ps_chan->l_channel_no, pc_temp, ps_chan->l_io_buf_size);
                if (l_temp == 0) {
                    return (GETEVT__NOMORE);
                }
                if (l_temp == -1) {
                    return (GETEVT__RDERR);
                }
                if (l_temp < ps_chan->l_io_buf_size) {
                    return (GETEVT__RDERR);
                }
                break; /* skip out while(1) */
            }          /* end of while(1) */
            break;
        case GETEVT__STREAM:
            if (f_stc_write("GETEVT", 7, ps_chan->l_channel_no) != STC__SUCCESS) {
                return (GETEVT__FAILURE);
            }

            for (l_temp = 0; l_temp < ps_chan->l_bufs_in_stream; l_temp++) {
                l_status = f_stc_read(pc_temp, ps_chan->l_buf_size, ps_chan->l_channel_no, ps_chan->l_timeout);
                if (l_status == STC__TIMEOUT) {
                    return (GETEVT__TIMEOUT);
                }
                if (l_status != STC__SUCCESS) {
                    return (GETEVT__RDERR);
                }
                pc_temp += ps_chan->l_buf_size;
            }
            l_temp = ((s_bufhe*)(ps_chan->pc_io_buf))->l_evt;
            if (((s_bufhe*)(ps_chan->pc_io_buf))->l_free[0] != 1) {   // swap
                f_evt_swap((CHARS*)&l_temp, 4);
            }
            if (l_temp < 0) {   // server will shutdown
                printf("**** I-f_evt: Stream server request for disconnect!\n");
                f_evt_get_close(ps_chan);
                return (GETEVT__RDERR);
            }
            /* if first buffer is empty, all are empty */
            if (((s_bufhe*)(ps_chan->pc_io_buf))->l_evt == 0) {
                return (GETEVT__TIMEOUT);
            }
            break;
        case GETEVT__TRANS:
            l_status = f_stc_read(pc_temp, ps_chan->l_buf_size, ps_chan->l_channel_no, ps_chan->l_timeout);
            l_temp = ((s_bufhe*)(ps_chan->pc_io_buf))->l_evt;
            if (((s_bufhe*)(ps_chan->pc_io_buf))->l_free[0] != 1) {   // swap
                f_evt_swap((CHARS*)&l_temp, 4);
            }
            if (l_temp < 0) {   // server will shutdown
                printf("**** I-f_evt: Transport server request for disconnect!\n");
                f_evt_get_close(ps_chan);
                return (GETEVT__RDERR);
            }
            if (l_status == STC__TIMEOUT) {
                return (GETEVT__TIMEOUT);
            }
            if (l_status != STC__SUCCESS) {
                return (GETEVT__RDERR);
            }
            break;
        case GETEVT__RFIO:
            l_temp = RFIO_read(ps_chan->l_channel_no, pc_temp, ps_chan->l_io_buf_size);
            if (l_temp == 0) {
                return (GETEVT__NOMORE);
            }
            if (l_temp == -1) {
                return (GETEVT__RDERR);
            }
            if (l_temp < ps_chan->l_io_buf_size) {
                return (GETEVT__RDERR);
            }
            break;
        case GETEVT__REVSERV:
        case GETEVT__EVENT:
        default:
            return (GETEVT__FAILURE);
    } /* end of switch */

    if (((s_bufhe*)(ps_chan->pc_io_buf))->l_free[0] != 1) {   // swap
        f_evt_swap(ps_chan->pc_io_buf, ps_chan->l_io_buf_size);
    }

    return (GETEVT__SUCCESS);
} /* end of f_evt_get_newbuf */

/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_check_buf                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_check_buf(CHARS *pc_head, INTS4 *pl_goosybuf, */
/*                                INTS4 *pl_swap, INTS4 *pl_filehead) */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : check a buffer is a file header or GOOSY buffer,    */
/*                and whether it's swaped.                            */
/*+ ARGUMENTS   :                                                     */
/*+ pc_head     : pointer to the buffer to be checked.                */
/*+ pl_goosybuf : 1 is goosy buffer, 0 is header                      */
/*+ pl_swap     : 1 means different endian, 0 means same endian.      */
/*+ pl_filehead : 1 means first buffer is header                      */
/*+ Return type : void                                                */
/*+ Status codes:                                                     */
/*+ FUNCTION    : check a buffer is a file header or GOOSY buffer,    */
/*                and whether it's swaped.                            */
/*1- C Main ****************+******************************************/
INTS4 f_evt_check_buf(CHARS* pc_head, INTS4* pl_size, INTS4* pl_is_goosybuf, INTS4* pl_swap, INTS4* pl_filehead)
{
    INTU4 l_size;

    *pl_is_goosybuf = 0;
    *pl_filehead = 0;
    *pl_size = 0;
    *pl_swap = 0;
    /* first check if it's file header */
    if ((((s_filhe*)(pc_head))->filhe_subtype == 1) && (((s_filhe*)(pc_head))->filhe_type == 2000)) {
        *pl_swap = 0;
        *pl_is_goosybuf = 0;
        *pl_filehead = 1;
        l_size = ((s_bufhe*)(pc_head))->l_dlen * 2;
        if (l_size % 512 > 0) {
            l_size += sizeof(s_bufhe);
        }
        if ((l_size >> 24) > 0) {
            *pl_size = 0;
        } else {
            *pl_size = l_size;
        }
        return (PUTEVT__SUCCESS);
    }
    f_evt_swap(pc_head, sizeof(s_filhe));
    if ((((s_filhe*)(pc_head))->filhe_subtype == 1) && (((s_filhe*)(pc_head))->filhe_type == 2000)) {
        *pl_swap = 1;
        *pl_is_goosybuf = 0;
        *pl_filehead = 1;
        l_size = ((s_bufhe*)(pc_head))->l_dlen * 2;
        if (l_size % 512 > 0) {
            l_size += sizeof(s_bufhe);
        }
        if ((l_size >> 24) > 0) {
            *pl_size = 0;
        } else {
            *pl_size = l_size;
        }
        return (PUTEVT__SUCCESS);
    }

    /* if not file header, check if it's goosy buffer header */
    l_size = ((s_bufhe*)(pc_head))->l_dlen * 2;
    if (l_size % 512 > 0) {
        l_size += sizeof(s_bufhe);
    }
    if ((((l_size >> 24) == 0) && (l_size > 0)) && (((s_bufhe*)(pc_head))->h_begin < 2)
        && (((s_bufhe*)(pc_head))->h_begin >= 0) && (((s_bufhe*)(pc_head))->h_end < 2)
        && (((s_bufhe*)(pc_head))->h_end >= 0) &&
        //(((s_bufhe *)(pc_head))->i_used<=(MAX_BUF_LGTH-sizeof(s_bufhe))/2)&&
        ((((s_bufhe*)(pc_head))->i_used > 0) || (((s_bufhe*)(pc_head))->l_free[2] > 0)) &&
        //(((s_bufhe *)(pc_head))->i_used>0)&&
        ((((s_bufhe*)(pc_head))->l_free[0] == 1) || (((s_bufhe*)(pc_head))->l_free[0] == 0) ||
         /* above, because some old lsm file forgot to set this bit, so it's zero */
         (((s_bufhe*)(pc_head))->l_free[0] == 256 * 256 * 256))) {
        *pl_swap = 1; /* !!!, because already swaped once */
        *pl_is_goosybuf = 1;
        *pl_size = l_size;
        return (PUTEVT__SUCCESS);
    }
    f_evt_swap(pc_head, sizeof(s_filhe));
    l_size = ((s_bufhe*)(pc_head))->l_dlen * 2 + sizeof(s_bufhe);
    if ((((l_size >> 24) == 0) && (l_size > 0)) && (((s_bufhe*)(pc_head))->l_dlen > 0)
        && (((s_bufhe*)(pc_head))->h_begin < 2) && (((s_bufhe*)(pc_head))->h_begin >= 0)
        && (((s_bufhe*)(pc_head))->h_end < 2) && (((s_bufhe*)(pc_head))->h_end >= 0) &&
        //(((s_bufhe *)(pc_head))->i_used<=(MAX_BUF_LGTH-sizeof(s_bufhe))/2)&&
        ((((s_bufhe*)(pc_head))->i_used > 0) || (((s_bufhe*)(pc_head))->l_free[2] > 0)) &&
        //(((s_bufhe *)(pc_head))->i_used>0)&&
        ((((s_bufhe*)(pc_head))->l_free[0] == 1) || (((s_bufhe*)(pc_head))->l_free[0] == 0) ||
         /* above, because some old lsm file forgot to set this bit, so it's zero */
         (((s_bufhe*)(pc_head))->l_free[0] == 256 * 256 * 256))) {
        *pl_swap = 0; /* !!!, because already swaped 2 times */
        *pl_is_goosybuf = 1;
        *pl_size = l_size;
        return (PUTEVT__SUCCESS);
    }
    return (PUTEVT__SUCCESS);
} /* end of f_evt_check_buf */

/*1- C Main ****************+******************************************/
/*+ Module      : f_evt_ini_bufhe                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_ini_bufhe(s_evt_channel *ps_chan)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : pre-fill each GOOSY buffer header in a stream       */
/*+ ARGUMENTS   :                                                     */
/*+  ps_chan    : Address of channel structure.                       */
/*+ Return type : void          .                                     */
/*1- C Main ****************+******************************************/
INTS4 f_evt_ini_bufhe(s_evt_channel* ps_chan)
{
    INTS4 l_temp;
    struct timeb s_timeb;

    /* because "timeb" is not "typedef", so we must use "struct" */

    for (l_temp = 0; l_temp < ps_chan->l_io_buf_size; l_temp += ps_chan->l_buf_size) {
        ps_chan->ps_bufhe = (s_bufhe*)(ps_chan->pc_io_buf + l_temp);
        ps_chan->ps_bufhe->l_dlen = (ps_chan->l_buf_size - sizeof(s_bufhe)) / 2;
        ps_chan->ps_bufhe->i_subtype = ps_chan->l_buf_subtype;
        ps_chan->ps_bufhe->i_type = ps_chan->l_buf_type;
        ps_chan->ps_bufhe->h_begin = 0;
        ps_chan->ps_bufhe->h_end = 0;
        ps_chan->ps_bufhe->i_used = 0;
        ps_chan->ps_bufhe->l_buf = ps_chan->l_buf_no;
        ps_chan->l_buf_no++;
        ps_chan->ps_bufhe->l_evt = 0;
        ps_chan->ps_bufhe->l_current_i = 0;
        ftime(&s_timeb);
        ps_chan->ps_bufhe->l_time[0] = (INTS4)s_timeb.time;
        ps_chan->ps_bufhe->l_time[1] = (INTS4)s_timeb.millitm;
        ps_chan->ps_bufhe->l_free[0] = 1; /* for swap flag */
        ps_chan->ps_bufhe->l_free[1] = 0;
        ps_chan->ps_bufhe->l_free[2] = 0;
        ps_chan->ps_bufhe->l_free[3] = 0;
    }
    return (PUTEVT__SUCCESS);
} /* end of f_evt_ini_bufhe */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_cre_tagfile                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_cre_tagfile(lmdfile,tagfile,filter)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Create a tag file from lmd file                     */
/*+ ARGUMENTS   :                                                     */
/*+  lmdfile    : LMD file name                                       */
/*+  tagfile    : tag file name                                       */
/*+  filter     : optional function for filter                        */
/*+ Return type : INTS4         .                                     */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__NOFILE    : file does not exist.            */
/*-               GETEVT__TAGWRERR  : tag file write error.            */
/*-               GETEVT__RDERR     : lmd read error.              */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_cre_tagfile(CHARS *,CHARS *, INTS4 (*)()); */
/*+ FUNCTION    : Create a tag file from lmd file       */
/*+   filter    : The filter function is called at the beginning */
/*                with a NULL as argument, then for each event */
/*                with the event pointer. Returning 0 skips the event, */
/*                1 takes the event into the tag file. */
/*                Different tag files can be created from one lmd file. */
/*1- C Main ****************+******************************************/
INTS4 f_evt_tag_filter(s_ve10_1* ps_ve10_1)
{
    /* take it */
    return (1);
    // if(ps_ve10_1 != NULL)
    //{
    //  printf("Filter   %9d Type/Subtype %5d %5d Length %5d[w] Trigger %2d\n",
    //                               ps_ve10_1->l_count,
    //                               ps_ve10_1->i_type,
    //                               ps_ve10_1->i_subtype,
    //                               ps_ve10_1->l_dlen,
    //                               ps_ve10_1->i_trigger);
    //  if(ps_ve10_1->l_count%2) return(1); /* take it */
    //  else                     return(0); /* skip it */
    //}
    // else                  printf("Initialized filter function\n");
    //  return(0);
}
INTS4 f_evt_cre_tagfile(CHARS* pc_lmd, CHARS* pc_tag, INTS4 (*e_filter)())
{
    INTS4 ii, l_take_it, l_temp, l_chan, l_out, l_file_pos = 0, l_bufnr = 0, l_events = 0;
    INTS4 l_firste, *pl, l_len, l_last = -1, l_lin = 0, l_fragsize;   //, la_head[2];
    INTS4 l_swap, l_swap_head, l_is_goosybuf, l_filehead = 0, l_size, l_size_head, l_dummy, l_evsize,
                                              l_evt_buf_size = 0;
    //  INTS2* pi;
    INTU4 *ps, *pd;
    CHARS /*c_lmd[128], c_tag[128], *pc_temp,*/* pc_evt_buf = NULL;
    s_ve10_1* ps_ve10_1;
    s_bufhe* ps_bufhe;
    s_taghe s_taghe;
    memset(&s_taghe, 0, sizeof(s_taghe));
    s_tag s_tag;
    int val;

    ps_bufhe = (s_bufhe*)c_temp;
    printf("LMD file %s, TAG file %s\n", pc_lmd, pc_tag);
    /* get file attributes */
    if ((l_chan = open(pc_lmd, GET__OPEN_FLAG)) == -1) {
        return (GETEVT__NOFILE);
    }
    /* read first 512 bytes */
    if (read(l_chan, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
        close(l_chan);
        return (GETEVT__RDERR);
    }
    /* check for file header, return size and swap */
    f_evt_check_buf(c_temp, &l_size_head, &l_is_goosybuf, &l_swap_head, &l_filehead);
    if (((l_is_goosybuf == 0) & (l_filehead == 0)) | (l_size_head == 0)) {
        printf("LMD format error: swap=%d, header=%d, isLMD=%d, size=%d\n",
               l_swap_head,
               l_filehead,
               l_is_goosybuf,
               l_size_head);
        close(l_chan);
        return (GETEVT__NOLMDFILE);
    }
    /* read file header and first buffer and check for goosy header */
    if (l_filehead == 1) {
        val = lseek(l_chan, 0, SEEK_SET); /* rewind file */
        if (-1 == val) {
            close(l_chan);
            return (GETEVT__FAILURE);
        }
        if (read(l_chan, c_temp, l_size_head) != l_size_head) {
            close(l_chan);
            return (GETEVT__RDERR);
        }
        if (read(l_chan, c_temp, MIN_BUF_LGTH) != MIN_BUF_LGTH) {
            close(l_chan);
            return (GETEVT__RDERR);
        }
        f_evt_check_buf(c_temp, &l_size, &l_is_goosybuf, &l_swap, &l_dummy);
        if ((l_is_goosybuf == 0) | (l_size != l_size_head) | (l_swap != l_swap_head)) {
            printf("LMD format error: swap=%d, isLMD=%d, size=%d\n", l_swap, l_is_goosybuf, l_size);
            close(l_chan);
            return (GETEVT__NOLMDFILE);
        }
    } /* check buffer behind header */
    else {
        l_size = 0;
        l_swap = 0;
    }

    val = lseek(l_chan, 0, SEEK_SET); /* rewind file */
    if (-1 == val) {
        close(l_chan);
        return (GETEVT__FAILURE);
    }

    printf("Buffer swap %d, File header %d, LMD buffer %d, size %d[b]\n", l_swap, l_filehead, l_is_goosybuf, l_size);

    /* found file header, skip */
    if (l_filehead == 1) {
        if (read(l_chan, c_temp, l_size) != l_size) {
            close(l_chan);
            return (GETEVT__RDERR);
        }
        l_file_pos += l_size;
        l_bufnr++;
    }

    /* Open and create tag file */
    if ((l_out = open(pc_tag, PUT__CRT_FLAG, DEF_FILE_ACCE)) == -1) {
        close(l_chan);
        return (GETEVT__NOFILE);
    }
    ssize_t wcount = write(l_out, (CHARS*)&s_taghe, sizeof(s_taghe));
    if (wcount != sizeof(s_taghe)) {
        close(l_chan);
        close(l_out);
        return (GETEVT__TAGWRERR);
    }

    /* Initialize filter function */
    // if(e_filter != NULL) { ii=(*e_filter)(NULL); }

    while (read(l_chan, c_temp, l_size) == l_size) {
        l_file_pos = l_bufnr * l_size;
        if (l_swap) {
            f_evt_swap(c_temp, l_size);
        }
        if ((ps_bufhe->h_end) & (ps_bufhe->h_begin) & (ps_bufhe->l_evt == 1)) {
            /* only fragment, next buffer */
            /* printf("Event fragment skipped Buffer %6d\n",l_bufnr);*/
            l_bufnr++;
            continue;
        }
        ps_ve10_1 = (s_ve10_1*)(ps_bufhe + 1);
        pl = (INTS4*)ps_ve10_1;
        l_file_pos += sizeof(s_bufhe);
        /* skip fragment at begin */
        if (ps_bufhe->h_end) {
            l_len = (*pl >> 1) + 2;
            l_file_pos += (l_len << 2); /* bytes */
            ps_ve10_1 = (s_ve10_1*)(pl + l_len);
            pl = (INTS4*)ps_ve10_1;
            ps_bufhe->l_evt--;
            /*     printf("Event fragment end skipped Buffer %6d\n",l_bufnr);*/
        }
        for (ii = 1; ii < ps_bufhe->l_evt; ii++) { /* except last element */
            /*printf("Event %10d pos %10d Buffer %6d\n",ps_ve10_1->l_count, l_file_pos,l_bufnr);*/
            if (e_filter != NULL) {
                l_take_it = (*e_filter)(ps_ve10_1);
            } else {
                l_take_it = 1;
            }
            l_len = (*pl >> 1) + 2;
            s_tag.l_event = ps_ve10_1->l_count;
            s_tag.l_offset = l_file_pos;
            if (l_take_it) {
                l_events++;
                if (ps_ve10_1->l_count != (l_last + 1)) {
                    l_lin++;
                    if (l_lin == 1) {
                        l_firste = ps_ve10_1->l_count;
                    }
                    /*              printf("New event number offset %d, index %d\n",ps_ve10_1->l_count,l_events);*/
                }
                l_last = ps_ve10_1->l_count;
                if (write(l_out, (CHARS*)&s_tag, sizeof(s_tag)) != sizeof(s_tag)) {
                    close(l_chan);
                    close(l_out);
                    return (GETEVT__TAGWRERR);
                }
            }
            l_file_pos += (l_len << 2); /* bytes */
            ps_ve10_1 = (s_ve10_1*)(pl + l_len);
            pl = (INTS4*)ps_ve10_1;
        }

        if (ps_bufhe->l_evt > 0) {
            if (ps_ve10_1->l_dlen < 4)
                printf("Buffer %d Event fragment %10d dlen %d ts %d %d trigger %d\n",
                       l_bufnr,
                       ps_ve10_1->l_count,
                       ps_ve10_1->l_dlen,
                       ps_ve10_1->i_type,
                       ps_ve10_1->i_subtype,
                       ps_ve10_1->i_trigger);
            s_tag.l_event = ps_ve10_1->l_count;
            if (ps_bufhe->h_begin) {
                /* copy event to event buffer for filter function */
                if (e_filter != NULL) {
                    /* is event buffer big enough? */
                    l_evsize = ps_bufhe->l_free[1] + 4; /* total words */
                    if (l_evt_buf_size < l_evsize * 2) {
                        if (pc_evt_buf != NULL) {
                            free(pc_evt_buf);
                        }
                        l_evt_buf_size = l_evsize * 2;
                        pc_evt_buf = (CHARS*)malloc(l_evt_buf_size);
                    }
                    if (NULL == pc_evt_buf) {
                        l_evt_buf_size = l_evsize * 2;
                        pc_evt_buf = (CHARS*)malloc(l_evt_buf_size);
                    }
                    /* copy event fragment to buffer */
                    ps = (INTU4*)ps_ve10_1;
                    pd = (INTU4*)pc_evt_buf;
                    l_fragsize = ps_ve10_1->l_dlen + 4; /* fragment size + header [w] */
                    for (ii = 0; ii < l_fragsize / 2; ii++) {
                        *pd++ = *ps++;
                    }
                    /* loop over fragments */
                    while (l_fragsize < l_evsize) {
                        if (read(l_chan, c_temp, l_size) != l_size) {
                            break;
                        }
                        l_bufnr++;
                        if (l_swap) {
                            f_evt_swap(c_temp, l_size);
                        }
                        ps = (INTU4*)(ps_bufhe + 1); /* behind buffer header, fragment header */
                        l_temp = (INTS4)*ps;         /* fragment size [w] */
                        ps += 2;                     /* to data behind fragment header */
                        for (ii = 0; ii < l_temp / 2; ii++) {
                            *pd++ = *ps++;
                        }
                        l_fragsize += l_temp;
                    }
                    if (l_fragsize < l_evsize) {
                        break;
                    }
                    ps_ve10_1 = (s_ve10_1*)pc_evt_buf;
                    ps_ve10_1->l_dlen = l_evsize - 4;
                    /* rewind last buffer, will be read again by while loop */
                    l_bufnr--;
                    val = lseek(l_chan, -l_size, SEEK_CUR);
                    if (-1 == val) {
                        free(pc_evt_buf);
                        ps_ve10_1 = NULL;
                        pd = NULL;
                        close(l_chan);
                        close(l_out);
                        return (GETEVT__FAILURE);
                    }
                }
                s_tag.l_offset = -l_file_pos;
                /* printf("Event %10d pos %10d Buffer -%6d\n",ps_ve10_1->l_count, l_file_pos,l_bufnr);*/
            } else {
                s_tag.l_offset = l_file_pos;
                /* printf("Event %10d pos %10d Buffer  %6d\n",ps_ve10_1->l_count, l_file_pos,l_bufnr);*/
            }
            if (e_filter != NULL) {
                l_take_it = (*e_filter)(ps_ve10_1);
            } else {
                l_take_it = 1;
            }
            if (l_take_it) {
                l_events++;
                if (ps_ve10_1->l_count != (l_last + 1)) {
                    l_lin++;
                    if (l_lin == 1) {
                        l_firste = ps_ve10_1->l_count;
                    }
                    /*              printf("New event number offset %d, index %d\n",ps_ve10_1->l_count,l_events);*/
                }
                l_last = ps_ve10_1->l_count;
                if (write(l_out, (CHARS*)&s_tag, sizeof(s_tag)) != sizeof(s_tag)) {
                    close(l_chan);
                    close(l_out);
                    return (GETEVT__TAGWRERR);
                }
            }
        }
        l_bufnr++;
        /*      if(l_bufnr > 3) break; */
    }
    val = lseek(l_out, 0, SEEK_SET); /* rewind file */
    if (-1 == val) {
        close(l_chan);
        close(l_out);
        return (GETEVT__FAILURE);
    }
    s_taghe.l_endian = 1;
    s_taghe.l_version = 1;
    s_taghe.l_bufsize = l_size;
    s_taghe.l_buffers = l_bufnr;
    s_taghe.l_events = l_events;
    s_taghe.l_filesize = sizeof(s_tag) * l_events;
    s_taghe.l_linear = (l_lin == 1);
    s_taghe.l_first = l_firste;
    s_taghe.l_last = s_tag.l_event;
    if (write(l_out, (CHARS*)&s_taghe, sizeof(s_taghe)) != sizeof(s_taghe)) {
        close(l_chan);
        close(l_out);
        return (GETEVT__TAGWRERR);
    }
    close(l_chan);
    close(l_out);
    printf("Buffers %6d, of size %d, Events %10d, first %d, last %d ",
           s_taghe.l_buffers,
           s_taghe.l_bufsize,
           s_taghe.l_events,
           s_taghe.l_first,
           s_taghe.l_last);
    if (s_taghe.l_linear) {
        printf("linear\n");
    } else {
        printf("not linear\n");
    }

    return (GETEVT__SUCCESS);
} /* end of f_evt_cre_tagfile */
/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_tagopen                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_tagopen(channel,tagfile,lmdfile,header,print)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Open tag and lmd file                    */
/*+ ARGUMENTS   :                                                     */
/*+  channel    : s_evt_channel* , must be allocated. */
/*+  tagfile    : Name of tag file */
/*+  filename   : LMD file name                                       */
/*+  header     : address of CHARS pointer. If it is not NULL, then         */
/*                try to return file header or other information      */
/*                about server. If it is NULL, then returns nothing.  */
/*+  print      : Print flag: 1=verbose */
/*+ Return type : INTS4         .                                     */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__NOFILE    : file does not exist.            */
/*-               GETEVT__TAGRDERR  : tag file read error.            */
/*-               GETEVT__RDERR     : read server error.              */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_tagopen( */
/*                     s_evt_channel *,CHARS *,CHARS *,CHARS **,INTS4); */
/*+ FUNCTION    : Open tag file and lmd file. If no tag file is found,       */
/*                a standard f_evt_get_open is called. In this case */
/*                following tag functions call standard f_evt_get functions. */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_tagopen(s_evt_channel* ps_chan, CHARS* pc_tag, CHARS* pc_lmd, CHARS** ps_head, INTS4 l_prihe)
{
    INTS4 /*l_temp,*/ ii;
    s_bufhe* ps_bufhe;

    ps_chan->ps_tag = NULL; /* tagfile buffer */
    ps_chan->ps_taghe = NULL;
    if (l_prihe) {
        printf("LMD file %s, TAG file %s\n", pc_lmd, pc_tag);
    }

    /* if tag file name not specified, do not try to open it SL:11.11.09*/
    if ((pc_tag == 0) || (*pc_tag == 0)) {
        ps_chan->l_tagfile_no = -1;
    } else {
        ps_chan->l_tagfile_no = open(pc_tag, GET__OPEN_FLAG);
    }

    /* open tag file and read header */
    if (ps_chan->l_tagfile_no == -1) {
        /* no tag file, use normal open */
        /*=============================================*/
        ii = f_evt_get_open(GETEVT__FILE, pc_lmd, ps_chan, (CHARS**)&ps_bufhe, 0, 0);
        *ps_head = (CHARS*)ps_bufhe;
        if (ii != GETEVT__SUCCESS) {
            printf("Error opening input file %s\n", pc_lmd);
            return (ii);
        }
        /*    printf("No tag file for %s\n",pc_lmd); */
        if (l_prihe) {
            ii = f_evt_type(ps_bufhe, NULL, 0, 0, 0, 0);
        }
        return (GETEVT__SUCCESS);
    }
    /*=============================================*/
    /* tag file found */
    ps_chan->ps_taghe = (s_taghe*)malloc(sizeof(s_taghe));
    if (read(ps_chan->l_tagfile_no, (CHARS*)ps_chan->ps_taghe, sizeof(s_taghe)) != sizeof(s_taghe)) {
        free(ps_chan->ps_taghe);
        ps_chan->ps_taghe = NULL;
        close(ps_chan->l_tagfile_no);
        return (GETEVT__TAGRDERR);
    }
    if (NULL == ps_chan->ps_taghe) {
        close(ps_chan->l_tagfile_no);
        return (GETEVT__TAGRDERR);
    }
    if (ps_chan->ps_taghe->l_endian != 1) {
        ps_chan->l_tagswap = 1;
    }
    if (ps_chan->l_tagswap) {
        f_evt_swap((CHARS*)ps_chan->ps_taghe, sizeof(s_taghe));
    }
    if (l_prihe) {
        printf("Buffers %6d, of size %d, Events %10d, first %d, last %d",
               ps_chan->ps_taghe->l_buffers,
               ps_chan->ps_taghe->l_bufsize,
               ps_chan->ps_taghe->l_events,
               ps_chan->ps_taghe->l_first,
               ps_chan->ps_taghe->l_last);
        if (ps_chan->ps_taghe->l_linear) {
            printf(" linear\n");
        } else {
            printf(" not linear\n");
        }
    }
    if ((ps_chan->l_channel_no = open(pc_lmd, GET__OPEN_FLAG)) == -1) {
        if (ps_chan->ps_taghe != NULL) {
            free(ps_chan->ps_taghe);
        }
        ps_chan->ps_taghe = NULL;
        close(ps_chan->l_tagfile_no);
        return (GETEVT__NOFILE);
    }
    /* read buffer header to check if we have to swap */
    ps_bufhe = (s_bufhe*)c_temp;
    if (ps_chan->ps_taghe->l_bufsize >= 0 && ps_chan->ps_taghe->l_bufsize < sizeof(c_temp)) {
        if (read(ps_chan->l_channel_no, c_temp, ps_chan->ps_taghe->l_bufsize) != ps_chan->ps_taghe->l_bufsize) {
            if (ps_chan->ps_taghe != NULL) {
                free(ps_chan->ps_taghe);
            }
            ps_chan->ps_taghe = NULL;
            if (ps_chan->ps_tag != NULL) {
                free(ps_chan->ps_tag);
            }
            ps_chan->ps_tag = NULL;
            close(ps_chan->l_tagfile_no);
            close(ps_chan->l_channel_no);
            return (GETEVT__RDERR);
        }
    }
    if (ps_chan->ps_taghe != NULL) {
        if (ps_chan->ps_taghe->l_linear == 0) {
            if (ps_chan->ps_taghe->l_filesize >= 0 && ps_chan->ps_taghe->l_filesize < sizeof(s_tag)) {
                ps_chan->ps_tag = (s_tag*)malloc(ps_chan->ps_taghe->l_filesize);
                if (read(ps_chan->l_tagfile_no, (CHARS*)ps_chan->ps_tag, ps_chan->ps_taghe->l_filesize)
                    != ps_chan->ps_taghe->l_filesize) {
                    if (ps_chan->ps_taghe != NULL) {
                        free(ps_chan->ps_taghe);
                    }
                    ps_chan->ps_taghe = NULL;
                    if (ps_chan->ps_tag != NULL) {
                        free(ps_chan->ps_tag);
                    }
                    ps_chan->ps_tag = NULL;
                    close(ps_chan->l_tagfile_no);
                    close(ps_chan->l_channel_no);
                    return (GETEVT__TAGRDERR);
                }
            }
        }
    }
    if (ps_bufhe->l_free[0] != 1) {
        ps_chan->l_lmdswap = 1;
    }
    if (ps_chan->l_lmdswap) {
        f_evt_swap_filhe(ps_bufhe);
    }
    if (l_prihe) {
        ii = f_evt_type(ps_bufhe, NULL, 0, 0, 0, 0);
    }
    if (ps_head != NULL) {
        if (ps_bufhe->i_type == 2000) {
            *ps_head = (CHARS*)ps_bufhe;
        }
    }
    ps_chan->l_evt_buf_size = 0;
    ps_chan->pc_evt_buf = NULL;
    ps_chan->l_io_buf_posi = 0; /* keeps index of last event */
    return (GETEVT__SUCCESS);
}

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_tagnext                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_tagnext(channel,skip,**event)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Get tagged event from lmd file                    */
/*+ ARGUMENTS   :                                                     */
/*+  channel    : s_evt_channel* , must be allocated. */
/*+  event      : address of pointer. If it is not NULL, then         */
/*                return event pointer.      */
/*+ Return type : INTS4         .                                     */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__NOFILE    : file does not exist.            */
/*-               GETEVT__TAGRDERR  : tag file read error.            */
/*-               GETEVT__RDERR     : lmd read error.              */
/*-               GETEVT__FRAGMENT  : Event fragment found.           */
/*-               GETEVT__NOMORE    : No more events.                 */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_tagnext(s_evt_channel *,INTS4,INTS4 **); */
/*+ FUNCTION    : Get next event at current position, either in tag      */
/*                file, or in lmd file. Optional <skip> events are skipped. */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_tagnext(s_evt_channel* ps_chan, INTS4 l_skip, INTS4** pl_event)
{
    INTS4 ii = 0, *pl = NULL, kk;
    /* no tagfile */
    /*=============================================*/
    if (ps_chan->ps_taghe == NULL) {
        for (kk = 0; kk <= l_skip; kk++) {
            ii = f_evt_get_event(ps_chan, (INTS4**)&pl, NULL);
            if (ii != GETEVT__SUCCESS) {
                break;
            }
        }
    }
    /*=============================================*/
    else {
        /* l_io_buf_posi is the index of last event */
        ii = f_evt_get_tagevent(ps_chan, ps_chan->l_io_buf_posi + l_skip + 1, 1, (INTS4**)&pl);
    }
    if (pl_event != NULL) {
        *pl_event = pl;
    }
    return (ii);
}
/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_tagevent                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_tagevent(*channel, value, mode, **event)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Get tagged event from lmd file                    */
/*+ ARGUMENTS   :                                                     */
/*+  channel    : s_evt_channel* , must be allocated. */
/*+   value     : event number or index */
/*+   mode      : 0: value is number, 1: value is index */
/*+   event     : address of pointer. If it is not NULL, then         */
/*                return event pointer.      */
/*+ Return type : INTS4         .                                     */
/*+ Status codes:                                                     */
/*-               GETEVT__SUCCESS   : success.                        */
/*-               GETEVT__TAGRDERR  : tag file read error.            */
/*-               GETEVT__RDERR     : lmd read error.              */
/*-               GETEVT__FRAGMENT  : Event fragment found.           */
/*-               GETEVT__NOMORE    : No more events.                 */
/*-               GETEVT__NOTAG     : Specified event not in tag file.              */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_tagevent( */
/*                           s_evt_channel *,INTS4,INTS4,INTS4 **); */
/*+ FUNCTION    : Get tag event. If no tag file is there, skip <value> */
/*                events, or look for event number <value>     */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_tagevent(s_evt_channel* ps_chan, INTS4 l_value, INTS4 l_type, INTS4** pl_event)
{
    INTS4 /*l_temp,l_chan,l_tag,*/ ii, kk, /*lb,l_tagbufs,l_tagrest,*/ l_evt, l_off, l_typ, l_val, l_evsize, l_fragsize;
    INTS4 la_head[2], *pl;
    CHARS* pc;
    s_ve10_1* ps_ve10_1;
    s_bufhe* ps_bufhe;
    s_tag* ps_tag;
    s_tag s_tag_l;
    //  s_filhe* ps_filhe;
    //  s_evt_channel s_chan_i;

    l_typ = l_type;
    l_val = l_value;
    /* no tagfile */
    /*=============================================*/
    if (ps_chan->ps_taghe == NULL) {
        /* search by index */
        if (l_type == 1) {
            if (l_val == 0) {
                l_val = 1;
            }
            for (kk = 0; kk < l_val; kk++) {
                ii = f_evt_get_event(ps_chan, (INTS4**)&pl, NULL);
                if (ii != GETEVT__SUCCESS) {
                    return (ii);
                }
            }
            *pl_event = pl;
        } else { /* search by event number */
            ii = f_evt_get_event(ps_chan, (INTS4**)&ps_ve10_1, NULL);
            if (ii != GETEVT__SUCCESS) {
                return (ii);
            }
            while (ps_ve10_1->l_count != l_val) {
                ii = f_evt_get_event(ps_chan, (INTS4**)&ps_ve10_1, NULL);
                if (ii != GETEVT__SUCCESS) {
                    return (ii);
                }
            }
            *pl_event = (INTS4*)ps_ve10_1;
        }
        return (GETEVT__SUCCESS);
    }
    /*=============================================*/
    ps_ve10_1 = (s_ve10_1*)c_temp;
    ps_bufhe = (s_bufhe*)c_temp;

    /* linear==1 means that event numbers are subsequent. */
    /* in that case we can calculate index from number */
    if (ps_chan->ps_taghe->l_linear) {
        if (l_typ == 0) {
            l_val = l_value - ps_chan->ps_taghe->l_first + 1;
        }
        l_typ = 1;
    }
    /* search by index or by value */
    if (l_typ == 1) {
        if (l_val > ps_chan->ps_taghe->l_events) {
            printf("Event index %d not found\n", l_val);
            return (GETEVT__NOTAG);
        }
        if (l_val == 0) {
            l_val = 1;
        }
        ps_tag = (s_tag*)&s_tag_l;
        int val =
            lseek(ps_chan->l_tagfile_no, (l_val - 1) * sizeof(s_tag) + sizeof(s_taghe), SEEK_SET); /* set file offset*/
        if (-1 == val) {
            return (GETEVT__TAGRDERR);
        }
        if (read(ps_chan->l_tagfile_no, (CHARS*)ps_tag, sizeof(s_tag)) != sizeof(s_tag)) {
            return (GETEVT__TAGRDERR);
        }
        if (ps_chan->l_tagswap) {
            f_evt_swap((CHARS*)ps_tag, sizeof(s_tag));
        }
        ps_chan->l_io_buf_posi = l_val; /* keeps index */
    } else {
        ps_tag = ps_chan->ps_tag;
        for (ii = 1; ii <= ps_chan->ps_taghe->l_events; ii++) {
            if (ps_tag->l_event == l_val) {
                break;
            }
            ps_tag++;
        }
        if (ps_tag->l_event != l_val) {
            printf("Event number %d not found\n", l_val);
            return (GETEVT__NOTAG);
        }
        ps_chan->l_io_buf_posi = ii; /* keeps index of last event */
    }
    /* now we have the requested event in ps_tag */
    l_off = ps_tag->l_offset;
    if (l_off < 0) {
        l_off = ((-l_off) / ps_chan->ps_taghe->l_bufsize) * ps_chan->ps_taghe->l_bufsize;
    }
    l_evt = ps_tag->l_event;
    /* full event in buffer, read */
    int val;
    if (ps_tag->l_offset > 0) {
        ps_ve10_1 = (s_ve10_1*)c_temp;
        val = lseek(ps_chan->l_channel_no, l_off, SEEK_SET); /* set file offset*/
        if (-1 == val) {
            return (GETEVT__TAGRDERR);
        }
        if (read(ps_chan->l_channel_no, c_temp, 8) != 8) {
            return (GETEVT__RDERR);
        }
        if (ps_chan->l_lmdswap) {
            f_evt_swap(c_temp, 8);
        }
        if (read(ps_chan->l_channel_no, (CHARS*)&c_temp[8], ps_ve10_1->l_dlen * 2) != ps_ve10_1->l_dlen * 2) {
            return (GETEVT__RDERR);
        }
        if (ps_chan->l_lmdswap) {
            f_evt_swap((CHARS*)&c_temp[8], ps_ve10_1->l_dlen * 2);
        }
        /*ii=f_evt_type(NULL,(s_evhe *)ps_ve10_1,-1,0,1,1);*/
    } else
    /* spanning event begin, read to event buffer */
    {
        val = lseek(ps_chan->l_channel_no, l_off, SEEK_SET); /* set file offset to buffer begin */
        if (-1 == val) {
            return (GETEVT__TAGRDERR);
        }
        if (read(ps_chan->l_channel_no, c_temp, sizeof(s_bufhe)) != sizeof(s_bufhe)) {
            return (GETEVT__RDERR);
        }
        if (ps_chan->l_lmdswap) {
            f_evt_swap(c_temp, sizeof(s_bufhe));
        }
        /* is event buffer big enough? */
        l_evsize = ps_bufhe->l_free[1] + 4; /* total words */
        if (ps_chan->l_evt_buf_size < l_evsize * 2) {
            if (ps_chan->pc_evt_buf != NULL) {
                free(ps_chan->pc_evt_buf);
            }
            ps_chan->l_evt_buf_size = l_evsize * 2;
            ps_chan->pc_evt_buf = (CHARS*)malloc(ps_chan->l_evt_buf_size);
        }
        l_fragsize = 0;
        ps_ve10_1 = (s_ve10_1*)ps_chan->pc_evt_buf;
        val = lseek(ps_chan->l_channel_no, -ps_tag->l_offset, SEEK_SET); /* set file offset*/
        if (-1 == val) {
            return (GETEVT__TAGRDERR);
        }
        if (read(ps_chan->l_channel_no, ps_chan->pc_evt_buf, 8) != 8) {
            return (GETEVT__RDERR);
        }
        if (ps_chan->l_lmdswap) {
            f_evt_swap(ps_chan->pc_evt_buf, 8);
        }
        pc = ps_chan->pc_evt_buf + 8;
        /* read fragment */
        if (read(ps_chan->l_channel_no, pc, ps_ve10_1->l_dlen * 2) != ps_ve10_1->l_dlen * 2) {
            return (GETEVT__RDERR);
        }
        l_fragsize += ps_ve10_1->l_dlen + 4; /* fragment size + header [w] */
        pc += ps_ve10_1->l_dlen * 2;         /* next in event buffer */
        ps_ve10_1->l_dlen = l_evsize - 4;    /* set correct event size */
        /* loop over fragments */
        while (l_fragsize < l_evsize) {
            l_off += ps_chan->ps_taghe->l_bufsize;                                 /* next buffer absolut address */
            val = lseek(ps_chan->l_channel_no, l_off + sizeof(s_bufhe), SEEK_SET); /* set file offset*/
            if (-1 == val) {
                return (GETEVT__TAGRDERR);
            }
            if (read(ps_chan->l_channel_no, (CHARS*)&la_head, 8) != 8) {
                return (GETEVT__RDERR);
            }
            if (ps_chan->l_lmdswap) {
                f_evt_swap((CHARS*)&la_head, 8);
            }
            if (read(ps_chan->l_channel_no, pc, la_head[0] * 2) != la_head[0] * 2) {
                return (GETEVT__RDERR);
            }
            pc += la_head[0] * 2;
            l_fragsize += la_head[0];
        }
        /* now swap whole event in buffer */
        pc = ps_chan->pc_evt_buf + 8; /* header already swapped */
        ps_ve10_1 = (s_ve10_1*)ps_chan->pc_evt_buf;
        if (ps_chan->l_lmdswap) {
            f_evt_swap(pc, ps_ve10_1->l_dlen * 2);
        }
    }
    *pl_event = (INTS4*)ps_ve10_1;
    return (GETEVT__SUCCESS);
} /* end of f_evt_ini_bufhe */

/*1+ C Main ****************+******************************************/
/*+ Module      : f_evt_get_tagclose                                     */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_evt_get_tagclose(s_evt_channel)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Close tag and lmd file, cleanup s_evt_channel                   */
/*+ ARGUMENTS   :                                                     */
/*+  channel    : s_evt_channel* , must be allocated. */
/*+ Return type : INTS4                                              */
/*+ Declaration :                                                     */
/*                INTS4 f_evt_get_tagclose(s_evt_channel *); */
/*+ FUNCTION    : Create a tag file from lmd file       */
/*1- C Main ****************+******************************************/
INTS4 f_evt_get_tagclose(s_evt_channel* ps_chan)
{
    /*=============================================*/
    if (ps_chan->ps_taghe == NULL) {
        f_evt_get_close(ps_chan);
        return (GETEVT__SUCCESS);
    }
    /*=============================================*/
    free(ps_chan->ps_taghe);
    if (ps_chan->ps_tag != NULL) {
        free(ps_chan->ps_tag);
    }
    if (ps_chan->pc_evt_buf != NULL) {
        free(ps_chan->pc_evt_buf);
    }
    close(ps_chan->l_tagfile_no);
    close(ps_chan->l_channel_no);
    memset((void*)ps_chan, 0, sizeof(s_evt_channel)); /* clear memory                 */
    return (GETEVT__SUCCESS);
}
s_evt_channel* f_evt_control()
{
    s_evt_channel* x;
    x = (s_evt_channel*)malloc(sizeof(s_evt_channel));
    memset(x, 0, sizeof(s_evt_channel));
    return (x);
}
