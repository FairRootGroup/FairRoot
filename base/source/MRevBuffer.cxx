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

#include "FairLogger.h"

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
    LOG(DEBUG) <<  "-I- client runs in debug mode (1)" << FairLogger::endl;
  } else if (iDebug == 2)
    LOG(DEBUG) <<  "-I- client shows buffer numbers and select/receive (mode 2)"
         << FairLogger::endl;
  else if (iDebug == 3) {
    LOG(DEBUG) <<  "-I- client shows buffer numbers (mode 3)" << FairLogger::endl;
  } else if (iDebug == 5) {
    LOG(DEBUG) <<  "-I- client shows event parameters (mode 5)" << FairLogger::endl;
  }

  if (iDebug == 1) {
    LOG(DEBUG) <<  "    check ENDIAN, ";
#ifdef _AIX
    LOG(DEBUG) <<  " should be BIG_ENDIAN: ";
#endif
#ifdef Linux
    LOG(DEBUG) <<  " should be LITTLE_ENDIAN: ";
#endif

#ifdef BIG__ENDIAN
    LOG(DEBUG) <<  " BIG_ENDIAN" << FairLogger::endl;
#else
    LOG(DEBUG) <<  " LITTLE_ENDIAN" << FairLogger::endl;
#endif
  }

  //  iBufSizeAlloc = 16384;
  //  piBuf = new int [iBufSizeAlloc/sizeof(int)+1]; // 16k buffer + len
  if (iDebug == 1)
    LOG(DEBUG) <<  "-D- buffer allocated (" << iBufSizeAlloc+sizeof(int)
         << " byte)" << FairLogger::endl;

  //  REvent* pev = new REvent();    // create event (once)
  //  pEvt = pev;                    // keep pointer in class MRevBuffer

  // LOG(INFO) <<  "    MRevBuffer() executed" << FairLogger::endl;

}  // constructor

MRevBuffer::~MRevBuffer()
{
  // LOG(INFO) <<  "    ~MRevBuffer() ..." << FairLogger::endl;
  delete [] piBuf;
  piNextEvt = 0;
  pEvt->~REvent();
  // LOG(INFO) <<  "    ~MRevBuffer() executed" << FairLogger::endl;

} // destructor

