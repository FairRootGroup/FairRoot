/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
#include "f_his_hist.h"
#include "f_his_toupper.h"
#include "f_his_swpbas.h"
#include "f_stccomm.h"
#include "f_swaplw.h"
#include "f_ut_compress.h"
#include "portnum_def.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
static CHARS c_gl_serv_access[64];
static CHARS c_gl_serv_base[32];
static INTS4 l_gl_serv_port;
static INTS4 l_gl_serv_chan;
static INTS4 l_gl_serv_verb;
struct s_tcpcomm* ps_tcpserv;
s_his_comm s_his_comm_serv;
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_getbas                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_getbas(char server, int port, char base, char password, int **p_buf)*/
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Returns list of histogram available from server     */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   c_server  : Node of server.                                     */
/*+  l_port     : Port number (must be known from server)             */
/*+  c_base     : Histogram base name                                 */
/*+  c_password : Password if required from server                    */
/*+    p_buf    : Address of buffer pointer.                          */
/*                Data base is allocated and address returned.        */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOACCESS: Password wrong                      */
/*-               COMM__NOBASE  : Base wrong                          */
/*-               COMM__NOSERVER: Cannot connect (Port?)              */
/*-               COMM__NOHIST  : Histogram not there                 */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Connects to histogram server.                       */
/*                Allocates and returns LEA data base                 */
/*                Bse must be compressed by server.                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_getbas(CHARS* pc_server, INTS4 l_port, CHARS* pc_base, CHARS* pc_access,INTS4** p_buffer)
{
  s_his_comm s_his_comm_cli;
//  s_his_head* ps_his_head;
  INTS4 i_j,i_l,l_status,l_chan,l_swap,l_buffer;//,l_histos,l_size;
  INTS4* pl_all=NULL,*pl_l;
  s_compress*               ps_compress;
  struct s_tcpcomm* ps_tcpcli;

  ps_tcpcli = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));

  /* get base ***************************************************/
  s_his_comm_cli.lu_endian=1;
  s_his_comm_cli.lu_size=0;
  s_his_comm_cli.lu_histos=0;
  s_his_comm_cli.lu_action=COMM__GETBASE;
  s_his_comm_cli.l_status=COMM__SUCCESS;
  strcpy(s_his_comm_cli.c_histo,"*");
  strcpy(s_his_comm_cli.c_access,pc_access);
  strcpy(s_his_comm_cli.c_base,pc_base);
  l_status = f_stc_connectserver (pc_server,l_port, &l_chan, ps_tcpcli);
  if(l_status != STC__SUCCESS) {l_status=COMM__NOSERVER; goto g_return;}
  l_status = f_stc_write(&s_his_comm_cli,sizeof(s_his_comm),l_chan);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_status = f_stc_read (&s_his_comm_cli,sizeof(s_his_comm),l_chan,-1);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_swap = (s_his_comm_cli.lu_endian > 1);
  if(l_swap) { l_status = f_swaplw((INTS4*)&s_his_comm_cli,5,NULL); }
  if(s_his_comm_cli.l_status != COMM__SUCCESS) {l_status=s_his_comm_cli.l_status; goto g_return;}

  /* allocate buffer for comporessed base */
  pl_all  = (INTS4*)malloc(s_his_comm_cli.lu_size);
  l_buffer = s_his_comm_cli.lu_size;
  /* break total buffer in TCP buffers */
  pl_l=pl_all;
  i_l=l_buffer/16384;
  l_buffer=l_buffer%16384;
  for(i_j=0; i_j<i_l; i_j++) {l_status = f_stc_read (pl_l,16384,l_chan,-1); pl_l+=4096;}
  if(l_buffer > 0) { l_status = f_stc_read (pl_l,l_buffer,l_chan,-1); }
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  /* uncompress base */
  ps_compress = (s_compress*) pl_all;
  if(l_swap == 1) {
    f_swaplw((INTS4*)pl_all,sizeof(s_compress)/4,NULL);
    pl_l=pl_all+(sizeof(s_compress)/4);
    f_swaplw((INTS4*)pl_l,ps_compress->l_masks,NULL);
  }
  *p_buffer  = (INTS4*)malloc(ps_compress->l_full_bytes);
  f_ut_compr_unpack((INTU1*)pl_all,(INTU1*) *p_buffer,ps_compress->l_full_bytes);
  if(l_swap == 1) { l_status = f_his_swpbas((s_head*) *p_buffer); }

  l_status=COMM__SUCCESS;
