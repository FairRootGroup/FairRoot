// $Id: m_histo_conv.c 478 2009-10-29 12:26:09Z linev $
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
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "f_ut_wild.h"
#include "f_his_hist.h"
#include "f_radware.h"
/**************************************************************************/
main(argc,argv)
int argc;
char* argv[];
{
  s_his_head* ps_his_head,*ps_his_head_dir;
  INTS4 i_j,ii,l_status,l_port,l_int;
  INTS4 l_size,l_histos=0;
  INTS4* pl_all,*pl_dir,*pl_l;
  REAL4* pr,*pr_l;
  CHARS* pc;
  CHARS c_server[32];
  CHARS c_histo[32];
  CHARS c_base[32];
  CHARS c_access[32];
  CHARS c_file[128];

  if(argc < 7) {
    printf("node port|6009 base password \"histogram\" [-print|-dir|-rad]\n");
    exit(0);
  }
  l_port=atol(argv[2]);
  strcpy(c_server,argv[1]);
  strcpy(c_access,argv[4]);
  strcpy(c_base,argv[3]);
  strcpy(c_histo,argv[5]);

  pl_all=NULL;
  /* get directory ******************************************************/
  if(strstr(argv[6],"-d") != NULL) {
    printf("Get directory %s from server %s [%d] pass=*** base=%s\n",
           c_histo,c_server,l_port,c_base);
    ps_his_head_dir=NULL;
    pl_dir=NULL;
    l_status = f_his_getdir(c_server,l_port,c_base,c_access,c_histo,(INTS4**)&pl_dir,(INTS4**)&l_histos);
    if(l_status == COMM__SUCCESS) {
      printf("Histograms: %d, slot size: %d b, Total: %d b\n",
             l_histos,sizeof(s_his_head),l_histos*sizeof(s_his_head));
      ps_his_head_dir = (s_his_head*)pl_dir;
      for(i_j=0; i_j<l_histos; i_j++) {
        if(f_ut_wild(ps_his_head_dir->c_name,c_histo)==0)
          printf("%-31s %s %8d %8d\n",
                 ps_his_head_dir->c_name,ps_his_head_dir->c_dtype,ps_his_head_dir->l_bins_1,ps_his_head_dir->l_bins_2);
        ps_his_head_dir++;
      }
    } else { printf("Error %d\n",l_status); }
    exit(0);
  }
  /* get histograms ******************************************************/
  printf("Lookup histograms %s at server %s [%d] pass=*** base=%s\n",
         c_histo,c_server,l_port,c_base);
  ps_his_head_dir=NULL;
  pl_dir=NULL;
  l_status = f_his_getdir(c_server,l_port,c_base,c_access,c_histo,(INTS4**)&pl_dir,(INTS4**)&l_histos);
  if(l_status != COMM__SUCCESS) {
    printf("Error %d getting histograms %s\n",l_status,c_histo);
    exit(0);
  }
  ps_his_head_dir = (s_his_head*)pl_dir;
  for(i_j=0; i_j<l_histos; i_j++) {
    if(f_ut_wild(ps_his_head_dir->c_name,c_histo)==0) {
      ps_his_head=NULL;
      pl_all=NULL;
      l_status = f_his_gethis(c_server,l_port,c_base,c_access,ps_his_head_dir->c_name,
                              (s_his_head**)&ps_his_head,(INTS4**)&pl_all,(INTS4**)&l_size);
      if(l_status != COMM__SUCCESS) {
        printf("Error %d getting histogram %s\n",l_status,ps_his_head_dir->c_name);
        exit(0);
      }

      /* process histogram ******************************************************/
      pl_l =         pl_all;
      pr_l =(REAL4*)pl_all;
      if(ps_his_head->c_dtype == 'i') { l_int=1; }
      else { l_int=0; }

      /* print histogram ******************************************************/
      if(strstr(argv[6],"-p") != NULL) {
        printf("Histogram %s\n",ps_his_head_dir->c_name);
        printf("          channels: %10d, total: %10d [b], %s %8d %8d\n",
               ps_his_head->l_bins_1*ps_his_head->l_bins_2,l_size,
               ps_his_head->c_dtype,ps_his_head->l_bins_1,ps_his_head->l_bins_2);
        /* print data channels */
        if(ps_his_head->l_bins_2 == 1) {
          for (i_j = 0; i_j < (ps_his_head->l_bins_1 - ps_his_head->l_bins_1 % 6); i_j += 6) {
            if(l_int) printf("%7d:%9d %9d %9d %9d %9d %9d\n",
                               i_j + 1,*pl_l,*(pl_l+1),*(pl_l+2),*(pl_l+3),*(pl_l+4),*(pl_l+5));
            else      printf("%7d:%11.4g %11.4g %11.4g %11.4g %11.4g %11.4g\n",
                               i_j + 1,*pr_l,*(pr_l+1),*(pr_l+2),*(pr_l+3),*(pr_l+4),*(pr_l+5));
            pl_l+=6;
            pr_l+=6;
          }
          if ((ps_his_head->l_bins_1 % 6)) {
            printf("%7d:",i_j + 1);
            for (i_j = ps_his_head->l_bins_1 - ps_his_head->l_bins_1 % 6; i_j < ps_his_head->l_bins_1; i_j++) {
              if(l_int) { printf("%9d ", *pl_l); }
              else { printf("%11.4g ", *pr_l); }
              pl_l++;
              pr_l++;
            }
            printf("\n");
          }
        } else { printf("2d Histograms %s not supported\n",ps_his_head_dir->c_name); }
      }
      /* dump radware histogram ******************************************************/
      if(strstr(argv[6],"-r") != NULL) {
        if(argc == 8) { strcpy(c_file,argv[7]); }
        else { strcpy(c_file,"rad_"); }
        strcat(c_file,ps_his_head_dir->c_name); // name from directory call includes path
        pc=c_file;
        for(ii=0; ii<strlen(c_file); ii++) {
          if(*pc == '/') { *pc='-'; }
          if(*pc == '(') { *pc='['; }
          if(*pc == ')') { *pc=']'; }
          if(*pc == ' ') { *pc='_'; }
          pc++;
        }
        strcat(c_file,".spe");
        if(ps_his_head->l_bins_2 == 1) {
          if(l_int == 0) {
            pr=(REAL4*) malloc(ps_his_head->l_bins_1*4);
            pr_l=pr;
            for(ii=0; ii<ps_his_head->l_bins_1; ii++) { *pr++=(REAL4)*pl_l++; }
          }
          l_status=f_radware_out1d(c_file,ps_his_head->c_name,pr_l,ps_his_head->l_bins_1,0);
          if(l_status == 0) { printf("Radware histogram %s written to file %s.\n",ps_his_head_dir->c_name,c_file); }
          else { printf("Radware histogram %s NOT written to file %s, ERROR!\n",ps_his_head_dir->c_name,c_file); }
          if(l_int == 0) { free(pr_l); }
        } else { printf("2d Histograms %s not supported\n",ps_his_head_dir->c_name); }
      }
      free(pl_all);
    }
    ps_his_head_dir++;
  }
}

