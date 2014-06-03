/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//////////////////////////////////////////////////////////////////////
// Copyright:
//   GSI, Gesellschaft fuer Schwerionenforschung mbH
//   Planckstr. 1
//   D-64291 Darmstadt
//   Germany
// created 16. 2.1999 by Horst Goeringer
//////////////////////////////////////////////////////////////////////
// MRevBuffer.cc
//   ROOT client package for multithreaded remote event server (MBS)
//////////////////////////////////////////////////////////////////////
// 15. 3.1999, H.G.: RecvRaw replaced by original recv calls
// 26. 7.1999, H.G.: accept dummy buffers (no events from DAQ)
// 20. 8.1999, H.G.: MRevBuffer::RevGetI added
//  3. 3.2000, H.G.: change default port no.: 6013 -> 6003
//  6. 3.2000, H.G.: new member function RevStatus
// 19.11.2001, H.G.: increase data buffer dynamically
//////////////////////////////////////////////////////////////////////

#include "MRevBuffer.h"            // class definition

#include "Riosfwd.h"                    // for ostream
#include "TSocket.h"                    // for TSocket, etc

#include <iostream>                     // for operator<<, basic_ostream, etc

#include <signal.h>                     // IWYU pragma: keep
#include <unistd.h>                     // IWYU pragma: keep
#include <time.h>                     // IWYU pragma: keep
#include <netinet/in.h>                     // IWYU pragma: keep

#ifdef Linux
#include <socket.h>                     // IWYU pragma: keep
#include <select.h>                     // IWYU pragma: keep
#else                             // AIX
#include <strings.h>                     // IWYU pragma: keep
#include <sys/socket.h>                     // IWYU pragma: keep
#include <sys/select.h>                     // IWYU pragma: keep
#endif

#include "ptrevcomm.h"            // communication structure
#include "ptrevmbsdef.h"          // MBS data definitions

// IWYU pragma: no_include <stdio.h>
// IWYU pragma: no_include <sys/_endian.h>
// IWYU pragma: no_include <sys/signal.h>

using namespace std;

ClassImp(MRevBuffer)
ClassImp(REvent)

extern "C"
{
  long swaplw( int*, int, int);          // swap data
  void exitCli(int);                     // handle CTL C
  int rclose(int*, int);                 // close connection to server
}

#ifdef Linux
struct timeval {
  long tv_sec;
  long tv_usec;
};
#endif

int iTimeOut;        // needed in exitCli to handle CTL C
int imySig = 0;      // needed in exitCli to handle CTL C
int iOutMode = 0;    // needed in exitCli to handle CTL C

MRevBuffer::MRevBuffer(Int_t iMode)
  : TObject(),
    pTSocket(NULL),
    iSocket(0),
    iBufNo1(0),
    iBufNo2(0),
    iDebug(iMode),
    iSwap(0),
    iStatus(1),
    iBufSizeAlloc(512000),
    iBufSize(0),
    iBufNo(0),
    iFragBegin(0),
    iFragConc(0),
    iFragBeginIgn(0),
    iFragEndIgn(0),
    iHeadPar(0),
    iEvtMax(0),
    iEvtNo(0),
    iEvtRel(0),
    iEvtBuf(0),
    iEvtPar(0),
    piBuf(new int [iBufSizeAlloc/sizeof(int)+1]),
    piNextEvt(NULL),
    pEvt(new REvent())
{
//  iStatus = 1;                         // server not yet connected
  /*
    iSwap = 0;
    iSocket = 0;
    iEvtRel = 0;
    iEvtPar = 0;
    iBufSize = 0;
  */

  signal(SIGINT, exitCli);                 // from now catch CTL C

//  iDebug = iMode;
  iOutMode = iMode;
  if (iDebug == 1) {
    cout << "-I- client runs in debug mode (1)" << endl;
  } else if (iDebug == 2)
    cout << "-I- client shows buffer numbers and select/receive (mode 2)"
         << endl;
  else if (iDebug == 3) {
    cout << "-I- client shows buffer numbers (mode 3)" << endl;
  } else if (iDebug == 5) {
    cout << "-I- client shows event parameters (mode 5)" << endl;
  }

  if (iDebug == 1) {
    cout << "    check ENDIAN, ";
#ifdef _AIX
    cout << " should be BIG_ENDIAN: ";
#endif
#ifdef Linux
    cout << " should be LITTLE_ENDIAN: ";
#endif

#ifdef BIG__ENDIAN
    cout << " BIG_ENDIAN" << endl;
#else
    cout << " LITTLE_ENDIAN" << endl;
#endif
  }

  //  iBufSizeAlloc = 16384;
  //  piBuf = new int [iBufSizeAlloc/sizeof(int)+1]; // 16k buffer + len
  if (iDebug == 1)
    cout << "-D- buffer allocated (" << iBufSizeAlloc+sizeof(int)
         << " byte)" << endl;

  //  REvent* pev = new REvent();    // create event (once)
  //  pEvt = pev;                    // keep pointer in class MRevBuffer

  // cout << "    MRevBuffer() executed" << endl;

}  // constructor