g_return:
  f_stc_discclient (l_chan);
  f_stc_close (ps_tcpcli);
  free(pl_all);
  free(ps_tcpcli);
  return(l_status);
}
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_getdir                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_getdir(char server, int port, char base, char password,*/
/*                              char histo, int **p_buf, int **l_histos)*/
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Returns list of histogram available from server     */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   c_server  : Node of server.                                     */
/*+  l_port     : Port number (must be known from server)             */
/*+  c_base     : Histogram base name                                 */
/*+  c_password : Password if required from server                    */
/*+  c_histo    : Histogram wildcard                                  */
/*+    p_buf    : Address of buffer pointer.                          */
/*                If NULL, buffer is allocated, if not l_histos gives */
/*                size of buffer in sizeof(s_his_head).               */
/*+   l_histos  : Size in sizeof(s_his_head) of buffer,               */
/*                returns number of histograms                        */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOACCESS: Password wrong                      */
/*-               COMM__NOBASE  : Base wrong                          */
/*-               COMM__NOSERVER: Cannot connect (Port?)              */
/*-               COMM__NOHIST  : Histogram not there                 */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Connects to histogram server.                       */
/*                Returns buffer with s_his_head slots                */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_getdir(CHARS* pc_server, INTS4 l_port, CHARS* pc_base, CHARS* pc_access, CHARS* pc_histo
                   ,INTS4** p_buffer, INTS4* pl_histos)
{
  s_his_comm s_his_comm_cli;
  s_his_head* ps_his_head;
  INTS4 i_j,i_l,l_status,l_chan,l_swap,l_buffer,l_histos,l_size;
  INTS4* pl_all,*pl_l;
  struct s_tcpcomm* ps_tcpcli;

  ps_tcpcli = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));

  /* get directory ***************************************************/
  s_his_comm_cli.lu_endian=1;
  s_his_comm_cli.lu_size=0;
  s_his_comm_cli.lu_histos=0;
  s_his_comm_cli.lu_action=COMM__GETDIR;
  s_his_comm_cli.l_status=COMM__SUCCESS;
  strcpy(s_his_comm_cli.c_histo,pc_histo);
  strcpy(s_his_comm_cli.c_access,pc_access);
  strcpy(s_his_comm_cli.c_base,pc_base);
  l_status = f_stc_connectserver (pc_server,l_port, &l_chan, ps_tcpcli);
  if(l_status != STC__SUCCESS) {l_status=COMM__NOSERVER; goto g_return;}
  l_status = f_stc_write(&s_his_comm_cli,sizeof(s_his_comm),l_chan);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_status = f_stc_read (&s_his_comm_cli,sizeof(s_his_comm),l_chan,-1);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_swap = (s_his_comm_cli.lu_endian > 1);
  if(l_swap) { l_status = f_swaplw((INTS4*)&s_his_comm_cli,5,NULL); }
  if(s_his_comm_cli.l_status != COMM__SUCCESS) {l_status=s_his_comm_cli.l_status; goto g_return;}

  l_histos=s_his_comm_cli.lu_histos;
  l_size=sizeof(s_his_head)*l_histos;
  /* allocate buffer */
  if(*p_buffer == 0) {
    pl_all  = (INTS4*)malloc(l_size);
    *p_buffer = pl_all;
  } else {
    if(*pl_histos < l_histos) {l_status=COMM__ERROR; goto g_return;}
    pl_all = *p_buffer;
  }
  *pl_histos = l_histos;
  l_buffer = s_his_comm_cli.lu_size;
  /* break total buffer in TCP buffers */
  pl_l=pl_all;
  i_l=l_buffer/16384;
  l_buffer=l_buffer%16384;
  for(i_j=0; i_j<i_l; i_j++) {l_status = f_stc_read (pl_l,16384,l_chan,-1); pl_l+=4096;}
  if(l_buffer > 0) { l_status = f_stc_read (pl_l,l_buffer,l_chan,-1); }
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}

  ps_his_head = (s_his_head*)pl_all;
  for(i_j=0; i_j<s_his_comm_cli.lu_histos; i_j++) {
    if(l_swap) { l_status = f_swaplw((INTS4*)ps_his_head,16,NULL); }
    ps_his_head++;

  }
  l_status=COMM__SUCCESS;
