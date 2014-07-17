/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/* ++++++++++++++++++++++
 * +++ errnum_def.h +++
 * ++++++++++++++++++++++
 * RSMayer
 * 07-Feb-1994
 * error numbers
 * last modification:
 *   23-Mar-1994 RSMayer insert EVent_server error numbers
 *   25-Mar-1994 RSMayer ERR__SIGNAL, SETTASK, SETVERB, CLRVERB added.
 *   31-Mar-1994 RSMayer ERR__USBFTY, ERR__NKNBFTY.
 *   12-Jul-1994 RSMayer Error numbers and msg. for Esone Server
 *   16-Feb-1995 RSMayer new error numbers. /RSM
 *   08-Mar-1995 RSMayer some basic error number text modified.
*/
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !!!! error numbers MUST be changed in s_error.h TOO !!!! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/* !!! bit1:0 succes, bit1:1 error, i.e. odd numbers are errors! !!! */

/* +++ UTIlity      error numbers start with   0 +++ */
#define ERR__SUCCESS  0    /* Normal successfull completion && */
#define ERR__ERROR    1    /* Error: && */
/* */
#define ERR__INFO     2    /* && */ /* only text */
#define ERR__ERR      3    /* && */ /* only text */
#define ERR__WARN     4    /* Warning: &&        */
/* */
#define ERR__ERRNF    7    /* Error number && not found */
#define ERR__MSKNF    9    /* Mask && not found */
#define ERR__MSKNIMPL 11   /* Mask && not implemented */
#define ERR__FNIMPL   13   /* Feature not implemented. && */
#define ERR__SYSERR   15   /* System error: && */
#define ERR__SIGNAL   16   /* Signal: && */

#define ERR__SETTASK  60   /* Set task name &&. */
#define ERR__SETVERB  62   /* Verbosity flag set: &&. */
#define ERR__CLRVERB  64   /* Verbosity flag cleared: &&. */
#define ERR__STS      66   /* errstat &&. */
#define ERR__INIT     68   /* Using f_ut_error local ctrl structure. */
#define ERR__INITERR  69   /* Warn: Not specified, using local ctrl structure.*/
#define ERR__INITGET  70   /* Get f_ut_error ctrl structure. &&.*/
#define ERR__INITADDR 71   /* Invalid addr:
Read or write f_ut_error ctrl structure. */
#define ERR__INITPUT  72   /* Put f_ut_error ctrl structure. &&.*/
#define ERR__TEST     74   /* Test f_ut_error: &&. */
#define ERR__ENALOG   76   /* Enable message log: &&. */
#define ERR__DISLOG   78   /* Disable message log: &&. */

#define ERR__MSG_COMM  80   /* Write command style to f_ut_send_msg */
#define ERR__MSG_INFO  81   /* Write info style to f_ut_send_msg    */
#define ERR__MSG_ERROR 82   /* Write error style to f_ut_send_msg   */


/* +++ COLlector    error numbers start with 100 +++ */
#define ERR__COL_HISENA 101 /* Histogramming already enabled. && */
#define ERR__COL_FIEVT  103 /* first event was not triggertype 14 */
#define ERR__COL_TRMIS  105 /* trigger type or local event counter mismatch */
#define ERR__COL_TRTYP  107 /* trigger type is out of range (1-15) */
#define ERR__COL_BIGEV  109 /* event is bigger than stream capacity */
#define ERR__COL_DAMIS  111 /* mismatch in pipe data buffers 0,1 */


/* +++ RD (Readout) error numbers start with 200 +++ */
#define ERR__RD_FITRG  201 /* first trigger type was not 14 */
#define ERR__RD_NORDT  203 /* table readout specified but no readout table */
/* was loaded */
#define ERR__RD_LECMIS 205 /* local event counter differs more than 1 count */
/* compared to previous one (modula 32) */
#define ERR__RD_TRTYP  207 /* trigger type is out of range (1-15) */
#define ERR__RD_TRMIS  209 /* trigger type is out of range (1-15) */


/* +++ TRansport    error numbers start with 300 +++ */
#define ERR__MALLOC 301
#define ERR__SCSI_WRTFILEMARK 303
#define ERR__SCSI_WRITE 305
#define ERR__SCSI_REWIND 307
#define ERR__SCSI_UNLOAD 309
#define ERR__SCSI_OPEN 311
#define ERR__SCSI_SETBLKSIZE 313
#define ERR__SCSI_UNKNMEDIA 315
#define ERR__SCSI_MSENSE 317
#define ERR__SCSI_INQUIRY 319
#define ERR__SCSI_MSELECT 321


