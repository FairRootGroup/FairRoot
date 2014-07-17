/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 52                                                */
/*   D-64220 Darmstadt                                                */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_his_swpbas                                        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : l_status = f_his_swpbas(ps_head)                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Swaps whole base (except strings)                   */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   ps_head  : (s_head *) input                                     */
/*                 pointer to header structure, address of shared     */
/*                 segment.                                           */
/*+ Return type : int                                                 */
/*                                                                    */
/*2+Description***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : l_status = f_his_swpbas(ps_head)                    */
/*                                                                    */
/*+ FUNCTION    :                                                     */
/*                                                                    */
/*3+Function******+***********+****************************************/
/*                                                                    */
/*                                                                    */
/*                                                                    */
/*2+Implementation************+****************************************/
/*+ Utility     : f_his_swpbas                                        */
/*+ File name   : f_his_swpbas.c                                      */
/*+ Home direct.: /sbs/prod/src                                       */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Created     : 06-Jul-2000                                         */
/*+ Object libr.:                                                     */
/*+ Updates     : Date        Purpose                                 */
/*1- C Procedure *************+****************************************/

#include "f_his_swpbas.h"

#include <stdlib.h>
#include <stdio.h>
#include "s_spe.h"
#include "s_pol_cond.h"
#include "s_win_cond.h"
#include "f_swaplw.h"

INTS4 f_his_swpbas(s_head* ps_head)
{
  INTS4  i;
  s_spe*  ps_spe;
  s_win* ps_win;
  s_pol* ps_pol;
  INTS4*  *pl;

  /* swap first two LWs to get correct size */
  pl=(INTS4**)ps_head;
  f_swaplw(*pl,2,NULL);
  if(ps_head->l_endian != 1) {
    printf("endian was wrong %x\n",ps_head->l_endian);
    return(-1);
  }

  /* swap whole base */
  pl += 2;
  f_swaplw(*pl,ps_head->l_len-2,NULL);

  /* swap back strings in header */
  pl=(INTS4**)&ps_head->c_date;
  f_swaplw(*pl,23,NULL);

  /* swap back strings in all slots */
  ps_spe=(s_spe*)(ps_head+1);
  pl=(INTS4**)&ps_spe->c_name;
  for(i=0; i<ps_head->i_slot; i++) {
    f_swaplw(*pl,71,NULL);
    pl += (sizeof(s_spe)/4);
  }

  /* swap back strings in all conditions */
  if(ps_head->l_cond_win > 0) {
    pl=(INTS4**)ps_head;
    pl = pl + ps_head->l_cond_win;
    ps_win = (s_win*)(pl + 1);
    /*reswap window names */
    for(i=0; i< **pl; i++) {
      f_swaplw((INTS4*)ps_win->c_name,28,NULL);
      ps_win++;
    }
  }
  if(ps_head->l_cond_pol > 0) {
    pl=(INTS4**)ps_head;
    pl = pl + ps_head->l_cond_pol;
    ps_pol = (s_pol*)(pl + 1);
    /*reswap window names */
    for(i=0; i < **pl; i++) {
      f_swaplw((INTS4*)ps_pol->c_name,28,NULL);
      ps_pol++;
    }
  }
  return(0);
}