TSocket* MRevBuffer::RevOpen ( char* pNode, Int_t iPort, Int_t iEvent)
{
  if (iEvent < 0) {
    LOG(INFO) <<  "-E- number of requested events (" << iEvent
         << ") invalid" << FairLogger::endl;
    return(0);
  }
  if (iEvent == 0) {
    iEvent = 2000000000;           // nearly unlimited
    LOG(INFO) <<  "-I- unlimited no. of MBS events requested - break with 'CTL C'"
         << FairLogger::endl;
  }

  if (iPort == 6001) {
    LOG(INFO) <<  "-E- old event server (port no. 6001) running on DAQ frontend not yet supported"
         << FairLogger::endl;
    LOG(INFO) <<  "    use stream server (port no. 6002) and remote event server (port no. 6003)"
         << FairLogger::endl;
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
    LOG(INFO) <<  "-I- open connection to server " << pNode
         << ":" << iPort << FairLogger::endl;

    pTSocket = new TSocket(pNode, iPort);
    if ( !pTSocket->IsValid() ) {
      LOG(INFO) <<  "-E- open connection to server " << pNode
           << " failed" << FairLogger::endl;
      return(0);
    }
    LOG(INFO) <<  "    connection to server " << pNode
         << ":" << iPort << " okay" << FairLogger::endl;

    iSocket = pTSocket->GetDescriptor();
    imySig = iSocket;
    if (iDebug == 1) {
      LOG(DEBUG) <<  "    socket " << iSocket << FairLogger::endl;
    }

  } else if (iDebug == 1) {
    LOG(DEBUG) <<  "-D- socket " << iSocket << FairLogger::endl;
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

REvent* MRevBuffer::RevGet(TSocket* pSocket, Int_t iFlush, Int_t)
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
  //srevInfo sInfo = {.iSize=0, .iMode=1, .iHeadPar=0 , .iTimeOut=0 };
  /** To support C++98  we have to put the initializers in the right order without the names*/
  srevInfo sInfo = {0, 1, 0 ,0 };
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
      LOG(DEBUG) <<  "-D- commbuf (data size " << ntohl(sComm.iSize)
           << " byte): mode(1) " << ntohl(sComm.iMode)
           << ", request " <<  ntohl(sComm.iBufRequ)
           << " event buffer(s)" << FairLogger::endl;

    // request event buffer from server
    ilen = pSocket->SendRaw(piComm, iCommSize, kDefault);
    if (ilen < 0) {
      LOG(INFO) <<  "-E- sending request for events to server, rc = "
           << ilen << FairLogger::endl;
      iError = 1;
      goto gEndGet;
    }

    if (iDebug == 1)
      LOG(DEBUG) <<  "    communication buffer sent (request info buffer) "
           << FairLogger::endl;

    // receive info buffer from server
    piInfo = &(sInfo.iSize);
    ilen = pSocket->RecvRaw(piInfo, iInfoSize, kDefault);
    if (ilen < 0) {
      LOG(INFO) <<  "-E- receiving info buffer from server, rc = "
           << ilen << FairLogger::endl;
      iError = 1;
      goto gEndGet;
    }

    iHeadPar = ntohl(sInfo.iHeadPar);
    iTimeOut = ntohl(sInfo.iTimeOut);
    if (iDebug == 1) {
      LOG(DEBUG) <<  "-D- info buffer received:" << FairLogger::endl;
      LOG(DEBUG) <<  "    size data " << ntohl(sInfo.iSize)
           << ", mode (1) " << ntohl(sInfo.iMode)
           << ", header parms " << iHeadPar
           << ", timeout " << iTimeOut << FairLogger::endl;
    }

    if ( (ntohl(sInfo.iMode) != 1) ||
         ( (int) ntohl(sInfo.iSize) != iInfoSize-iint) ) {
      LOG(INFO) <<  "-E- invalid info buffer received: " << FairLogger::endl;
      LOG(INFO) <<  "    size data ( " << iInfoSize-iint
           << ") "  << ntohl(sInfo.iSize)
           << ", mode (1) " << ntohl(sInfo.iMode)
           << ", header parms " << iHeadPar
           << ", timeout " << iTimeOut << FairLogger::endl;
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
        LOG(DEBUG) <<  "-D- skip current buffer" << FairLogger::endl;
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
            LOG(DEBUG) <<  "-D- request new buffer" << FairLogger::endl;
          }
          inew = 1;
          if (iDebug == -1) {
            piNextEvt += iEvtPar;         // skip previous event
            LOG(DEBUG) <<  "-D- next 40 2byte-words of buffer:" << FairLogger::endl;
            psNextEvt = (short*) piNextEvt;
            for (Int_t iii=0; iii<40; iii++) {
              LOG(DEBUG) <<  "    " << iii+1 << ": " << psNextEvt[iii]
                   << FairLogger::endl;
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
      LOG(INFO) <<  "-E- sending request for buffer " << iBufNo+1
           << " to server, rc = " << ilen << FairLogger::endl;
      iError = 1;
      goto gEndGet;
    }

    if (imySig == -1) { goto gEndGet; }

    if (iDebug == 1)
      LOG(DEBUG) <<  "-D- communication buffer sent (request next buffer) "
           << FairLogger::endl;

gRetryLen:
    // get size of data following
    piBuf[0] = -1;                         // enables receive check
    iSize = iint;
    pcBuf = (char*) piBuf;
    while(iSize > 0) {
      if ( (imySig == -1) && (iDebug) ) {
        LOG(DEBUG) <<  "    CTL C detected (before recv len)" << FairLogger::endl;
      }
gNextRecvL:
      iRC = recv(iSocket, pcBuf, iSize, 0);
      if (iRC < 0) {
        if (imySig == -1) {
          if (iDebug) {
            sprintf(cMsg,
                    "\n-E- receiving data length from server");
            perror(cMsg);
            LOG(DEBUG) <<  "    CTL C detected (during recv len)"
                 << FairLogger::endl;
          }
          goto gNextRecvL;
        } else {                                 // a real problem
          sprintf(cMsg, "\n-E- receiving data length from server");
          perror(cMsg);
          if (iDebug) { LOG(DEBUG) <<  "    retry" << FairLogger::endl; }

          iRetryRecv++;      // count no. of retries to limit them
          if (iRetryRecv > iRetryRecvLim) { // avoid infinite loop
            iError = 1;
            goto gEndGet;
          } else { goto gNextRecvL; }
        }
      }
      if ( iRC == 0 ) {
        if ( (iDebug == 2) || (iDebug == 3) ) {
          LOG(DEBUG) <<  FairLogger::endl;
        }
        LOG(INFO) <<  "-E- receiving data length: connection closed by server"
             << FairLogger::endl;
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
      LOG(DEBUG) <<  "    CTL C detected (after recv len)" << FairLogger::endl;
    }

    iBufSize = ntohl(piBuf[0]);
    if (iDebug == 1) {
      LOG(DEBUG) <<  "    data size received: " << iBufSize << FairLogger::endl;
    }

    if (iBufSize <= 0) {
      if (iBufSize == 0) {
        if (iDebug) {
          LOG(DEBUG) <<  FairLogger::endl;
        }
        LOG(INFO) <<  "-W- server closed connection" << FairLogger::endl;
        LOG(INFO) <<  "    " << iEvtNo << " of " << iEvtMax
             << " events received" << FairLogger::endl;
        iError = 1;
        goto gEndGet;
      }

      if (iBufSize == -1) {
        if (iRetryFirst) {
          LOG(INFO) <<  FairLogger::endl << "-E- no data length received: ";
          iRetryFirst = 0;
        }
        iRetry++;
        if (iRetry > iRetryMax) {
          LOG(INFO) <<  iRetryMax << "times" << FairLogger::endl;
          iError = 1;
          goto gEndGet;
        }
        goto gRetryLen;
      } else {
        LOG(INFO) <<  FairLogger::endl << "-E- invalid data length received: "
             << iBufSize << FairLogger::endl;
        iError = 1;
      }

      goto gEndGet;
    }
    if (iRetry) {
      LOG(INFO) <<  iRetry << "times" << FairLogger::endl;
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
        LOG(DEBUG) <<  "-I- total buffer increased to "
             << iBufSizeAlloc << " byte" << FairLogger::endl;
    }

    // get event buffer without length field
    piBuf[1] = -1;                         // enables receive check
    iSize = iBufSize;
    pcBuf = (char*) &(piBuf[1]);
    while(iSize > 0) {
      if ( (imySig == -1) && (iDebug) ) {
        LOG(DEBUG) <<  "    CTL C detected (before recv data)" << FairLogger::endl;
      }
gNextRecvD:
      iRC = recv(iSocket, pcBuf, iSize, 0);
      if (iRC < 0) {
        if (imySig == -1) {
          if (iDebug) {
            sprintf(cMsg, "\n-E- receiving data from server");
            perror(cMsg);
            LOG(DEBUG) <<  "    CTL C detected (during recv data)"
                 << FairLogger::endl;
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
          LOG(DEBUG) <<  FairLogger::endl;
        }
        LOG(INFO) <<  "-E- receiving data: connection closed by server"
             << FairLogger::endl;
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
        LOG(DEBUG) <<  "    CTL C detected (after recv data)" << FairLogger::endl;
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
        if (iDebug == 3) { LOG(INFO) <<  FairLogger::endl; }
        LOG(DEBUG) <<  "*** connection to remote event server okay, but currently no DAQ events ("
             << iBufNoServ << ")" << FairLogger::endl;
        iStatus = 3;
        goto gRetryLen;
      } else {
        LOG(INFO) <<  "-E- invalid event number in dummy buffer no. "
             << iBufNoServ << ": "
             << iEvtBuf << " (expected: 0)" << FairLogger::endl;
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
        LOG(DEBUG) <<  "    Event data swapped" << FairLogger::endl;
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
      LOG(DEBUG) <<  FairLogger::endl << "buffer " << iBufNo
           << " (" << iBufNoServ << "): "
           << " size "
           << iBufSize << " byte" << FairLogger::endl;
      if (pFrag->cBuf_fragBegin) {
        LOG(DEBUG) <<  "    last event fragment" << FairLogger::endl;
      }
      if (pFrag->cBuf_fragEnd) {
        LOG(DEBUG) <<  "    first event fragment" << FairLogger::endl;
      }
      LOG(DEBUG) <<  "    buffer contains " << iEvtBuf << " elements"
           << FairLogger::endl;
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
      LOG(DEBUG) <<  "-D- first 50 2byte-words of buffer:" << FairLogger::endl;
      psNextEvt = (short*) &piBuf[1];
      for (Int_t iii=0; iii<50; iii++) {
        LOG(DEBUG) <<  "    " << iii+1 << ": " << psNextEvt[iii] << FairLogger::endl;
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
    LOG(DEBUG) <<  "    evt " << iEvtNo << " (" << piNextEvt[3]
         << "), len " << pEvtHead->iMbsEv101_dlen
         << ", type " << pEvtHead->sMbsEv101_type
         << "." << pEvtHead->sMbsEv101_subtype
         << ", trigger " << pEvtHead->sMbsEv101_trigger;
    LOG(DEBUG) <<  ", SE1 len " << iselen1
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
//      LOG(DEBUG) <<  ", SE" << ii << " " << iselen
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
//    LOG(DEBUG) <<  FairLogger::endl;
  }

  // fill event header
  iHead[0] = piNextEvt[0];                      // event length
  iHead[1] = piNextEvt[3];                      // event number
  pEvt->ReFillHead(iHead);

  // fill event data
  pEvt->ReFillData(piNextEvt);

  if (imySig == -1) {
    LOG(INFO) <<  FairLogger::endl << "-D- CTL C specified";
    if (iDebug) { LOG(DEBUG) <<  " (at end RevGet)" << FairLogger::endl; }
    else { LOG(INFO) <<  FairLogger::endl; }
    goto gEndGet;
  }

  if (iEvtNo == iEvtMax) {
    LOG(INFO) <<  FairLogger::endl << "-I- all required events ("
         << iEvtMax << ") received: " << iBufNo << " buffers ("
         << iBufNo1 << " - " << iBufNo2 << ")" << FairLogger::endl;
    LOG(INFO) <<  "    fragments found: " << iFragBeginIgn << " begin, "
         << iFragEndIgn << " end" << FairLogger::endl;
    if (iFragConc)
      LOG(INFO) <<  "    " << iFragConc
           << " events not concatenated from fragments" << FairLogger::endl;
  }

  iStatus = 0;                      // last event request successfull
  return(pEvt);

gEndGet:
  if ( (iError) || (imySig == -1) ) {
    if (iDebug) {
      LOG(DEBUG) <<  "    RevGet: closing connection to server";
    }
    iRC = rclose(&iSocket, 2);
    if ( (iDebug) && (iRC == 0) ) {
      LOG(DEBUG) <<  " - done" << FairLogger::endl;
    }

    if (imySig == -1) { iStatus = 5; }          // user break (CTL C)
    else { iStatus = 6; }                       // failure
    imySig = 0;                             // notify CTL C handler
  } else if (iDebug == 1) {
    LOG(DEBUG) <<  "    RevGet: keeping connection to server" << FairLogger::endl;
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
      LOG(INFO) <<  "-I- *** Last request for events was successfull"
           << FairLogger::endl;
      break;
    case 1:
      LOG(INFO) <<  "-I- *** Remote event server not yet connected"
           << FairLogger::endl;
      break;
    case 2:
      LOG(INFO) <<  "-I- *** Remote event server connected, but still no request for events"
           << FairLogger::endl;
      break;
    case 3:
      LOG(INFO) <<  "-I- *** Connection to remote event server okay, but currently no DAQ events"
           << FairLogger::endl;
      break;
    case 4:
      LOG(INFO) <<  "-I- *** Connection to remote event server closed"
           << FairLogger::endl;
      break;
    case 5:
      LOG(INFO) <<  "-I- *** Connection to remote event server closed after user break (CTL C)"
           << FairLogger::endl;
      break;
    case 6:
      LOG(INFO) <<  "-I- *** Connection to remote event server closed after failure"
           << FairLogger::endl;
      break;
    default:
      LOG(INFO) <<  "-E- Invalid status remote event server found: "
           << iStatus << FairLogger::endl;
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
    LOG(DEBUG) <<  "-D- send close request (data size "
         << ntohl(sComm.iSize) << " byte): "
         << ntohl(sComm.iMode) << ", "
         << ntohl(sComm.iBufRequ) << FairLogger::endl;

  iRC = pSocket->SendRaw(piComm, iCommSize, kDefault);
  if (iRC < 0)
    LOG(INFO) <<  "-E- sending close request to server, rc = "
         << iRC << FairLogger::endl;
  else if (iDebug == 1) {
    LOG(DEBUG) <<  "    close request sent" << FairLogger::endl;
  }

  if (iDebug) {
    LOG(DEBUG) <<  "    RevClose: closing connection to server";
  }
  iRC = rclose(&iSocket, 2);
  if ( (iDebug) && (iRC == 0) ) {
    LOG(DEBUG) <<  " - done" << FairLogger::endl;
  }

  iStatus = 4;                        // connection to server closed
  imySig = 0;                         // notify CTL C handler
  LOG(INFO) <<  "-I- connection to server closed" << FairLogger::endl;

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
  // LOG(INFO) <<  "    REvent() ..." << FairLogger::endl;
//  iNumb = 0;
//  piData = 0;
}

REvent::~REvent()
{
  // LOG(INFO) <<  "    ~REvent() ..." << FairLogger::endl;
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
    LOG(INFO) <<  "-E- event parameter number " << iChan
         << " out of range (" << (iSize+4)/( (signed) sizeof(short))
         << " long words)" << FairLogger::endl;
    return(-1);
  }
  pint = piData;
  iValue = pint[iChan-1];
  //LOG(INFO) <<  "    param " <<  iChan << ": " << iValue << FairLogger::endl;
  return iValue;
}