g_return:
  f_stc_discclient (l_chan);
  f_stc_close (ps_tcpcli);
  free(ps_tcpcli);
  return(l_status);
}
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_gethis                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_gethis(char server, int port, char base, char password,*/
/*                        char histo, s_his_head **p_head, int **p_buf, int **l_size)*/
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Returns histogram from server                       */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   c_server  : Node of server.                                     */
/*+  l_port     : Port number (must be known from server)             */
/*+  c_base     : Histogram base name                                 */
/*+  c_password : Password if required from server                    */
/*+  c_histo    : Histogram                                           */
/*+    p_head   : Address of header pointer (s_his_head)              */
/*                If NULL, s_his_head will be allocated               */
/*+    p_buf    : Address of buffer pointer                           */
/*                If NULL, buffer for data will be allocated          */
/*+   l_size    : Size in bytes of buffer, returns size               */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOACCESS: Password wrong                      */
/*-               COMM__NOBASE  : Base wrong                          */
/*-               COMM__NOSERVER: Cannot connect (Port?)              */
/*-               COMM__NOHIST  : Histogram not there                 */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Connects to histogram server.                       */
/*                Returns buffer with s_his_head and data buffer      */
/*                Required buffer size can be obtained from           */
/*                s_his_head after calling f_his_getdir.              */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_gethis(CHARS* pc_server, INTS4 l_port, CHARS* pc_base, CHARS* pc_access, CHARS* pc_histo
                   , s_his_head** p_head, INTS4** p_buffer, INTS4* pl_size)
{
  s_his_comm s_his_comm_cli;
  s_his_head* ps_his_head;
  INTS4 i_j,i_l,l_status,l_chan,l_swap,l_buffer,/*l_histos,*/l_size;
  INTS4* pl_all/*,*pl_head*/,*pl_l;
  struct s_tcpcomm* ps_tcpcli;

  ps_tcpcli = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));

  /* get histogram ******************************************************/
  s_his_comm_cli.lu_endian=1;
  s_his_comm_cli.lu_size=0;
  s_his_comm_cli.lu_histos=0;
  s_his_comm_cli.lu_action=COMM__GETHIST;
  s_his_comm_cli.l_status=COMM__SUCCESS;
  strcpy(s_his_comm_cli.c_histo,pc_histo);
  strcpy(s_his_comm_cli.c_access,pc_access);
  strcpy(s_his_comm_cli.c_base,pc_base);
  l_status = f_stc_connectserver (pc_server,l_port, &l_chan, ps_tcpcli);
  if(l_status != STC__SUCCESS) {l_status=COMM__NOSERVER; goto g_return;}
  l_status = f_stc_write(&s_his_comm_cli,sizeof(s_his_comm),l_chan);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_status = f_stc_read (&s_his_comm_cli,sizeof(s_his_comm),l_chan,-1);
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}
  l_swap = (s_his_comm_cli.lu_endian > 1);
  if(l_swap) { l_status = f_swaplw((INTS4*)&s_his_comm_cli,5,NULL); }
  if(s_his_comm_cli.l_status != COMM__SUCCESS) {l_status=s_his_comm_cli.l_status; goto g_return;}

  l_size=s_his_comm_cli.lu_size-sizeof(s_his_head);
  /* allocate buffer */
  if(*p_buffer == 0) {
    pl_all  = (INTS4*)malloc(l_size);
    *p_buffer = pl_all;
  } else {
    if(*pl_size < l_size) {l_status=COMM__ERROR; goto g_return;}
    pl_all = *p_buffer;
  }
  /* allocate header buffer */
  if(*p_head == 0) {
    ps_his_head = (s_his_head*)malloc(sizeof(s_his_head));
    *p_head = ps_his_head;
  } else { ps_his_head = *p_head; }

  l_status = f_stc_read (ps_his_head,sizeof(s_his_head),l_chan,-1);
  if(l_swap) { l_status = f_swaplw((INTS4*)ps_his_head,16,NULL); }

  *pl_size = l_size;
  l_buffer = l_size;

  /* break total buffer in TCP buffers */
  pl_l=pl_all;
  i_l=l_buffer/16384;
  l_buffer=l_buffer%16384;
  for(i_j=0; i_j<i_l; i_j++) {l_status = f_stc_read (pl_l,16384,l_chan,-1); pl_l+=4096;}
  if(l_buffer > 0) { l_status = f_stc_read (pl_l,l_buffer,l_chan,-1); }
  if(l_status != STC__SUCCESS) {l_status=COMM__ERROR; goto g_return;}

  if(l_swap) { l_status = f_swaplw((INTS4*)pl_all,l_size/4,NULL); }

  l_status=COMM__SUCCESS;
