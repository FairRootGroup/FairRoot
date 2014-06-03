/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* type definitions */
#include "typedefs.h"
#include "f_ut_compress.h"
#include <stdio.h>

#define PACK(bit)   if(*pc_in != 0){*pl_mask += bit ; *pc_out++ = *pc_in; }  pc_in++;

#ifdef GSI__LINUX
#define UNPACK(bit) if(l_mask & bit ) *pc_out++ = *pc_in++; else *pc_out++ = 0;
#endif
#ifdef GSI__NT
#define UNPACK(bit) if(l_mask & bit ) *pc_out++ = *pc_in++; else *pc_out++ = 0;
#endif
#ifdef GSI__WINNT
#define UNPACK(bit) if(l_mask & bit ) *pc_out++ = *pc_in++; else *pc_out++ = 0;
#endif
#ifdef GSI__VMS
#define UNPACK(bit) if(l_mask & bit ) *pc_out = *pc_in++; pc_out++;
#endif
#ifdef GSI__AIX
#define UNPACK(bit) if(l_mask & bit ) *pc_out = *pc_in++; pc_out++;
#endif
#ifdef GSI__SOLARIS
#define UNPACK(bit) if(l_mask & bit ) *pc_out = *pc_in++; pc_out++;
#endif
#ifdef GSI__LYNX
#define UNPACK(bit) if(l_mask & bit ) *pc_out = *pc_in++; pc_out++;
#endif
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_ut_compr_size                                     */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : size=f_ut_compr_size(*input,inlen)                  */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : return size of compressed data field.               */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+    input    : (INTU1 *) Pointer to data field.                    */
/*+    inlen    : (INTS4) Length of input data field [bytes].         */
/*                                                                    */
/*+ Return type : INTS4                                               */
/*+    return   : Number of bytes of compressed output                */
/*+ Include name: f_ut_compress.h                                     */
/*                                                                    */
/*2+Implementation************+****************************************/
/*                                                                    */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Last Update : 13-Jul-2000                                         */
/*                                                                    */
/*2+Internals*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : UTIL                                                */
/*+ Created     : 07-Jul-2000                                         */
/*                                                                    */
/*1- C Procedure ***********+******************************************/
INTS4 f_ut_compr_size(INTU1* pc_input,INTS4 l_inlen)
{
 // INTU4 I,J,K,L,M,N;
  INTU4 l_bytes;
  INTU4 l_masks;
  INTU4* pl_mask,*pl_end;
  INTU1* *pc_in;
//  s_compress*  ps_compress;

  pc_in = &pc_input;
  l_bytes=0;
  pl_mask=(INTU4*)pc_input;
  pl_end=pl_mask+l_inlen/4;
  while(pl_mask!=pl_end) {
    if(*pl_mask&0x000000ff) { l_bytes++; }
    if(*pl_mask&0x0000ff00) { l_bytes++; }
    if(*pl_mask&0x00ff0000) { l_bytes++; }
    if(*pl_mask&0xff000000) { l_bytes++; }
    pl_mask++;
  }
  if(l_bytes%4 != 0) { l_bytes=l_bytes+4-l_bytes%4; }
  l_masks=(l_inlen >> 5);
  if(l_inlen%32 != 0) { l_masks++; }
  return(l_bytes+4*l_masks+sizeof(s_compress));
}

/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_ut_compr_zeros                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : zeros=f_ut_compr_zeros(*input,inlen)                */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : return % zero bytes.                                */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+    input    : (INTU1 *) Pointer to data field.                    */
/*+    inlen    : (INTS4) Length of input data field [bytes].         */
/*                                                                    */
/*+ Return type : INTS4                                               */
/*+    return   : % of zero bytes                                     */
/*+ Include name: f_ut_compress.h                                     */
/*                                                                    */
/*2+Implementation************+****************************************/
/*                                                                    */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Last Update : 13-Jul-2000                                         */
/*                                                                    */
/*2+Internals*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : UTIL                                                */
/*+ Created     : 07-Jul-2000                                         */
/*                                                                    */
/*1- C Procedure ***********+******************************************/
INTS4 f_ut_compr_zeros(INTU1* pc_input,INTS4 l_inlen)
{
  INTU4 I;
  INTU4 l_bytes;
  INTU1* *pc_in;

  pc_in = &pc_input;
  l_bytes=0;
  for(I=1; I<=l_inlen; I++) if(*pc_in++ == 0) { l_bytes++; }
  return (l_bytes*100/l_inlen);
}

