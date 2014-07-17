/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 52                                                */
/*   D-64220 Darmstadt                                               */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_ut_time                                     */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : CHARS * = f_ut_time(CHARS *)                          */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Returns date/time string in format                  */
/*                  day-month-year hours:min:sec                      */
/*                must be linked on Lynx with -X (=posix library)     */
/*                because of the time correction done.                */
/*                On VMS with /PREF=ALL                               */
/*                                                                    */
/*3+Function******+***********+****************************************/
/*                                                                    */
/*                Length of returned string is 17. No \n.             */
/*                                                                    */
/*3+Examples******+***********+****************************************/
/*                Description                                         */
/*2+Implementation************+****************************************/
/*+ Utility     : util                                                */
/*+ File name   : f_ut_time.c                                         */
/*+ Home direct.: path                                                */
/*+ Declaration : CHARS *f_ut_time(CHARS *);                            */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Created     : 24-Mar-1994                                         */
/*+ Object libr.:                                                     */
/*+ Updates     : Date        Purpose                                 */
/*-             : 03-apr-97 : support VMS, AIX, DECunix, Lynx         */
/*1- C Procedure *************+****************************************/
#ifdef Lynx
#include <types.h>
#include <timeb.h>
#else
#include <sys/types.h>
#include <sys/timeb.h>
#endif
#include <stdio.h>
#include <time.h>

CHARS*     f_ut_time (CHARS* pc_time)
{

//  time_t    t_time;
  struct timeb tp;
  struct tm st_time;

  ftime (&tp);

#ifdef Lynx
  /* Note: due to an error in POSIX Version of localtime, 1 day has to be */
  /* added to get the correct date. During daylight saving period 1 hour */
  /* has to be added additionaly                                         */
  tp.time+=86400; /* add 1 day */
  localtime_r(&st_time,&tp.time);
  if(st_time.tm_mon > 2 && st_time.tm_mon < 9) {  /* daylight saving ? */
    tp.time+=3600;
    localtime_r(&st_time,&tp.time);
  }
#else
  st_time=*localtime(&tp.time);
#endif

  strftime(pc_time,30,"%d-%h-%y %T",&st_time);
  return ((CHARS*) pc_time);
}