/* +++ EVent_server error numbers start with 400 +++ */
#define ERR__EV_CLNOTMR  400  /* Warning: Client not marked. && */
#define ERR__EV_CLAMRK   402  /* Warning: Client allready marked. && */
#define ERR__EV_ECLAMRK  403  /* Client allready marked. && */
#define ERR__EV_CLNOTV   404  /* Warning: Client not valid. && */
#define ERR__EV_ECLNOTV  405  /* Client not valid. && */
#define ERR__EV_CLNRDY   406  /* No client ready/active. && */
#define ERR__EV_FLTNV    407  /* Filter not valid. && */
#define ERR__EV_WARNFLT  408  /* Warning for filter. && */
#define ERR__EV_EBFACKN  409  /* Buffer acknoledge. && */
#define ERR__EV_WBFACKN  410  /* Warning: Buffer acknoledge. && */
#define ERR__EV_WBACKTO  412  /* Warning: Buffer acknoledge timeout. && */
#define ERR__EV_WBFPEND  414  /* Buffer pending. && */
#define ERR__EV_CLNSTS   415  /* Wrong client status. && */
#define ERR__EV_LSTBUF   416  /* Info: Was last buffer. && */
#define ERR__EV_WRTBUF   417  /* Error writing buffer. && */
#define ERR__EV_CLNACC   419  /* Error client accept . && */
#define ERR__EV_RELSTR   420  /* Release stream: &&. */
#define ERR__EV_USBFTY   421  /* Unsupported buffer typ: &&. */
#define ERR__EV_UKNBFTY  423  /* Unknown buffer typ: &&. */
#define ERR__EV_UKNEVTY  425  /* Unknown event typ: &&. */
#define ERR__EV_UKNSETY  427  /* Unknown subevent typ: &&. */
#define ERR__EV_EVTOOBIG 429  /* Event too big for buffer: &&. */
/* */

/* +++ ESone_server error numbers start with 500 +++ */
#define ERR__ES_CLNOTMR  500  /* Warning: Client not marked. && */
#define ERR__ES_CLAMRK   502  /* Warning: Client allready marked. && */
#define ERR__ES_BFRDTO   514  /* Buffer read timeout. && */
#define ERR__ES_ERDBUF   515  /* Error reading buffer. && */
#define ERR__ES_LSTBUF   516  /* Info: Was last buffer. && */
#define ERR__ES_WRTBUF   517  /* Error writing buffer. && */
#define ERR__ES_CLNACC   519  /* Error client accept. && */
#define ERR__ES_MAXCLN   521  /* Maximum number of clients exceeded. && */
#define ERR__ES_BFSTRD   530  /* Buffer status read: && */
#define ERR__ES_BFSTWR   532  /* Buffer status write: && */
#define ERR__ES_BFPROC   534  /* Buffer in process: && */
#define ERR__ES_EESONE   537  /* Error in Esone call: && */
/* */

/* +++ Histogram_manager error numbers start with 600 +++ */
#define ERR__HIS_SPNFND  601  /* Error: Histogram && not found */
#define ERR__HIS_EOFSPN  602  /* Warn: End of histogram list. && */
#define ERR__HIS_RANGES  603  /* Error: Value out of range. && */
#define ERR__HIS_WRNGNO  605  /* Error: Wrong number typed */
#define ERR__HIS_EANAL   607  /* Error in analysis: && */
#define ERR__HIS_NFREEM  609  /* Error: Can't get the memory */
#define ERR__HIS_NOPENF  611  /* Error: Can't open the file */
#define ERR__HIS_INVHIS  613  /* Error: Invalid histogram name or too long */
#define ERR__HIS_NALFNO  615  /* Error: Only alphanumeric symbols allowed */
#define ERR__HIS_NOMEMR  617  /* Error: No memory allocated */
#define ERR__HIS_HALREX  619  /* Histogram && already exists */
#define ERR__HIS_NFREDP  621  /* No free memory in data pool && */
#define ERR__HIS_HTABFU  623  /* Histogram table full && */
#define ERR__HIS_EWPAR   625  /* Wrong parameter && */
#define ERR__HIS_SKIPEVT 626  /* Skip event &&. */
#define ERR__HIS_SKIPSEV 628  /* Skip subevent &&. */
#define ERR__HIS_NBASATT 629  /* No Base attached. &&*/
#define ERR__HIS_BASATT  630  /* Base && already attached. */
#define ERR__HIS_NHISBAS 631  /* Base && is not a histogram base. */
#define ERR__HIS_DBLOCK  633  /* Base locked by another user. && */
/* */