/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_ut_compr_pack                                     */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : size=f_ut_compr_pack(*input,inlen,*output,outlen)   */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Compress data field by removing zero bytes          */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+    input    : (INTU1 *) Pointer to input data field.              */
/*+    inlen    : (INTS4) Length of input data field in bytes.        */
/*+    output   : (INTU1 *) Pointer to compressed output data field.  */
/*+    outlen   : (INTS4) Length of output data field.                */
/*                                                                    */
/*+ Return type : INTS4                                               */
/*+    return   : Number of bytes of compressed output                */
/*+    return   : -1: output buffer may be too small                  */
/*+ Include name: f_ut_compress.h                                     */
/*                                                                    */
/*2+Description***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : size=f_ut_compr_pack(*input,inlen,*output,outlen)   */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+    input    : (INTU1 *) Pointer to input data field. The field    */
/*                must be longword aligned.                           */
/*+    inlen    : (INTS4) Length of input data field in bytes.        */
/*+    output   : (INTU1 *) Pointer to output data field.             */
/*                The output field must be 12.5% bigger than input.   */
/*+    outlen   : (INTS4) Length of output data field in bytes.       */
/*                                                                    */
/*+ FUNCTION    : The output field begins with structure s_compress:  */
/*                                                                    */
/*-               INTU4 l_endian:     set to 1 by creator             */
/*-               INTU4 l_length:     total size [b] of compr. buffer */
/*-               INTU4 l_masks:      # of masks following this header */
/*-               INTU4 l_full_bytes: # of bytes of uncompressed buffer */
/*-               INTU4 l_comp_bytes: # of non zero bytes             */
/*-               INTU4 l_pattern:    COMPR__PATTERN                  */
/*+ :                                                                  */
/*                Then there follow inbytes/32 pattern longwords.     */
/*                Then follow all non zero bytes.                     */
/*                Zero bytes are suppressed. The overhead is about    */
/*                13% of input, i.e. if no zeros are found, output is */
/*                13% bigger than input. In the patterns, bits are    */
/*                set for following nonzero bytes, not set for        */
/*                suppressed zero bytes.                              */
/*+  endian     : When receiving a compressed buffer one must check   */
/*                the endian. If it is not 1, one must swap           */
/*                s_compress and then s_sompress.l_masks longwords.   */
/*                Then the buffer can be uncompressed. The            */
/*                uncompressed buffer must be checked again for right */
/*                endian, and eventually swapped.                     */
/*                                                                    */
/*+ EXAMPLE     : l=f_ut_compr_pack(pl_data,1024,pl_comp,2000);       */
/*                l=f_ut_compr_unpack(pl_comp,pl_data,1024);          */
/*                pl_data should be the same now.                     */
/*                                                                    */
/*+ NOTE        : Output data field must be 13% bigger than input.    */
/*                                                                    */
/*2+Implementation************+****************************************/
/*                                                                    */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Last Update : 13-Jul-2000                                         */
/*                                                                    */
/*2+Internals*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : UTIL                                                */
/*+ Created     : 07-Jul-2000                                         */
/*                                                                    */
/*1- C Procedure ***********+******************************************/
INTS4 f_ut_compr_pack(INTU1* pc_input,INTS4 l_inlen,INTU1* pc_output,INTS4 l_outlen)
{
  INTU4 I;//,J,K,M,N;
  INTU4 l_bytes;
  INTU4 l_mask,l_masks;
  INTU4* pl_mask;
  INTU1* pc_out,*pc_in,*pc_1;
  s_compress*  ps_compress;

  /* how many masks do we need: one for 32 bytes */
  l_masks=(l_inlen >> 5);
  if(l_inlen%32 != 0) { l_masks++; }
  /* on output we need the header, the masks, and maybe all bytes */
  if(l_outlen < 4*l_masks+sizeof(s_compress)+l_inlen) { return -1; }
  pc_out=pc_output;
  pc_in =pc_input;
  ps_compress=(s_compress*)pc_out;    /* header */
  pl_mask=(INTU4*)(ps_compress+1);    /* first mask behind header */
  pc_out = (INTU1*)(pl_mask+l_masks); /* first data byte behind all masks */
  pc_1=pc_out;
  *pl_mask=0;
  l_mask=1;
  l_bytes=0;
  /* loop over all masks -1 */
  for(I=1; I<l_masks; I++) {
    PACK(0x00000001);
    PACK(0x00000002);
    PACK(0x00000004);
    PACK(0x00000008);
    PACK(0x00000010);
    PACK(0x00000020);
    PACK(0x00000040);
    PACK(0x00000080);
    PACK(0x00000100);
    PACK(0x00000200);
    PACK(0x00000400);
    PACK(0x00000800);
    PACK(0x00001000);
    PACK(0x00002000);
    PACK(0x00004000);
    PACK(0x00008000);
    PACK(0x00010000);
    PACK(0x00020000);
    PACK(0x00040000);
    PACK(0x00080000);
    PACK(0x00100000);
    PACK(0x00200000);
    PACK(0x00400000);
    PACK(0x00800000);
    PACK(0x01000000);
    PACK(0x02000000);
    PACK(0x04000000);
    PACK(0x08000000);
    PACK(0x10000000);
    PACK(0x20000000);
    PACK(0x40000000);
    PACK(0x80000000);
    pl_mask++;
    *pl_mask=0;
  }
  l_bytes=pc_out-pc_1 ;
  /* last mask could be less than 32 bytes */
  l_mask=1;
  for(I=0; I<(l_inlen-l_masks*32+32); I++) {
    if(*pc_in != 0) {*pl_mask += l_mask; *pc_out++ = *pc_in; l_bytes++; }
    l_mask = l_mask << 1;
    pc_in++;
  }
  /* add the number of last fragment bytes */
  ps_compress->l_endian     = 1;
  ps_compress->l_length     = l_bytes+4*l_masks+sizeof(s_compress);
  ps_compress->l_pattern    = COMPR__PATTERN;
  ps_compress->l_masks      = l_masks;
  ps_compress->l_full_bytes = l_inlen;
  ps_compress->l_comp_bytes = l_bytes; /* without header and masks */

  return (l_bytes+4*l_masks+sizeof(s_compress));
}

