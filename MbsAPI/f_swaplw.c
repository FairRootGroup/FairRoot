/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
#define DEBUG 0
/*2+F_SWAPLW****+******************************************************/
/*                                                                    */
/*+ Module      : F_SWAPLW                                            */
/*                                                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : sts = f_swaplw(pp_source,                           */
/*                               l_len,                               */
/*                               pp_dest)                             */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Long word byte swap.                                */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*+    pp_source   : Pointer to source.                               */
/*+    l_dest      : length (in long words)                           */
/*+    pp_dest     : Pointer to destination or 0 if                   */
/*                   destination = source.                            */
/*                                                                    */
/*+ FUNCTION    : Long word byte swap. Works on the source field if   */
/*                pp_dest points to value 0 or swaps from the source  */
/*                to the destination field.                           */
/*                (Should be replaced by a fast assembler routine)    */
/*                                                                    */
/*+ Return type : int (see s_errnum_def.h)                            */
/*+ Status codes: bit 0: success                                      */
/*                                                                    */
/*+ Initialize  : -                                                   */
/*+ Include name: -                                                   */
/*                                                                    */
/*3+Implementation************+****************************************/
/*                                                                    */
/*+ File name   : PC_PROC.C                                           */
/*+ Version     : 1.01                                                */
/*+ Author      : R.S. Mayer                                          */
/*+ Last Update : 27-Apr-1994                                         */
/*+ Object libr.: ?                                                   */
/*3+Updates*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date          Purpose                               */
/*                                                                    */
/*3+Description***+***********+****************************************/
/*1- C Procedure ***********+******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* function prototypes */

/* defines */

int f_swaplw(int* pp_source, int l_len, int* pp_dest)

{
  unsigned char*     p_source, *p_dest, *p_s, *p_d;
  unsigned int      lu_save;

  /* +++ action +++ */
  p_source = (unsigned char*) pp_source;
  p_dest   = (unsigned char*) pp_dest;

  if (p_dest == NULL) {
    /* source == destination          */
    for (p_d = (unsigned char*) p_source,
         p_s = (unsigned char*) &lu_save;
         p_d < p_source + (l_len * 4);
        ) {
      lu_save = *( (int*) p_d);
      p_s    += 4;                 /* increment source               */
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
    }
  } else {
    for (p_s = (unsigned char*) p_source,
         p_d = (unsigned char*) p_dest;
         p_s < p_source + (l_len * 4);
         p_s += 4) {
      p_s     += 4;                /* increment source               */
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
      *(p_d++) = *(--p_s);
    }

  }  /* dest == 0 */

  return(0);
}

