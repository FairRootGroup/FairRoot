/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/*  CLNT_BUF_DEF.H
 *
 *  definitions MUST be EQUAL for GPS-Server, GPS-Client and SBS-Monitor
 *  modif: 24-Feb-1994 RSM  CLNT__BUFHEAD
 *
 */
/* +++ length in bytes +++ */
#define CLNT__OUTBUFHEAD   344                  /* header length (300) inluding
* CLNT_INFO_CONTROL and
* CLNT_INFO_CLIENT
* but without *p_clntoutbuf[2]
* and *p_client. Data trans-
* mission starts at l_dlen
*/
#define CLNT__INFO_CONTROL  24                    /* len of info from
* s_control to be copied to
* s_clntoutbuf
*/
#define CLNT__INFO_CLIENT   20                    /* len of info from
* s_client  to be copied to
* s_clntoutbuf
*/
#define CLNT__SMALLBUF     512                  /* size of smallest buffer
* to be sent
*/
#define CLNT__RESTBUF      168                  /* begin of rest buffer addr
* is &p_clntoutbuf->
*    c_buffer[CLNT_RESTBUF]
* CLNT_RESTBUF =
  *      CLNT_SMALLBUF -
  *      CLNT_OUTBUFHEAD
  */
#define CLNT__BUFHEAD      336                  /* Header of output/input in
  * s_clntbuf and
  * s_clntoutbuf
  * from l_dlen to
  *      l_clntoutbuf_fltm
  */
#define CLNT__BUFH_LW       11                   /* Header from l_testbit
  *        to l_msgtyp in LW */
#define CLNT__MSGLEN       256                   /* Length of message string
  */
#define CLNT__REST_LW       11                   /* rest of header after
  * s_clntbuf.c_message[] to
  * s_clntbuf.c_buffer[0]
  */

