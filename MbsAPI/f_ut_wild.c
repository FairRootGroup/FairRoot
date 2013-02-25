// $Id: f_ut_wild.c 478 2009-10-29 12:26:09Z linev $
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

#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATCH    0
#define NOMATCH -1

INTS4 f_ut_wild(CHARS* pc_test, CHARS* pc_wild)
{
  INTS4 l_wild,l_test,l_len;
  CHARS c_wild[256],c_test[256];
  CHARS* pc_h,*pc_n,*pc_w,*pc_s;
  strcpy(c_wild,pc_wild);
  strcpy(c_test,pc_test);
  pc_w=(CHARS*)c_wild;
  pc_s=(CHARS*)c_test;
  l_test=strlen(pc_s);
  while(1) {
    while(*pc_w=='*') {
      while(*pc_w=='*') {pc_w++; if(*pc_w==0) { return MATCH; }}
      pc_h=pc_w;
      while((*pc_h!='*')&(*pc_h!=0)) { pc_h++; }
      if(*pc_h==0) {
        /* match pc_w at end of test */
        l_len=strlen(pc_w);
        if(strlen(pc_s) < l_len) { return NOMATCH; }
        pc_s=(CHARS*)&c_test[l_test-l_len];
      }
      if(*pc_h=='*') {
        /* match pc_w-pc_h somewhere in test */
        *pc_h=0;
        if((pc_n=(CHARS*)strstr(pc_s,pc_w))==NULL) { return NOMATCH; }
        l_len=strlen(pc_w);
        *pc_h='*';
        pc_w=pc_h;
        pc_s=pc_n+l_len;
      }
    }
    if((*pc_w!='%') & (*pc_w!=*pc_s)) { return NOMATCH; }
    pc_s++;
    pc_w++;
    if((*pc_s==0)&(*pc_w==0)) { return MATCH; }
    if(*pc_s==0) {
      if((*pc_w=='*') & (*(pc_w+1)==0)) { return MATCH; }
      return NOMATCH;
    }
    if(*pc_w==0) { return NOMATCH; }
  }
}