MRevBuffer::~MRevBuffer()
{
  // cout << "    ~MRevBuffer() ..." << endl;
  delete [] piBuf;
  piNextEvt = 0;
  pEvt->~REvent();
  // cout << "    ~MRevBuffer() executed" << endl;

} // destructor

TSocket* MRevBuffer::RevOpen ( char* pNode, Int_t iPort, Int_t iEvent)
{
  if (iEvent < 0) {
    cout << "-E- number of requested events (" << iEvent
         << ") invalid" << endl;
    return(0);
  }
  if (iEvent == 0) {
    iEvent = 2000000000;           // nearly unlimited
    cout << "-I- unlimited no. of MBS events requested - break with 'CTL C'"
         << endl;
  }

  if (iPort == 6001) {
    cout << "-E- old event server (port no. 6001) running on DAQ frontend not yet supported"
         << endl;
    cout << "    use stream server (port no. 6002) and remote event server (port no. 6003)"
         << endl;
    return(0);
  }
  if (iPort == 0) { iPort = 6003; } // default MBS remote event server

  iEvtMax = iEvent;
  iEvtNo = 0;
  iBufNo = 0;
  iBufNo1 = 0;
  iBufNo2 = 0;
  iFragConc = 0;
  iFragBegin = 0;
  iFragBeginIgn = 0;
  iFragEndIgn = 0;

  if (!iSocket) {
    iEvtNo = -1;            // initialization (info buffer) required
    cout << "-I- open connection to server " << pNode
         << ":" << iPort << endl;

    pTSocket = new TSocket(pNode, iPort);
    if ( !pTSocket->IsValid() ) {
      cout << "-E- open connection to server " << pNode
           << " failed" << endl;
      return(0);
    }
    cout << "    connection to server " << pNode
         << ":" << iPort << " okay" << endl;

    iSocket = pTSocket->GetDescriptor();
    imySig = iSocket;
    if (iDebug == 1) {
      cout << "    socket " << iSocket << endl;
    }

  } else if (iDebug == 1) {
    cout << "-D- socket " << iSocket << endl;
  }

  iStatus = 2;                                   // server connected
  return(pTSocket);

} // RevOpen

Int_t* MRevBuffer::RevGetI(TSocket* pSocket, Int_t iFlush)
{
  Int_t* piEvent;
  REvent* pEvent;

  pEvent = RevGet(pSocket, iFlush, 0);
  if (pEvent) { piEvent = piNextEvt; }
  else { piEvent = 0; }
  return piEvent;

} // RevGetI

