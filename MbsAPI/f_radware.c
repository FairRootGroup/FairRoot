/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include "f_radware.h"
#include "typedefs.h"

#ifdef GSI__WINNT
#include <errno.h>
#else
#include <errno.h>
#include <unistd.h>
#endif

#define HIS__BASPERM   0774
//*************************************************************
int f_radware_out1d(char* pc_file, char* pc_name, float* pr_data, int l_chan, int l_over)
{
//  char c_retmsg[128];
  int  i32_fd, i32_bytes, i32_hislen;
  int  l_status,/*ll,*/l_head[6];//,l_bytes;
  char /**pc,*/c_str[128];

  if(l_over) { // delete old file
    strcpy(c_str,"rm ");
    strcat(c_str,pc_file);
    system(c_str);
  }
  i32_fd = open(pc_file, O_WRONLY | O_CREAT | O_EXCL, HIS__BASPERM);
  if (i32_fd < 0) {
    printf("Error %d opening file %s, already exists?\n",errno, pc_file);
    return(1);
  }
//write file
  strcpy(c_str,pc_name);
  strcat(c_str,"        ");
  l_head[0]=24;
  l_head[1]=1;
  l_head[2]=1;
  l_head[3]=1;
  l_head[4]=24;
  l_head[5]=l_chan*4; /* record size */

  i32_bytes   = write(i32_fd, (char*) l_head, 4);
  i32_bytes  += write(i32_fd, c_str, 8);
  l_head[0]   = l_chan;
  i32_bytes  += write(i32_fd, (char*) l_head, 24);  /* includes record size */

  i32_bytes  += write(i32_fd, (char*) pr_data, l_chan*4);
  l_head[0]   = l_chan*4;
  i32_bytes  += write(i32_fd, (char*) l_head, 4);

  i32_hislen = l_chan*4 + 40;
  if (i32_bytes == i32_hislen) {
    //  printf("Histogram %32s: %d bytes (data %d) written to %s\n",
    //     pc_name,i32_bytes,l_chan*4,pc_file);
  } else {
    printf("Error %d. Dumping histogram:%s, %d bytes written to %s\n",
           errno,pc_name,i32_bytes,pc_file);
  }
  l_status = close(i32_fd);
  if (l_status != 0) {
    printf("Error %d. Close %s failed!\n",errno,pc_file);
    return(1);
  }
  return(0);
}
//*************************************************************
int f_radware_out2d(char* pc_file, char* pc_name, int* pl_data, int l_chan, int l_over)
{
  int   i32_fd, i32_bytes;//, i32_hislen;
  int   l_status;//,ll,l_head[6],l_bytes;
  char /**pc,*/c_str[128];

  if(l_over) {
    strcpy(c_str,"rm ");
    strcat(c_str,pc_file);
    system(c_str);
  }
  i32_fd = open(pc_file, O_WRONLY | O_CREAT | O_EXCL, HIS__BASPERM);
  if (i32_fd < 0) {
    printf("Error %d opening file %s, already exists?\n",errno, pc_file);
    return(1);
  }
  i32_bytes  = write(i32_fd, (char*) pl_data, l_chan*4);
  if (i32_bytes == l_chan*4) {
    //  printf("Histogram %32s: %d bytes written to %s\n",
    //     pc_name,i32_bytes,pc_file);
  } else {
    printf("Error %d. Dumping histogram:%s, only %d bytes written to %s\n",
           errno,pc_name,i32_bytes,pc_file);
  }
  l_status = close(i32_fd);
  if (l_status != 0) {
    printf("Error %d. Close %s failed!\n",errno,pc_file);
    return(1);
  }
  return(0);
}
