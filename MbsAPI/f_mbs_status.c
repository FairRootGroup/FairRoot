/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include "sbs_def.h"
#include "sys_def.h"
#include "ml_def.h"
#include "portnum_def.h"
#include "s_daqst.h"
#include "s_setup.h"
#include "s_set_ml.h"
#include "s_set_mo.h"
#include "f_stccomm.h"
#include "f_ut_status.h"

long l_gl_tcp_chan;

int l_status,l;

#define VERSION__DAQST  2
#define VERSION__SETUP  1
#define VERSION__SET_ML 1
#define VERSION__SET_MO 1

/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_mbs_status                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status=f_mbs_status(s_daqst, socket)             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read s_daqst from socket.                           */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+  s_daqst    : pointer to s_daqst                                  */
/*+  socket     : Tcp socket from connect                             */
/*1- C Procedure *************+****************************************/
INTS4 f_mbs_status(CHARS* c_node, s_daqst* ps_daqst)
{
  struct s_tcpcomm* ps_tcpcomm;

  ps_tcpcomm = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    return(-2);
  }
  l_status = f_ut_status_r (ps_daqst, l_gl_tcp_chan);
  f_stc_discclient (l_gl_tcp_chan);
  free(ps_tcpcomm);
  return l_status;
}


/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_mbs_setup                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status=f_mbs_setup(s_setup, socket)              */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read s_setup from socket.                           */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+  s_setup    : pointer to s_setup                                  */
/*+  socket     : Tcp socket from connect                             */
/*1- C Procedure *************+****************************************/
INTS4 f_mbs_setup(CHARS* c_node, s_setup* ps_setup)
{
  s_daqst* ps_daqst;
  struct s_tcpcomm* ps_tcpcomm;

  ps_tcpcomm = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    return(-2);
  }
  ps_daqst   = (s_daqst*) malloc (sizeof( s_daqst));
  l_status = f_ut_status_r (ps_daqst, l_gl_tcp_chan);
  f_stc_discclient (l_gl_tcp_chan);
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    free(ps_daqst);
    return(-1);
  }
  if(ps_daqst->bh_setup_loaded == 0) { l_status=-3; }
  else { l_status = f_ut_setup_r (ps_setup, l_gl_tcp_chan); }
  f_stc_discclient (l_gl_tcp_chan);
  free(ps_daqst);
  free(ps_tcpcomm);
  return l_status;
}


/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_mbs_ml_setup                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status=f_mbs_ml_setup(s_set_ml, socket)            */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read s_set_ml from socket.                          */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+  s_set_ml   : pointer to s_set_ml                                 */
/*+  socket     : Tcp socket from connect                             */
/*1- C Procedure *************+****************************************/
INTS4 f_mbs_ml_setup(CHARS* c_node, s_set_ml* ps_set_ml)
{
  s_daqst* ps_daqst;
  struct s_tcpcomm* ps_tcpcomm;

  ps_tcpcomm = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    return(-2);
  }
  ps_daqst   = (s_daqst*) malloc (sizeof( s_daqst));
  l_status = f_ut_status_r (ps_daqst, l_gl_tcp_chan);
  f_stc_discclient (l_gl_tcp_chan);
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    free(ps_daqst);
    return(-1);
  }
  if(ps_daqst->bh_set_ml_loaded == 0) { l_status=-3; }
  else { l_status = f_ut_set_ml_r (ps_set_ml, l_gl_tcp_chan); }
  f_stc_discclient (l_gl_tcp_chan);
  free(ps_tcpcomm);
  free(ps_daqst);
  return l_status;
}
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_mbs_mo_setup                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status=f_mbs_mo_setup(s_set_mo, socket)            */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Read s_set_mo from socket.                          */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+  s_set_mo   : pointer to s_set_mo                                 */
/*+  socket     : Tcp socket from connect                             */
/*1- C Procedure *************+****************************************/
INTS4 f_mbs_mo_setup(CHARS* c_node, s_set_mo* ps_set_mo)
{
  s_daqst* ps_daqst;
  struct s_tcpcomm* ps_tcpcomm;

  ps_tcpcomm = (struct s_tcpcomm*) malloc (sizeof( struct s_tcpcomm));
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    return(-2);
  }
  ps_daqst   = (s_daqst*) malloc (sizeof( s_daqst));
  l_status = f_ut_status_r (ps_daqst, l_gl_tcp_chan);
  f_stc_discclient (l_gl_tcp_chan);
  l_status = f_stc_connectserver (c_node,PORT__STAT_SERV,&l_gl_tcp_chan,ps_tcpcomm);
  if (l_status != STC__SUCCESS) {
    free(ps_tcpcomm);
    free(ps_daqst);
    return(-1);
  }
  if(ps_daqst->bh_set_mo_loaded == 0) { l_status=-3; }
  else { l_status = f_ut_set_mo_r (ps_set_mo, l_gl_tcp_chan); }
  f_stc_discclient (l_gl_tcp_chan);
  free(ps_tcpcomm);
  free(ps_daqst);
  return l_status;
}