REvent* MRevBuffer::RevGet(TSocket* pSocket, Int_t iFlush, Int_t iSkip)
{
  Int_t iint = sizeof(int);
  Int_t ii;
  Int_t ilen, iselen, iselen1, ielen, inew = 0;

  Short_t* pshort;

  Char_t cMsg[128] = "";
  Char_t* pcBuf;
  Int_t iSize, iRC;
  Long_t lRC;

  Int_t iError = 0;
  Int_t iRetry;
  Int_t iRetryMax = 1000;
  Int_t iRetryFirst;
  Int_t iRetryRecv = 0;         // count retries of recv call
  Int_t iRetryRecvLim = 1;      // max. no. of succeeding retries

  Int_t* piComm;
  srevComm sComm;
  Int_t iCommSize = sizeof(sComm);      // size comm. buffer (byte)

  Int_t* piInfo;
  srevInfo sInfo;
  Int_t iInfoSize = sizeof(sInfo);      // size info buffer (byte)

//    Int_t iHeadPar = 12;         // no. of params in MBS buffer header
  iHeadPar = 12;         // no. of params in MBS buffer header
  Int_t iBufNoServ;                   // buffer no. sent from server
  short* psNextEvt;
  Int_t iHead[2];

  sMbsEv101 sEvtHead, *pEvtHead;                // header event 10.1
  pEvtHead = &sEvtHead;
  sMbsSev101 sSEvtHead, *pSEvtHead;                // header event 10.1
  pSEvtHead = &sSEvtHead;
  sMbsBufFrag sFrag, *pFrag;                  // fragmented event flags
  pFrag = &sFrag;

  if (iEvtNo >= iEvtMax) { goto gEndGet; }

  piComm = &(sComm.iSize);               // communication buffer
  sComm.iSize = htonl(iCommSize-iint);   // size of data following
  sComm.iMode = htonl(1);                // required: get events
  sComm.iIdent = 1;                      // required: tell endian type
  sComm.iBufRequ = htonl(1);             // send one buffer

  // initialize communication with server
  if (iEvtNo == -1) {        // initialize communication with server
    if (iDebug == 1)
      cout << "-D- commbuf (data size " << ntohl(sComm.iSize)
           << " byte): mode(1) " << ntohl(sComm.iMode)
           << ", request " <<  ntohl(sComm.iBufRequ)
           << " event buffer(s)" << endl;

    // request event buffer from server
    ilen = pSocket->SendRaw(piComm, iCommSize, kDefault);
    if (ilen < 0) {
      cout << "-E- sending request for events to server, rc = "
           << ilen << endl;
      iError = 1;
      goto gEndGet;
    }

    if (iDebug == 1)
      cout << "    communication buffer sent (request info buffer) "
           << endl;

    // receive info buffer from server
    piInfo = &(sInfo.iSize);
    ilen = pSocket->RecvRaw(piInfo, iInfoSize, kDefault);
    if (ilen < 0) {
      cout << "-E- receiving info buffer from server, rc = "
           << ilen << endl;
      iError = 1;
      goto gEndGet;
    }

    iHeadPar = ntohl(sInfo.iHeadPar);
    iTimeOut = ntohl(sInfo.iTimeOut);
    if (iDebug == 1) {
      cout << "-D- info buffer received:" << endl;
      cout << "    size data " << ntohl(sInfo.iSize)
           << ", mode (1) " << ntohl(sInfo.iMode)
           << ", header parms " << iHeadPar
           << ", timeout " << iTimeOut << endl;
    }

    if ( (ntohl(sInfo.iMode) != 1) ||
         ( (int) ntohl(sInfo.iSize) != iInfoSize-iint) ) {
      cout << "-E- invalid info buffer received: " << endl;
      cout << "    size data ( " << iInfoSize-iint
           << ") "  << ntohl(sInfo.iSize)
           << ", mode (1) " << ntohl(sInfo.iMode)
           << ", header parms " << iHeadPar
           << ", timeout " << iTimeOut << endl;
      iError = 1;
      goto gEndGet;
    }

    iEvtNo = 0;                                // initilization done
    inew = 1;                                  // request new buffer

  } // (iEvtNo == -1)
  else {
    if (iFlush) {
      inew = 1;                            // request new buffer
      if (iDebug == 1) {
        cout << "-D- skip current buffer" << endl;
      }
    } else {
      if (iEvtNo >= 0) {
        // refresh some buffer infos not stored in class data
        pFrag = (sMbsBufFrag*) &piBuf[3];

        // check if new buffer needed
        ii = 0;                          // count buffer header
        if (pFrag->cBuf_fragBegin) { ii++; }
        if (pFrag->cBuf_fragEnd) { ii++; }

        if (iEvtRel+ii >= iEvtBuf) {
          if (iDebug == 1) {
            cout << "-D- request new buffer" << endl;
          }
          inew = 1;
          if (iDebug == -1) {
            piNextEvt += iEvtPar;         // skip previous event
            cout << "-D- next 40 2byte-words of buffer:" << endl;
            psNextEvt = (short*) piNextEvt;
            for (Int_t iii=0; iii<40; iii++) {
              cout << "    " << iii+1 << ": " << psNextEvt[iii]
                   << endl;
            }
          }
        } else { inew = 0; }

      } // (iEvtNo > 0)
    } // (!iFlush)
  } // (iEvtNo != -1)

  // request new buffer
  if (inew) {
    iEvtRel = 0;
    iRetry = 0;
    iRetryFirst = 1;
    if (imySig == -1) {
      sComm.iBufRequ = htonl(0);  // signal finish to server
    }

    // request next buffer or finish
    ilen = pSocket->SendRaw(piComm, iCommSize, kDefault);
    if (ilen < 0) {
      cout << "-E- sending request for buffer " << iBufNo+1
           << " to server, rc = " << ilen << endl;
      iError = 1;
      goto gEndGet;
    }

    if (imySig == -1) { goto gEndGet; }

    if (iDebug == 1)
      cout << "-D- communication buffer sent (request next buffer) "
           << endl;

gRetryLen:
    // get size of data following
    piBuf[0] = -1;                         // enables receive check
    iSize = iint;
    pcBuf = (char*) piBuf;
    while(iSize > 0) {
      if ( (imySig == -1) && (iDebug) ) {
        cout << "    CTL C detected (before recv len)" << endl;
      }
gNextRecvL:
      iRC = recv(iSocket, pcBuf, iSize, 0);
      if (iRC < 0) {
        if (imySig == -1) {
          if (iDebug) {
            sprintf(cMsg,
                    "\n-E- receiving data length from server");
            perror(cMsg);
            cout << "    CTL C detected (during recv len)"
                 << endl;
          }
          goto gNextRecvL;
        } else {                                 // a real problem
          sprintf(cMsg, "\n-E- receiving data length from server");
          perror(cMsg);
          if (iDebug) { cout << "    retry" << endl; }

          iRetryRecv++;      // count no. of retries to limit them
          if (iRetryRecv > iRetryRecvLim) { // avoid infinite loop
            iError = 1;
            goto gEndGet;
          } else { goto gNextRecvL; }
        }
      }
      if ( iRC == 0 ) {
        if ( (iDebug == 2) || (iDebug == 3) ) {
          cout << endl;
        }
        cout << "-E- receiving data length: connection closed by server"
             << endl;
        iError = 1;
        goto gEndGet;
      }

      iRetryRecv = 0;
      iSize -= iRC;
      pcBuf += iRC;

    } /* while(iSize > 0) */

    if (iDebug == 2) {
      printf("Rl:");
      fflush(stdout);
    }

    if ( (imySig == -1) && (iDebug) ) {
      cout << "    CTL C detected (after recv len)" << endl;
    }

    iBufSize = ntohl(piBuf[0]);
    if (iDebug == 1) {
      cout << "    data size received: " << iBufSize << endl;
    }

    if (iBufSize <= 0) {
      if (iBufSize == 0) {
        if (iDebug) {
          cout << endl;
        }
        cout << "-W- server closed connection" << endl;
        cout << "    " << iEvtNo << " of " << iEvtMax
             << " events received" << endl;
        iError = 1;
        goto gEndGet;
      }

      if (iBufSize == -1) {
        if (iRetryFirst) {
          cout << endl << "-E- no data length received: ";
          iRetryFirst = 0;
        }
        iRetry++;
        if (iRetry > iRetryMax) {
          cout << iRetryMax << "times" << endl;
          iError = 1;
          goto gEndGet;
        }
        goto gRetryLen;
      } else {
        cout << endl << "-E- invalid data length received: "
             << iBufSize << endl;
        iError = 1;
      }

      goto gEndGet;
    }
    if (iRetry) {
      cout << iRetry << "times" << endl;
    }

    // increase data buffer, if necessary
    if (iBufSize+iint > iBufSizeAlloc) {
      delete [] piBuf;
      iBufSizeAlloc = iBufSize+iint;
      // new total buffer size (including length field)
      piBuf = new int [iBufSizeAlloc/iint];
      piBuf[0] = iBufSize;
      // keep sent buffer size (without length field)
      if (iDebug == 1)
        cout << "-I- total buffer increased to "
             << iBufSizeAlloc << " byte" << endl;
    }

    // get event buffer without length field
    piBuf[1] = -1;                         // enables receive check
    iSize = iBufSize;
    pcBuf = (char*) &(piBuf[1]);
    while(iSize > 0) {
      if ( (imySig == -1) && (iDebug) ) {
        cout << "    CTL C detected (before recv data)" << endl;
      }
gNextRecvD:
      iRC = recv(iSocket, pcBuf, iSize, 0);
      if (iRC < 0) {
        if (imySig == -1) {
          if (iDebug) {
            sprintf(cMsg, "\n-E- receiving data from server");
            perror(cMsg);
            cout << "    CTL C detected (during recv data)"
                 << endl;
          }
          goto gNextRecvD;
        } else {                                 // a real problem
          sprintf(cMsg, "\n-E- receiving data from server");
          perror(cMsg);

          iRetryRecv++;      // count no. of retries to limit them
          if (iRetryRecv > iRetryRecvLim) { // avoid infinite loop
            iError = 1;
            goto gEndGet;
          } else { goto gNextRecvD; }
        }
      }
      if ( iRC == 0 ) {
        if ( (iDebug == 2) || (iDebug == 3) ) {
          cout << endl;
        }
        cout << "-E- receiving data: connection closed by server"
             << endl;
        iError = 1;
        goto gEndGet;
      }

      iRetryRecv = 0;
      iSize -= iRC;
      pcBuf += iRC;

    } /* while(iSize > 0) */

    if (iDebug == 2) {
      printf("Rd:");
      fflush(stdout);
    }

    if (imySig == -1) {
      if (iDebug) {
        cout << "    CTL C detected (after recv data)" << endl;
      }
      goto gEndGet;
    }

    // test for dummy buffer (no DAQ events available)
    if ( iBufSize == (sizeof(sptrevDummy)-sizeof(int)) ) {
      iBufNoServ = ntohl(piBuf[1]);
      iEvtBuf = ntohl(piBuf[2]);
      if (iEvtBuf == 0) {
        if (iDebug == 1)
          printf("    dummy buffer no. %d, %d events\n",
                 iBufNoServ, iEvtBuf);
        if (iDebug == 3) { cout << endl; }
        cout << "*** connection to remote event server okay, but currently no DAQ events ("
             << iBufNoServ << ")" << endl;
        iStatus = 3;
        goto gRetryLen;
      } else {
        cout << "-E- invalid event number in dummy buffer no. "
             << iBufNoServ << ": "
             << iEvtBuf << " (expected: 0)" << endl;
        iError = 1;
        goto gEndGet;
      }
    }

    if (!iSwap) {
      if (piBuf[9] != 1) { iSwap = 1; }
    }

    /* swap MBS buffer */
    if (iSwap) {
      lRC  = swaplw( &piBuf[1], iBufSize/iint, 0);
      if ( (iBufNo == 0) && (iDebug) ) {
        cout << "    Event data swapped" << endl;
      }
    }

    iBufNo++;
    iBufNoServ = piBuf[4];
    iEvtBuf = piBuf[5];           // no. of events in current buffer

    if (iEvtNo == 0) {
      iBufNo = 1;                          // restart counting
      iBufNo1 = iBufNoServ;                // keep first buffer no.
      iFragBegin = 0;
      iFragBeginIgn = 0;
      iFragEndIgn = 0;
      iFragConc = 0;
    }
    iBufNo2 = iBufNoServ;                   // keep last buffer no.

    if (iDebug >= 2) {
      printf("%d:", iBufNoServ);
      fflush(stdout);
    }

    pFrag = (sMbsBufFrag*) &piBuf[3];
    if (iDebug == 1) {
      cout << endl << "buffer " << iBufNo
           << " (" << iBufNoServ << "): "
           << " size "
           << iBufSize << " byte" << endl;
      if (pFrag->cBuf_fragBegin) {
        cout << "    last event fragment" << endl;
      }
      if (pFrag->cBuf_fragEnd) {
        cout << "    first event fragment" << endl;
      }
      cout << "    buffer contains " << iEvtBuf << " elements"
           << endl;
    }

    if (pFrag->cBuf_fragEnd) {
      iFragEndIgn++;
      if ( (iEvtNo > 0) && (iFragBegin) ) {
        iFragConc++;
      }
    }

    if (pFrag->cBuf_fragBegin) {
      iFragBegin = 1;                // keep info for next buffer
      iFragBeginIgn++;
    }

    if (iDebug == -1) {
      cout << "-D- first 50 2byte-words of buffer:" << endl;
      psNextEvt = (short*) &piBuf[1];
      for (Int_t iii=0; iii<50; iii++) {
        cout << "    " << iii+1 << ": " << psNextEvt[iii] << endl;
      }
    }

    iEvtRel = 1;                      // first event in buffer
    piNextEvt = piBuf + iHeadPar+1;   // ptr first element in buffer
    iEvtPar = piNextEvt[0]/2 + 2;     // no. of parameters new event

    if (pFrag->cBuf_fragEnd) {
      piNextEvt += iEvtPar;          // skip fragment end
      iEvtPar = piNextEvt[0]/2 + 2;  // no. of parameters new event
    }

  } // new buffer
  else {
    iEvtRel++;                        // event no. in buffer
    piNextEvt += iEvtPar;             // skip previous event
    iEvtPar = piNextEvt[0]/2 + 2;     // no. of parameters new event

    // also if starting with current buffer: keep first buffer no.
    if (iEvtNo == 0) {
      iBufNo = 1;                          // restart counting
      iBufNoServ = piBuf[4];
      iBufNo1 = iBufNoServ;

      iFragBegin = 0;
      iFragBeginIgn = 0;
      iFragEndIgn = 0;
      iFragConc = 0;
      pFrag = (sMbsBufFrag*) &piBuf[3];
      if (pFrag->cBuf_fragBegin) {
        iFragBegin = 1;                // keep info for next buffer
        iFragBeginIgn++;
      }
      if (pFrag->cBuf_fragEnd) { iFragEndIgn++; }

    } // (iEvtNo == 0)
  } // continue with current buffer

  iEvtNo++;                            // total event no.
  psNextEvt = (short*) piNextEvt;
  pEvtHead = (sMbsEv101*) piNextEvt;
  ielen = pEvtHead->iMbsEv101_dlen;
  pSEvtHead = (sMbsSev101*) &piNextEvt[4];
  pshort = (short*) pSEvtHead;



  pEvt->nSubEvt = 0;



  if ( (iDebug == 1) || (iDebug == 5) ) {
    iselen1 = pSEvtHead->iMbsSev101_dlen;


    pEvt->nSubEvt += 1;
    pEvt->subEvtSize[0] = pSEvtHead->iMbsSev101_dlen/2 - 1;
    pEvt->subEvtType[0] = pSEvtHead->sMbsSev101_type;
    pEvt->subEvtSubType[0] = pSEvtHead->sMbsSev101_subtype;
    pEvt->subEvtProcId[0] = pSEvtHead->sMbsSev101_procid;
    pEvt->subEvtSubCrate[0] = pSEvtHead->cMbsSev101_subcrate;
    pEvt->subEvtControl[0] = pSEvtHead->cMbsSev101_control;
    pEvt->pSubEvt[0] = (Int_t*) &pshort[6];

/*
    cout << "    evt " << iEvtNo << " (" << piNextEvt[3]
         << "), len " << pEvtHead->iMbsEv101_dlen
         << ", type " << pEvtHead->sMbsEv101_type
         << "." << pEvtHead->sMbsEv101_subtype
         << ", trigger " << pEvtHead->sMbsEv101_trigger;
    cout << ", SE1 len " << iselen1
         << " procid " << pSEvtHead->sMbsSev101_procid;
*/
    ielen -= (iselen1 + 8);

    ii = 1;
    iselen = iselen1;
    while (ielen > 0) {
      ii++;
//          if (ii > 3) break;
      pshort += iselen + 4;
      pSEvtHead = (sMbsSev101*) pshort;
      iselen = pSEvtHead->iMbsSev101_dlen;
//      cout << ", SE" << ii << " " << iselen
//           << " " << pSEvtHead->sMbsSev101_procid;
      ielen -= (iselen + 4);



      pEvt->nSubEvt += 1;
      pEvt->subEvtSize[ii-1] = pSEvtHead->iMbsSev101_dlen/2 - 1;
      pEvt->subEvtType[ii-1] = pSEvtHead->sMbsSev101_type;
      pEvt->subEvtSubType[ii-1] = pSEvtHead->sMbsSev101_subtype;
      pEvt->subEvtProcId[ii-1] = pSEvtHead->sMbsSev101_procid;
      pEvt->subEvtSubCrate[ii-1] = pSEvtHead->cMbsSev101_subcrate;
      pEvt->subEvtControl[ii-1] = pSEvtHead->cMbsSev101_control;
      pEvt->pSubEvt[ii-1] = (Int_t*) &pshort[6];


    }
//    cout << endl;
  }

  // fill event header
  iHead[0] = piNextEvt[0];                      // event length
  iHead[1] = piNextEvt[3];                      // event number
  pEvt->ReFillHead(iHead);

  // fill event data
  pEvt->ReFillData(piNextEvt);

  if (imySig == -1) {
    cout << endl << "-D- CTL C specified";
    if (iDebug) { cout << " (at end RevGet)" << endl; }
    else { cout << endl; }
    goto gEndGet;
  }

  if (iEvtNo == iEvtMax) {
    cout << endl << "-I- all required events ("
         << iEvtMax << ") received: " << iBufNo << " buffers ("
         << iBufNo1 << " - " << iBufNo2 << ")" << endl;
    cout << "    fragments found: " << iFragBeginIgn << " begin, "
         << iFragEndIgn << " end" << endl;
    if (iFragConc)
      cout << "    " << iFragConc
           << " events not concatenated from fragments" << endl;
  }

  iStatus = 0;                      // last event request successfull
  return(pEvt);

gEndGet:
  if ( (iError) || (imySig == -1) ) {
    if (iDebug) {
      cout << "    RevGet: closing connection to server";
    }
    iRC = rclose(&iSocket, 2);
    if ( (iDebug) && (iRC == 0) ) {
      cout << " - done" << endl;
    }

    if (imySig == -1) { iStatus = 5; }          // user break (CTL C)
    else { iStatus = 6; }                       // failure
    imySig = 0;                             // notify CTL C handler
  } else if (iDebug == 1) {
    cout << "    RevGet: keeping connection to server" << endl;
  }

  return 0 ;

} // RevGet

