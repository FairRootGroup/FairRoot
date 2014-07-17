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
/*   D-64220 Darmstadt                                               */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_his_toupper                                       */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_his_toupper(string,i_max)                         */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     :  Convert string to upper case.                      */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   string    : (char *) input/output                               */
/*                 pointer to character string                        */
/*                                                                    */
/*+   i_max     : int input                                           */
/*                 maximum number of char to be converted.            */
/*                                                                    */
/*+ Return type : void                                                */
/*                                                                    */
/*2+Description***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_his_tolower(string,i_max)                         */
/*                                                                    */
/*+ FUNCTION    : Converts string to upper case until '\0' or         */
/*                the specified maximum number of characters          */
/*                                                                    */
/*3+Function******+***********+****************************************/
/*                                                                    */
/*2+Implementation************+****************************************/
/*+ Utility     : f_his_toupper                                       */
/*+ File name   : f_his_toupper.c                                     */
/*+ Home direct.: /sbs/prod/src                                       */
/*+ Version     : 1.01                                                */
/*+ Author      : Ilya Kuznetsov                                      */
/*+ Created     : 20-Sep-1994                                         */
/*+ Object libr.: libxxx.a                                            */
/*+ Updates     : Date        Purpose                                 */
/*-               11-Oct-94 : changes/RSM                             */
/*1- C Procedure *************+****************************************/

#include <ctype.h>

#include "f_his_toupper.h"

void f_his_toupper(CHARS* c, INTS4 i)
/* +++ convert string to uppercase, max i char +++ */
{
  INTS4 i_j=0;
  while (!((c[i_j]=='\0') || (i_j==i))) {
    c[i_j]=(CHARS)toupper((INTS4)c[i_j]);
    i_j++;
  }
  c[i_j] = '\0';
}