g_return:
  f_stc_discclient (l_chan);
  f_stc_close (ps_tcpcli);
  free(ps_tcpcli);
  return(l_status);
}
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_server                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_server(int *pl_port, char base, char accesss)*/
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Start histogram server                              */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+  pl_port    : Address to receive port number used.                */
/*+  base       : Base name                                           */
/*+  access     : Password                                            */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Creates histogram server.                           */
/*                Returns port number                                 */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_server(CHARS* pc_base, CHARS* pc_access, INTS4* pl_port)
{
  INTS4 /**pl_l,i_j,i_l,ll,l_buffer,*/l_status;

  ps_tcpserv  = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));
  l_gl_serv_port=PORT__HIST_SERV;
  strcpy(c_gl_serv_access,pc_access);
  strcpy(c_gl_serv_base,pc_base);
  f_his_toupper(c_gl_serv_access,sizeof(c_gl_serv_access));
  f_his_toupper(c_gl_serv_base,sizeof(c_gl_serv_base));

  while((l_status = f_stc_createserver (&l_gl_serv_port, ps_tcpserv)) != STC__SUCCESS) {
    l_gl_serv_port++;
    if(l_gl_serv_port > PORT__HIST_SERV + 20) {
      printf("Error creating histogram server\n");
      return(COMM__ERROR);
    }
  }
  *pl_port=l_gl_serv_port;
  return(0);
}

