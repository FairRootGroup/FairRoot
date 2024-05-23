// $Id: f_ut_utime.c 581 2010-02-18 12:49:52Z linev $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#include "f_ut_utime.h"

/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 52                                                */
/*   D-64220 Darmstadt                                                */
/*                                                                    */
/*1+ C Procedure *************+****************************************/
/*                                                                    */
/*+ Module      : f_ut_utime                                         */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : char * = f_ut_utime(l_sec,l_msec,char *pc_time)    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Returns date/time string in VMS format              */
/*                  day-month-year hours:min:sec.00                   */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+   l_sec     : Seconds as returned from ftime function             */
/*+   l_msec    : Milliseconds                                        */
/*+  pc_time    : Address of string (23 characters)                   */
/*                                                                    */
/*2+Implementation************+****************************************/
/*+ Utility     : util                                                */
/*+ File name   : f_ut_utime.c                                       */
/*+ Home direct.: path                                                */
/*+ Declaration : char *f_ut_utime(char *);                          */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Created     : 24-Mar-1994                                         */
/*+ Object libr.:                                                     */
/*+ Updates     : Date        Purpose                                 */
/*-               14-apr-97 : POSIX now OK on Lynx /HE                */
/*                            gcc -mposix4d9 -mthreads -DLynx         */
/*1- C Procedure *************+****************************************/
#ifdef Lynx
#include <sys/types.h>
#include <timeb.h>
#else
#include <sys/timeb.h>
#include <sys/types.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>

INTS4 f_ut_utime(INTS4 l_sec, INTS4 l_msec, CHARS* pc_time)
{

    //  time_t t_time;
    struct timeb tp;
    struct tm st_time;
    CHARS c_allmon[37] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    CHARS c_mon[4];
    CHARS* pc_mon;

    if (l_sec == 0) {
        strcpy(pc_time, "no valid date");
#ifdef VMS
        return (1);
#else
        return (0);
#endif
    }
    *pc_time = 0;
    ftime(&tp);
    if (l_sec > 0) {
        tp.time = l_sec;
        /*
    #ifdef VMS
        tp.time = l_sec + 7200;
    #endif
    */
#ifdef xxxLynx
        tp.time = l_sec + 86400; /* one day */
#endif
        tp.millitm = l_msec;
    }
#ifdef xxxLynx
    localtime_r(&st_time, &tp.time);
    if (st_time.tm_mon > 2 && st_time.tm_mon < 9) { /* daylight saving ? */
        tp.time += 3600;
        localtime_r(&st_time, &tp.time);
    }
#else
    st_time = *localtime(&tp.time);
#endif
    pc_mon = (CHARS*)&c_allmon;
    pc_mon += (st_time.tm_mon * 3);
    strncpy(c_mon, pc_mon, 3);
    c_mon[3] = '\0';
    if (st_time.tm_year < 100)
        sprintf(pc_time,
                "%02d-%s-19%02d %02d:%02d:%02d.%02d",
                st_time.tm_mday,
                c_mon,
                st_time.tm_year,
                st_time.tm_hour,
                st_time.tm_min,
                st_time.tm_sec,
                l_msec / 10);
    else
        sprintf(pc_time,
                "%02d-%s-20%02d %02d:%02d:%02d.%02d",
                st_time.tm_mday,
                c_mon,
                st_time.tm_year - 100,
                st_time.tm_hour,
                st_time.tm_min,
                st_time.tm_sec,
                l_msec / 10);
#ifdef VMS
    return (1);
#else
    return (0);
#endif
}