Int_t MRevBuffer::RevBufsize()
{
  return iBufSize;
} // RevBufsize

void MRevBuffer::RevBufWait( Int_t iWait )
{
  if (iWait > 0) { sleep(iWait); }
} // RevBufWait

Int_t MRevBuffer::RevStatus( Int_t iOut )
{
  if (iOut) switch(iStatus) {
    case 0:
      cout << "-I- *** Last request for events was successfull"
           << endl;
      break;
    case 1:
      cout << "-I- *** Remote event server not yet connected"
           << endl;
      break;
    case 2:
      cout << "-I- *** Remote event server connected, but still no request for events"
           << endl;
      break;
    case 3:
      cout << "-I- *** Connection to remote event server okay, but currently no DAQ events"
           << endl;
      break;
    case 4:
      cout << "-I- *** Connection to remote event server closed"
           << endl;
      break;
    case 5:
      cout << "-I- *** Connection to remote event server closed after user break (CTL C)"
           << endl;
      break;
    case 6:
      cout << "-I- *** Connection to remote event server closed after failure"
           << endl;
      break;
    default:
      cout << "-E- Invalid status remote event server found: "
           << iStatus << endl;
    }
  return iStatus;

} // RevStatus

void  MRevBuffer::RevClose( TSocket* pSocket )
{
  int iRC;
  Int_t* piComm;
  srevComm sComm;
  Int_t iCommSize = sizeof(sComm);       // size comm. buffer (byte)

  if (imySig < 0) { return; }        // CTL Y: connection closed elsewhere
  if (iSocket == 0) { return; }

  // tell server that no more events needed
  piComm = &(sComm.iSize);               // communication buffer
  sComm.iSize = htonl(iCommSize-sizeof(int));// size of data following
  sComm.iMode = htonl(1);                // required: get events
  sComm.iIdent = 1;                      // required: tell endian type
  sComm.iBufRequ = htonl(0);             // no more event buffers

  if (iDebug == 1)
    cout << "-D- send close request (data size "
         << ntohl(sComm.iSize) << " byte): "
         << ntohl(sComm.iMode) << ", "
         << ntohl(sComm.iBufRequ) << endl;

  iRC = pSocket->SendRaw(piComm, iCommSize, kDefault);
  if (iRC < 0)
    cout << "-E- sending close request to server, rc = "
         << iRC << endl;
  else if (iDebug == 1) {
    cout << "    close request sent" << endl;
  }

  if (iDebug) {
    cout << "    RevClose: closing connection to server";
  }
  iRC = rclose(&iSocket, 2);
  if ( (iDebug) && (iRC == 0) ) {
    cout << " - done" << endl;
  }

  iStatus = 4;                        // connection to server closed
  imySig = 0;                         // notify CTL C handler
  cout << "-I- connection to server closed" << endl;

} // RevClose