/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_wait                                          */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_wait(int *pl_action, char histogram)        */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Wait for client                                     */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+  pl_action  : Address to receive required action.                 */
/*+  histogram  : Histogram sepc.                                     */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOACCESS: Password wrong                      */
/*-               COMM__NOBASE  : Base wrong                          */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Waits for client to connect.                        */
/*                Returns action required.                            */
/*                Checks for correct base and password                */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_wait(INTS4* pl_action, CHARS* pc_histo)
{
  INTS4 /**pl_l,i_j,i_l,ll,l_buffer,*/l_status;
  /* Wait for client to connect */
  if(l_gl_serv_verb == 1) {printf("Waiting for client on port %d [%s] \n",l_gl_serv_port,c_gl_serv_access);}
  l_status = f_stc_acceptclient (ps_tcpserv, &l_gl_serv_chan);
  if(l_status != STC__SUCCESS) { printf("error accepting client\n"); return(COMM__ERROR);}
  if(l_gl_serv_verb == 1) {printf("Client connected. \n");}
  l_status = f_stc_read (&s_his_comm_serv,sizeof(s_his_comm),l_gl_serv_chan,-1);
  if(l_status != STC__SUCCESS) { printf("error reading client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR); }
  /* check access */
  f_his_toupper(s_his_comm_serv.c_access,sizeof(s_his_comm_serv.c_access));
  f_his_toupper(s_his_comm_serv.c_base,sizeof(s_his_comm_serv.c_base));
  if((strlen(c_gl_serv_access) != 0) &
      (strcmp(s_his_comm_serv.c_access,c_gl_serv_access) != 0)) {
    printf("Client connected with wrong password [%s]. \n",s_his_comm_serv.c_access);
    s_his_comm_serv.lu_endian=1;
    s_his_comm_serv.lu_size=0;
    s_his_comm_serv.lu_histos=0;
    s_his_comm_serv.l_status=COMM__NOACCESS;
    l_status = f_stc_write (&s_his_comm_serv,sizeof(s_his_comm), l_gl_serv_chan);
    f_stc_discclient (l_gl_serv_chan);
    return(COMM__NOACCESS);
  }
  /* check base name */
  if(strcmp(s_his_comm_serv.c_base,c_gl_serv_base) != 0) {
    printf("Client connected for wrong base [%s]. \n",s_his_comm_serv.c_base);
    s_his_comm_serv.lu_endian=1;
    s_his_comm_serv.lu_size=0;
    s_his_comm_serv.lu_histos=0;
    s_his_comm_serv.l_status=COMM__NOBASE;
    l_status = f_stc_write (&s_his_comm_serv,sizeof(s_his_comm), l_gl_serv_chan);
    f_stc_discclient (l_gl_serv_chan);
    return(COMM__NOBASE);
  }
  if(s_his_comm_serv.lu_endian > 100) { l_status = f_swaplw((INTS4*)&s_his_comm_serv,5,NULL); }
  if(l_gl_serv_verb == 1) {
    printf("%d: %d %d %d %d %d \"%s\" \"%s\" \"%s\"\n",l_status
           ,s_his_comm_serv.lu_endian
           ,s_his_comm_serv.lu_action
           ,s_his_comm_serv.lu_histos
           ,s_his_comm_serv.lu_size
           ,s_his_comm_serv.l_status
           ,s_his_comm_serv.c_access
           ,s_his_comm_serv.c_base
           ,s_his_comm_serv.c_histo);
  }
  *pl_action=s_his_comm_serv.lu_action;
  strcpy(pc_histo,s_his_comm_serv.c_histo);
  return(COMM__SUCCESS);
}

/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_senddir                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_senddir(s_his_head *ps_head, int l_histos)  */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Send list of available histogram                    */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+  ps_head    : Address of header list.                             */
/*+  l_histos   : Number of histograms                                */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOHIST  : Histogram not there                 */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Send list of s_his_head to client.                  */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_senddir(s_his_head* ps_head, INTS4 l_histos)
{
  INTS4* pl_l,i_j,i_l,/*ll,*/l_buffer,l_status;

  if(l_gl_serv_verb == 1) {printf("Send directory %s. \n",s_his_comm_serv.c_histo);}
  s_his_comm_serv.lu_histos=l_histos;
  s_his_comm_serv.lu_endian=1;
  s_his_comm_serv.lu_action=COMM__PUTDIR;
  s_his_comm_serv.lu_size=sizeof(s_his_head)*s_his_comm_serv.lu_histos;
  s_his_comm_serv.l_status=COMM__SUCCESS;
  l_status = f_stc_write (&s_his_comm_serv,sizeof(s_his_comm), l_gl_serv_chan);
  if(l_status != STC__SUCCESS)
    { printf("error writing comm to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR);}

  /* break total buffer in TCP buffers */
  pl_l=(INTS4*)ps_head;
  l_buffer = s_his_comm_serv.lu_size;
  i_l=l_buffer/16384;
  l_buffer=l_buffer%16384;
  for(i_j=0; i_j<i_l; i_j++) {l_status = f_stc_write (pl_l,16384,l_gl_serv_chan); pl_l+=4096;}
  if(l_buffer > 0) { l_status = f_stc_write (pl_l,l_buffer,l_gl_serv_chan); }

  if(l_status != STC__SUCCESS)
    { printf("error writing directory to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR);}
  f_stc_discclient (l_gl_serv_chan);
  return(COMM__SUCCESS);
}
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_sendhis                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_sendhis(s_his_head *ps_head, int histos, char *histo, int *data)*/
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Send histogram                                      */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+  ps_head    : Address of header list.                             */
/*+  histos     : Number of histograms                                */
/*+  histo      : Name of requested histograms                        */
/*+  data       : Pointer array to histogram data                     */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*-               COMM__NOHIST  : Histogram not there                 */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Send one s_his_head and data to client.             */
/*                Histogram is searched by name.                      */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_sendhis(s_his_head* ps_head, INTS4 l_histos, CHARS* pc_histo, INTS4* pl_data)
{
  s_his_head* ps_his_head;
  INTS4* pl_l,i_j,i_l,ll,l_buffer,l_status;

  s_his_comm_serv.lu_endian=1;
  s_his_comm_serv.lu_histos=0;
  s_his_comm_serv.lu_action=COMM__PUTHIST;
  ps_his_head = ps_head;
  for(ll=0; ll<l_histos; ll++) {
    pl_l = pl_data;
    if(strcmp(ps_his_head->c_name,pc_histo) == 0) {
      s_his_comm_serv.lu_histos=1;
      s_his_comm_serv.l_status=COMM__SUCCESS;
      s_his_comm_serv.lu_size=sizeof(s_his_head)+ps_his_head->l_bins_1 * ps_his_head->l_bins_2 * 4;
      l_status = f_stc_write (&s_his_comm_serv,sizeof(s_his_comm), l_gl_serv_chan);
      if(l_status != STC__SUCCESS)
        { printf("error writing comm to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR);}
      if(l_gl_serv_verb == 1) {printf("%-32s %8ld\n",ps_his_head->c_name,s_his_comm_serv.lu_size-sizeof(s_his_head));}
      l_status = f_stc_write (ps_his_head,sizeof(s_his_head), l_gl_serv_chan);
      if(l_status != STC__SUCCESS)
        { printf("error writing header to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR); }

      /* break total buffer in TCP buffers */
      l_buffer = s_his_comm_serv.lu_size-sizeof(s_his_head);
      i_l=l_buffer/16384;
      l_buffer=l_buffer%16384;
      for(i_j=0; i_j<i_l; i_j++) {l_status = f_stc_write (pl_l,16384,l_gl_serv_chan); pl_l+=4096;}
      if(l_buffer > 0) { l_status = f_stc_write (pl_l,l_buffer,l_gl_serv_chan); }
      if(l_status != STC__SUCCESS)
        { printf("error writing data to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR); }
      break;
    } /* found */
    ps_his_head++;
  } /* loop */
  if(s_his_comm_serv.lu_histos == 0) {
    if(l_gl_serv_verb == 1) {printf("Histogram %s not found\n",pc_histo);}
    s_his_comm_serv.l_status=COMM__NOHIST;
    s_his_comm_serv.lu_size=0;
    l_status = f_stc_write (&s_his_comm_serv,sizeof(s_his_comm), l_gl_serv_chan);
    if(l_status != STC__SUCCESS)
      { printf("error writing comm to client\n"); f_stc_discclient(l_gl_serv_chan); return(COMM__ERROR); }
    f_stc_discclient (l_gl_serv_chan);
    return(COMM__NOHIST);
  }
  f_stc_discclient (l_gl_serv_chan);
  return(COMM__SUCCESS);
}
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_his_close                                         */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l=f_his_close()                                     */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Stop server, close sockets                          */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ Return type : int.                                                */
/*-               COMM__SUCCESS : OK                                  */
/*-               COMM__ERROR   : Error                               */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ FUNCTION    : Stop server, close sockets .                        */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ File name   : f_his_hist.c                                        */
/*+ Version     : 1.01                                                */
/*+ Author      : Hans Essel                                          */
/*+ Created     : 21-May-2000                                         */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*1- C Main ****************+******************************************/
INTS4 f_his_close()
{
  printf("Exit histogram server\n");
  f_stc_close (ps_tcpserv);
  free(ps_tcpserv);
  return(COMM__SUCCESS);
}
