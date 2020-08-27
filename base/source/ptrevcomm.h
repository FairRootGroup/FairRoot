/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*********************************************************************
 * Copyright:
 *   GSI, Gesellschaft fuer Schwerionenforschung mbH
 *   Planckstr. 1
 *   D-64291 Darmstadt
 *   Germany
 *********************************************************************
 * ptrevcomm.h
 * communication structures
 *    multi-threaded remote event server <-> ROOT clients
 * created  2. 2.99, Horst Goeringer
 *********************************************************************
 * 23. 3.1999, H.G.: srevInfo added
 * 26. 7.1999, H.G.: sptrevDummy added
 * 10.11.1999, H.G.: iIdent in srevComm added
 *********************************************************************
 */

/* client requests events from server */
typedef struct
{
    int iSize;    /* size of comm. buffer without this element (bytes) */
    int iMode;    /* must be 1: client requests data  */
    int iIdent;   /* =1: NOT IN NET REPR. to identify client endian type */
    int iBufRequ; /* number of buffers requested */
} srevComm;

/* server sends info to client */
typedef struct
{
    int iSize; /* size of info buffer without this element (bytes) */
    int iMode; /* must be 1: server sends info */
    /* else: client tries swap */
    int iHeadPar; /* no. of header parms in buffer */
    int iTimeOut; /* wait time client after CTL C */
} srevInfo;

/* server sends dummy buffer to client, if no DAQ events available */
typedef struct
{
    int iSize;  /* size of data following */
    int iBufNo; /* current buffer number */
    int iEvtNo; /* no. of events in buffer (= 0) */
} sptrevDummy;