/*1+ C Procedure ***********+******************************************/
/*                                                                    */
/*+ Module      : f_ut_compr_unpack                                   */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : size=f_ut_compr_unpack(*input,*output,outlen)       */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : Deompress data field.                               */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+    input    : (INTU1 *) Pointer to compressed data field.         */
/*+    output   : (INTU1 *) Pointer to uncompressed output data field.*/
/*+    outlen   : (INTS4) Length of output data field.                */
/*                                                                    */
/*+ Return type : INTS4                                               */
/*+    return   : 0 : OK                                              */
/*+    return   : -1: output buffer may be too small                  */
/*+ Include name: f_ut_compress.h                                     */
/*                                                                    */
/*2+Description***************+****************************************/
/*                Receiving a compressed buffer which could have      */
/*                a different endian, proceed as follows:             */
/*                Receive sizeof(s_compress) bytes and check          */
/*                s_compress.l_endian. If not 1 swap s_compress.      */
/*                Get s_compress.l_length-sizeof(s_compress) bytes.   */
/*                Swap next s_compress.l_masks longwords.             */
/*                Call f_ut_compr_unpack to compress the buffer.      */
/*                The uncompressed buffer must be checked for correct */
/*                endian again. The method is up to the sender.       */
/*                                                                    */
/*2+Implementation************+****************************************/
/*                                                                    */
/*+ Version     : 1.01                                                */
/*+ Author      : H.G.Essel                                           */
/*+ Last Update : 13-Jul-2000                                         */
/*                                                                    */
/*2+Internals*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : UTIL                                                */
/*+ Created     : 07-Jul-2000                                         */
/*                                                                    */
/*1- C Procedure ***********+******************************************/
INTS4 f_ut_compr_unpack(INTU1* pc_input,INTU1* pc_output,INTS4 l_outlen)
{
  INTU4 L;//,I,J,K,M,N;
  INTU4 l_mask;
  INTU4* pl_mask;//,*pl_tmp,*pl_out;
  INTU1* pc_out,*pc_in;
  s_compress*  ps_compress;

  ps_compress=(s_compress*)pc_input;
  /* is output buffer big enough?  */
  if(ps_compress->l_full_bytes > l_outlen) { return -1; }

#ifdef GSI__VMS
  pl_out=(INTU4*) pc_output;
  pl_tmp=pl_out+(ps_compress->l_full_bytes>>2);
  while(pl_out != pl_tmp) { *pl_out++ = 0; }
#endif
#ifdef GSI__LYNX
  pl_out=(INTU4*) pc_output;
  pl_tmp=pl_out+(ps_compress->l_full_bytes>>2);
  while(pl_out != pl_tmp) { *pl_out++ = 0; }
#endif
#ifdef GSI__AIX
  memset(pc_output,0,ps_compress->l_full_bytes);
#endif

  pl_mask=(INTU4*)(ps_compress+1);
  pc_in = (INTU1*)(pl_mask+ps_compress->l_masks);
  pc_out=pc_output;
  /* all masks -1 */
  for(L=1; L<ps_compress->l_masks; L++) {
    l_mask=*pl_mask;
    UNPACK(0x00000001);
    UNPACK(0x00000002);
    UNPACK(0x00000004);
    UNPACK(0x00000008);
    UNPACK(0x00000010);
    UNPACK(0x00000020);
    UNPACK(0x00000040);
    UNPACK(0x00000080);
    UNPACK(0x00000100);
    UNPACK(0x00000200);
    UNPACK(0x00000400);
    UNPACK(0x00000800);
    UNPACK(0x00001000);
    UNPACK(0x00002000);
    UNPACK(0x00004000);
    UNPACK(0x00008000);
    UNPACK(0x00010000);
    UNPACK(0x00020000);
    UNPACK(0x00040000);
    UNPACK(0x00080000);
    UNPACK(0x00100000);
    UNPACK(0x00200000);
    UNPACK(0x00400000);
    UNPACK(0x00800000);
    UNPACK(0x01000000);
    UNPACK(0x02000000);
    UNPACK(0x04000000);
    UNPACK(0x08000000);
    UNPACK(0x10000000);
    UNPACK(0x20000000);
    UNPACK(0x40000000);
    UNPACK(0x80000000);
    pl_mask++;
  }
  l_mask=*pl_mask;
  /* restore bytes of last mask (could be less than 32) */
  for(L=0; L<ps_compress->l_full_bytes-ps_compress->l_masks*32+32; L++) {
    if(l_mask%2 != 0) { *pc_out++ = *pc_in++; }
    else { *pc_out++=0; }
    l_mask = l_mask >> 1;
  }
  return 0;
}