/////////////////////////////////////////////////////////////////////

REvent::REvent()
  : TObject(),
    iSize(0),
    iNumb(0),
    piData(NULL),
    nSubEvt(0),
    subEvtSize(),
    subEvtType(),
    subEvtSubType(),
    pSubEvt()
{
  // cout << "    REvent() ..." << endl;
//  iNumb = 0;
//  piData = 0;
}

REvent::~REvent()
{
  // cout << "    ~REvent() ..." << endl;
}

void REvent::ReFillHead(Int_t* pHead)
{
  iSize = pHead[0];     // event size without header in 2-byte-words
  iNumb = pHead[1];
}

void REvent::ReFillData(Int_t* pdata)
{
  piData = pdata;
}

Int_t REvent::ReGetNumb()
{
  return iNumb;
}

Int_t REvent::ReGetSize()
{
  return iSize;
}

Int_t REvent::ReGetData(Int_t iChan)
{
  Int_t iValue;
  Int_t* pint;

  //if ( (iChan < 1) || (iChan > iSize/( (signed) sizeof(int))) )
  if ( (iChan < 1) || (iChan > (iSize+4)/( (signed) sizeof(short))) ) {
    cout << "-E- event parameter number " << iChan
         << " out of range (" << (iSize+4)/( (signed) sizeof(short))
         << " long words)" << endl;
    return(-1);
  }
  pint = piData;
  iValue = pint[iChan-1];
  //cout << "    param " <<  iChan << ": " << iValue << endl;
  return iValue;
}
