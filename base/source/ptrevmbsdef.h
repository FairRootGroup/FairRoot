/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*********************************************************************
 * ptrevmbsdef.h
 * contains declarations and definitions for GSI MBS 10.1 events
 * used in ROOT clients for multithreaded remote event server
 * created 18. 2.99, Horst Goeringer, GSI
 *
 * 27. 4.1999, H.G.: replace xxx_ENDIAN -> xxx__ENDIAN
 *                   xxx_ENDIAN used by AIX (machine.h)
 * 16. 9.1999, H.G.: add complete buffer header sMbsBufHead
 *                   rename VMEx -> MbsX
 * 23. 9.1999, H.G.: additional definitions old PAW clients
 *********************************************************************
 */

#ifdef _AIX
#define BIG__ENDIAN 1
#endif
#ifdef Linux
#define LITTLE__ENDIAN 1
#endif

#define COMMSIZE 404 /* max size comm. buffer (old and new clients) */
#define INFOALL 512
/* max size info buffers (old and new clients) and header (old) */
#define HEADOLD 344 /* header size (old clients) */

/************************* buffer header *****************************/

typedef struct
{                   /* MBS buffer header */
    long lBuf_dlen; /* buffer length without header (2byte words) */
#ifdef BIG__ENDIAN
    short sBuf_subtype; /* buffer subtype */
    short sBuf_type;    /* buffer type */
    short sBuf_frag;    /* fragment bytes */
    short sBuf_ulen;    /* used data length (2byte words) */
#else
    short sBuf_type;              /* buffer type */
    short sBuf_subtype;           /* buffer subtype */
    short sBuf_ulen;              /* used data length (2byte words) */
    short sBuf_frag;              /* fragment bytes */
#endif
    long lBuf_bufno;  /* current buffer number */
    long lBuf_ele;    /* number of elements in buffer */
    long lBuf_rem[7]; /* unused remainder of buffer header */
} sMbsBufHead;

/* */

typedef struct
{ /* fragment word of buffer header */
#ifdef BIG__ENDIAN
    unsigned char cBuf_fragBegin; /* fragment begin flag */
    unsigned char cBuf_fragEnd;   /* fragment end flag */
    short sBuf_ulen;              /* used Data length in words (2 byte) */
#else
    short sBuf_ulen;              /* used Data length in words (2 byte) */
    unsigned char cBuf_fragEnd;   /* fragment end flag */
    unsigned char cBuf_fragBegin; /* fragment begin flag */
#endif
} sMbsBufFrag;

/************************ event header *******************************/

typedef struct
{                       /* event header */
    int iMbsEv101_dlen; /*  Data length in words */
#ifdef BIG__ENDIAN
    short sMbsEv101_subtype;
    short sMbsEv101_type;
    short sMbsEv101_trigger; /*  Trigger number */
    short sMbsEv101_dummy;   /*  Not used yet */
#else
    short sMbsEv101_type;
    short sMbsEv101_subtype;
    short sMbsEv101_dummy;   /*  Not used yet */
    short sMbsEv101_trigger; /*  Trigger number */
#endif
    int iMbsEv101_count; /*  Current event number */
} sMbsEv101;

/************************* subevent header ***************************/

typedef struct
{ /* subevent header 10.1 */
#ifdef BIG__ENDIAN
    int iMbsSev101_dlen; /*  Data length in words */
    short sMbsSev101_subtype;
    short sMbsSev101_type;
    unsigned char cMbsSev101_control;
    unsigned char cMbsSev101_subcrate; /* Camac subcrate */
    short sMbsSev101_procid;           /* processor id. */
#else
    int iMbsSev101_dlen;     /*  Data length in words */
    short sMbsSev101_type;
    short sMbsSev101_subtype;
    short sMbsSev101_procid;           /* processor id. */
    unsigned char cMbsSev101_subcrate; /* Camac subcrate */
    unsigned char cMbsSev101_control;
#endif
} sMbsSev101;

/* end ptrevmbsdef.h */
