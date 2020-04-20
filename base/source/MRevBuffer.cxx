/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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

#include "MRevBuffer.h"   // class definition

#include <TSocket.h>      // for TSocket, etc
#include <netinet/in.h>   // IWYU pragma: keep
#include <signal.h>       // IWYU pragma: keep
#include <time.h>         // IWYU pragma: keep
#include <unistd.h>       // IWYU pragma: keep

#ifdef Linux
#include <select.h>       // IWYU pragma: keep
#include <socket.h>       // IWYU pragma: keep
#else                     // AIX
#include <strings.h>      // IWYU pragma: keep
#include <sys/select.h>   // IWYU pragma: keep
#include <sys/socket.h>   // IWYU pragma: keep
#endif

#include "ptrevcomm.h"     // communication structure
#include "ptrevmbsdef.h"   // MBS data definitions

// IWYU pragma: no_include <stdio.h>
// IWYU pragma: no_include <sys/_endian.h>
// IWYU pragma: no_include <sys/signal.h>

#include "FairLogger.h"

ClassImp(MRevBuffer);
ClassImp(REvent);

extern "C"
{
    long swaplw(int*, int, int);   // swap data
    void exitCli(int);             // handle CTL C
    int rclose(int*, int);         // close connection to server
}

#ifdef Linux
struct timeval
{
    long tv_sec;
    long tv_usec;
};
#endif

int iTimeOut;       // needed in exitCli to handle CTL C
int imySig = 0;     // needed in exitCli to handle CTL C
int iOutMode = 0;   // needed in exitCli to handle CTL C

MRevBuffer::MRevBuffer(Int_t iMode)
    : TObject()
    , pTSocket(nullptr)
    , iSocket(0)
    , iBufNo1(0)
    , iBufNo2(0)
    , iDebug(iMode)
    , iSwap(0)
    , iStatus(1)
    , iBufSizeAlloc(512000)
    , iBufSize(0)
    , iBufNo(0)
    , iFragBegin(0)
    , iFragConc(0)
    , iFragBeginIgn(0)
    , iFragEndIgn(0)
    , iHeadPar(0)
    , iEvtMax(0)
    , iEvtNo(0)
    , iEvtRel(0)
    , iEvtBuf(0)
    , iEvtPar(0)
    , piBuf(new int[iBufSizeAlloc / sizeof(int) + 1])
    , piNextEvt(nullptr)
    , pEvt(new REvent())
{
    //  iStatus = 1;                         // server not yet connected
    /*
    iSwap = 0;
    iSocket = 0;
    iEvtRel = 0;
    iEvtPar = 0;
    iBufSize = 0;
  */

    signal(SIGINT, exitCli);   // from now catch CTL C

    //  iDebug = iMode;
    iOutMode = iMode;
    if (iDebug == 1) {
        LOG(debug) << "-I- client runs in debug mode (1)";
    } else if (iDebug == 2)
        LOG(debug) << "-I- client shows buffer numbers and select/receive (mode 2)";
    else if (iDebug == 3) {
        LOG(debug) << "-I- client shows buffer numbers (mode 3)";
    } else if (iDebug == 5) {
        LOG(debug) << "-I- client shows event parameters (mode 5)";
    }

    if (iDebug == 1) {
        LOG(debug) << "    check ENDIAN, ";
#ifdef _AIX
        LOG(debug) << " should be BIG_ENDIAN: ";
#endif
#ifdef Linux
        LOG(debug) << " should be LITTLE_ENDIAN: ";
#endif

#ifdef BIG__ENDIAN
        LOG(debug) << " BIG_ENDIAN";
#else
        LOG(debug) << " LITTLE_ENDIAN";
#endif
    }

    //  iBufSizeAlloc = 16384;
    //  piBuf = new int [iBufSizeAlloc/sizeof(int)+1]; // 16k buffer + len
    if (iDebug == 1)
        LOG(debug) << "-D- buffer allocated (" << iBufSizeAlloc + sizeof(int) << " byte)";

    //  REvent* pev = new REvent();    // create event (once)
    //  pEvt = pev;                    // keep pointer in class MRevBuffer

    // LOG(info) <<  "    MRevBuffer() executed";

}   // constructor

MRevBuffer::~MRevBuffer()
{
    // LOG(info) <<  "    ~MRevBuffer() ...";
    delete[] piBuf;
    piNextEvt = 0;
    pEvt->~REvent();
    // LOG(info) <<  "    ~MRevBuffer() executed";

}   // destructor

TSocket* MRevBuffer::RevOpen(char* pNode, Int_t iPort, Int_t iEvent)
{
    if (iEvent < 0) {
        LOG(info) << "-E- number of requested events (" << iEvent << ") invalid";
        return (0);
    }
    if (iEvent == 0) {
        iEvent = 2000000000;   // nearly unlimited
        LOG(info) << "-I- unlimited no. of MBS events requested - break with 'CTL C'";
    }

    if (iPort == 6001) {
        LOG(info) << "-E- old event server (port no. 6001) running on DAQ frontend not yet supported";
        LOG(info) << "    use stream server (port no. 6002) and remote event server (port no. 6003)";
        return (0);
    }
    if (iPort == 0) {
        iPort = 6003;
    }   // default MBS remote event server

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
        iEvtNo = -1;   // initialization (info buffer) required
        LOG(info) << "-I- open connection to server " << pNode << ":" << iPort;

        pTSocket = new TSocket(pNode, iPort);
        if (!pTSocket->IsValid()) {
            LOG(info) << "-E- open connection to server " << pNode << " failed";
            return (0);
        }
        LOG(info) << "    connection to server " << pNode << ":" << iPort << " okay";

        iSocket = pTSocket->GetDescriptor();
        imySig = iSocket;
        if (iDebug == 1) {
            LOG(debug) << "    socket " << iSocket;
        }

    } else if (iDebug == 1) {
        LOG(debug) << "-D- socket " << iSocket;
    }

    iStatus = 2;   // server connected
    return (pTSocket);

}   // RevOpen

Int_t* MRevBuffer::RevGetI(TSocket* pSocket, Int_t iFlush)
{
    Int_t* piEvent;
    REvent* pEvent;

    pEvent = RevGet(pSocket, iFlush, 0);
    if (pEvent) {
        piEvent = piNextEvt;
    } else {
        piEvent = 0;
    }
    return piEvent;

}   // RevGetI

REvent* MRevBuffer::RevGet(TSocket* pSocket, Int_t iFlush, Int_t)
{
    Int_t iint = sizeof(int);
    Int_t ii;
    Int_t ilen, iselen, iselen1, ielen, inew = 0;

    Short_t* pshort;

    Char_t cMsg[128] = "";
    Char_t* pcBuf;
    Int_t iSize, iRC;

    Int_t iError = 0;
    Int_t iRetry;
    Int_t iRetryMax = 1000;
    Int_t iRetryFirst;
    Int_t iRetryRecv = 0;      // count retries of recv call
    Int_t iRetryRecvLim = 1;   // max. no. of succeeding retries

    Int_t* piComm;
    srevComm sComm;
    Int_t iCommSize = sizeof(sComm);   // size comm. buffer (byte)

    Int_t* piInfo;
    // srevInfo sInfo = {.iSize=0, .iMode=1, .iHeadPar=0 , .iTimeOut=0 };
    /** To support C++98  we have to put the initializers in the right order without the names*/
    srevInfo sInfo = {0, 1, 0, 0};
    Int_t iInfoSize = sizeof(sInfo);   // size info buffer (byte)

    //    Int_t iHeadPar = 12;         // no. of params in MBS buffer header
    iHeadPar = 12;      // no. of params in MBS buffer header
    Int_t iBufNoServ;   // buffer no. sent from server
    short* psNextEvt;
    Int_t iHead[2];

    sMbsEv101 sEvtHead, *pEvtHead;   // header event 10.1
    pEvtHead = &sEvtHead;
    sMbsSev101 sSEvtHead, *pSEvtHead;   // header event 10.1
    pSEvtHead = &sSEvtHead;
    sMbsBufFrag sFrag, *pFrag;   // fragmented event flags
    pFrag = &sFrag;

    if (iEvtNo >= iEvtMax) {
        goto gEndGet;
    }

    piComm = &(sComm.iSize);                 // communication buffer
    sComm.iSize = htonl(iCommSize - iint);   // size of data following
    sComm.iMode = htonl(1);                  // required: get events
    sComm.iIdent = 1;                        // required: tell endian type
    sComm.iBufRequ = htonl(1);               // send one buffer

    // initialize communication with server
    if (iEvtNo == -1) {   // initialize communication with server
        if (iDebug == 1)
            LOG(debug) << "-D- commbuf (data size " << ntohl(sComm.iSize) << " byte): mode(1) " << ntohl(sComm.iMode)
                       << ", request " << ntohl(sComm.iBufRequ) << " event buffer(s)";

        // request event buffer from server
        ilen = pSocket->SendRaw(piComm, iCommSize, kDefault);
        if (ilen < 0) {
            LOG(info) << "-E- sending request for events to server, rc = " << ilen;
            iError = 1;
            goto gEndGet;
        }

        if (iDebug == 1)
            LOG(debug) << "    communication buffer sent (request info buffer) ";

        // receive info buffer from server
        piInfo = &(sInfo.iSize);
        ilen = pSocket->RecvRaw(piInfo, iInfoSize, kDefault);
        if (ilen < 0) {
            LOG(info) << "-E- receiving info buffer from server, rc = " << ilen;
            iError = 1;
            goto gEndGet;
        }

        iHeadPar = ntohl(sInfo.iHeadPar);
        iTimeOut = ntohl(sInfo.iTimeOut);
        if (iDebug == 1) {
            LOG(debug) << "-D- info buffer received:";
            LOG(debug) << "    size data " << ntohl(sInfo.iSize) << ", mode (1) " << ntohl(sInfo.iMode)
                       << ", header parms " << iHeadPar << ", timeout " << iTimeOut;
        }

        if ((ntohl(sInfo.iMode) != 1) || (static_cast<int>(ntohl(sInfo.iSize)) != iInfoSize - iint)) {
            LOG(info) << "-E- invalid info buffer received: ";
            LOG(info) << "    size data ( " << iInfoSize - iint << ") " << ntohl(sInfo.iSize) << ", mode (1) "
                      << ntohl(sInfo.iMode) << ", header parms " << iHeadPar << ", timeout " << iTimeOut;
            iError = 1;
            goto gEndGet;
        }

        iEvtNo = 0;   // initilization done
        inew = 1;     // request new buffer

    }   // (iEvtNo == -1)
    else {
        if (iFlush) {
            inew = 1;   // request new buffer
            if (iDebug == 1) {
                LOG(debug) << "-D- skip current buffer";
            }
        } else {
            if (iEvtNo >= 0) {
                // refresh some buffer infos not stored in class data
                pFrag = reinterpret_cast<sMbsBufFrag*>(&piBuf[3]);

                // check if new buffer needed
                ii = 0;   // count buffer header
                if (pFrag->cBuf_fragBegin) {
                    ii++;
                }
                if (pFrag->cBuf_fragEnd) {
                    ii++;
                }

                if (iEvtRel + ii >= iEvtBuf) {
                    if (iDebug == 1) {
                        LOG(debug) << "-D- request new buffer";
                    }
                    inew = 1;
                    if (iDebug == -1) {
                        piNextEvt += iEvtPar;   // skip previous event
                        LOG(debug) << "-D- next 40 2byte-words of buffer:";
                        psNextEvt = reinterpret_cast<short*>(piNextEvt);
                        for (Int_t iii = 0; iii < 40; iii++) {
                            LOG(debug) << "    " << iii + 1 << ": " << psNextEvt[iii];
                        }
                    }
                } else {
                    inew = 0;
                }

            }   // (iEvtNo > 0)
        }       // (!iFlush)
    }           // (iEvtNo != -1)

    // request new buffer
    if (inew) {
        iEvtRel = 0;
        iRetry = 0;
        iRetryFirst = 1;
        if (imySig == -1) {
            sComm.iBufRequ = htonl(0);   // signal finish to server
        }

        // request next buffer or finish
        ilen = pSocket->SendRaw(piComm, iCommSize, kDefault);
        if (ilen < 0) {
            LOG(info) << "-E- sending request for buffer " << iBufNo + 1 << " to server, rc = " << ilen;
            iError = 1;
            goto gEndGet;
        }

        if (imySig == -1) {
            goto gEndGet;
        }

        if (iDebug == 1)
            LOG(debug) << "-D- communication buffer sent (request next buffer) ";

    gRetryLen:
        // get size of data following
        piBuf[0] = -1;   // enables receive check
        iSize = iint;
        pcBuf = reinterpret_cast<char*>(piBuf);
        while (iSize > 0) {
            if ((imySig == -1) && (iDebug)) {
                LOG(debug) << "    CTL C detected (before recv len)";
            }
        gNextRecvL:
            iRC = recv(iSocket, pcBuf, iSize, 0);
            if (iRC < 0) {
                if (imySig == -1) {
                    if (iDebug) {
                        sprintf(cMsg, "\n-E- receiving data length from server");
                        perror(cMsg);
                        LOG(debug) << "    CTL C detected (during recv len)";
                    }
                    goto gNextRecvL;
                } else {   // a real problem
                    sprintf(cMsg, "\n-E- receiving data length from server");
                    perror(cMsg);
                    if (iDebug) {
                        LOG(debug) << "    retry";
                    }

                    iRetryRecv++;                       // count no. of retries to limit them
                    if (iRetryRecv > iRetryRecvLim) {   // avoid infinite loop
                        iError = 1;
                        goto gEndGet;
                    } else {
                        goto gNextRecvL;
                    }
                }
            }
            if (iRC == 0) {
                if ((iDebug == 2) || (iDebug == 3)) {
                    LOG(debug) << "\n";
                }
                LOG(info) << "-E- receiving data length: connection closed by server";
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

        if ((imySig == -1) && (iDebug)) {
            LOG(debug) << "    CTL C detected (after recv len)";
        }

        iBufSize = ntohl(piBuf[0]);
        if (iDebug == 1) {
            LOG(debug) << "    data size received: " << iBufSize;
        }

        if (iBufSize <= 0) {
            if (iBufSize == 0) {
                if (iDebug) {
                    LOG(debug) << "\n";
                }
                LOG(info) << "-W- server closed connection";
                LOG(info) << "    " << iEvtNo << " of " << iEvtMax << " events received";
                iError = 1;
                goto gEndGet;
            }

            if (iBufSize == -1) {
                if (iRetryFirst) {
                    LOG(info) << "\n"
                              << "-E- no data length received: ";
                    iRetryFirst = 0;
                }
                iRetry++;
                if (iRetry > iRetryMax) {
                    LOG(info) << iRetryMax << "times";
                    iError = 1;
                    goto gEndGet;
                }
                goto gRetryLen;
            } else {
                LOG(info) << "\n"
                          << "-E- invalid data length received: " << iBufSize;
                iError = 1;
            }

            goto gEndGet;
        }
        if (iRetry) {
            LOG(info) << iRetry << "times";
        }

        // increase data buffer, if necessary
        if (iBufSize + iint > iBufSizeAlloc) {
            delete[] piBuf;
            iBufSizeAlloc = iBufSize + iint;
            // new total buffer size (including length field)
            piBuf = new int[iBufSizeAlloc / iint];
            piBuf[0] = iBufSize;
            // keep sent buffer size (without length field)
            if (iDebug == 1)
                LOG(debug) << "-I- total buffer increased to " << iBufSizeAlloc << " byte";
        }

        // get event buffer without length field
        piBuf[1] = -1;   // enables receive check
        iSize = iBufSize;
        pcBuf = reinterpret_cast<char*>(&(piBuf[1]));
        while (iSize > 0) {
            if ((imySig == -1) && (iDebug)) {
                LOG(debug) << "    CTL C detected (before recv data)";
            }
        gNextRecvD:
            iRC = recv(iSocket, pcBuf, iSize, 0);
            if (iRC < 0) {
                if (imySig == -1) {
                    if (iDebug) {
                        sprintf(cMsg, "\n-E- receiving data from server");
                        perror(cMsg);
                        LOG(debug) << "    CTL C detected (during recv data)";
                    }
                    goto gNextRecvD;
                } else {   // a real problem
                    sprintf(cMsg, "\n-E- receiving data from server");
                    perror(cMsg);

                    iRetryRecv++;                       // count no. of retries to limit them
                    if (iRetryRecv > iRetryRecvLim) {   // avoid infinite loop
                        iError = 1;
                        goto gEndGet;
                    } else {
                        goto gNextRecvD;
                    }
                }
            }
            if (iRC == 0) {
                if ((iDebug == 2) || (iDebug == 3)) {
                    LOG(debug) << "\n";
                }
                LOG(info) << "-E- receiving data: connection closed by server";
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
                LOG(debug) << "    CTL C detected (after recv data)";
            }
            goto gEndGet;
        }

        // test for dummy buffer (no DAQ events available)
        if (iBufSize == (sizeof(sptrevDummy) - sizeof(int))) {
            iBufNoServ = ntohl(piBuf[1]);
            iEvtBuf = ntohl(piBuf[2]);
            if (iEvtBuf == 0) {
                if (iDebug == 1)
                    printf("    dummy buffer no. %d, %d events\n", iBufNoServ, iEvtBuf);
                if (iDebug == 3) {
                    LOG(info) << "\n";
                }
                LOG(debug) << "*** connection to remote event server okay, but currently no DAQ events (" << iBufNoServ
                           << ")";
                iStatus = 3;
                goto gRetryLen;
            } else {
                LOG(info) << "-E- invalid event number in dummy buffer no. " << iBufNoServ << ": " << iEvtBuf
                          << " (expected: 0)";
                iError = 1;
                goto gEndGet;
            }
        }

        if (!iSwap) {
            if (piBuf[9] != 1) {
                iSwap = 1;
            }
        }

        //  Long_t lRC;

        /* swap MBS buffer */
        if (iSwap) {
            //      lRC  = swaplw( &piBuf[1], iBufSize/iint, 0);
            swaplw(&piBuf[1], iBufSize / iint, 0);
            if ((iBufNo == 0) && (iDebug)) {
                LOG(debug) << "    Event data swapped";
            }
        }

        iBufNo++;
        iBufNoServ = piBuf[4];
        iEvtBuf = piBuf[5];   // no. of events in current buffer

        if (iEvtNo == 0) {
            iBufNo = 1;             // restart counting
            iBufNo1 = iBufNoServ;   // keep first buffer no.
            iFragBegin = 0;
            iFragBeginIgn = 0;
            iFragEndIgn = 0;
            iFragConc = 0;
        }
        iBufNo2 = iBufNoServ;   // keep last buffer no.

        if (iDebug >= 2) {
            printf("%d:", iBufNoServ);
            fflush(stdout);
        }

        pFrag = reinterpret_cast<sMbsBufFrag*>(&piBuf[3]);
        if (iDebug == 1) {
            LOG(debug) << "\n"
                       << "buffer " << iBufNo << " (" << iBufNoServ << "): "
                       << " size " << iBufSize << " byte";
            if (pFrag->cBuf_fragBegin) {
                LOG(debug) << "    last event fragment";
            }
            if (pFrag->cBuf_fragEnd) {
                LOG(debug) << "    first event fragment";
            }
            LOG(debug) << "    buffer contains " << iEvtBuf << " elements";
        }

        if (pFrag->cBuf_fragEnd) {
            iFragEndIgn++;
            if ((iEvtNo > 0) && (iFragBegin)) {
                iFragConc++;
            }
        }

        if (pFrag->cBuf_fragBegin) {
            iFragBegin = 1;   // keep info for next buffer
            iFragBeginIgn++;
        }

        if (iDebug == -1) {
            LOG(debug) << "-D- first 50 2byte-words of buffer:";
            psNextEvt = reinterpret_cast<short*>(&piBuf[1]);
            for (Int_t iii = 0; iii < 50; iii++) {
                LOG(debug) << "    " << iii + 1 << ": " << psNextEvt[iii];
            }
        }

        iEvtRel = 1;                        // first event in buffer
        piNextEvt = piBuf + iHeadPar + 1;   // ptr first element in buffer
        iEvtPar = piNextEvt[0] / 2 + 2;     // no. of parameters new event

        if (pFrag->cBuf_fragEnd) {
            piNextEvt += iEvtPar;             // skip fragment end
            iEvtPar = piNextEvt[0] / 2 + 2;   // no. of parameters new event
        }

    }   // new buffer
    else {
        iEvtRel++;                        // event no. in buffer
        piNextEvt += iEvtPar;             // skip previous event
        iEvtPar = piNextEvt[0] / 2 + 2;   // no. of parameters new event

        // also if starting with current buffer: keep first buffer no.
        if (iEvtNo == 0) {
            iBufNo = 1;   // restart counting
            iBufNoServ = piBuf[4];
            iBufNo1 = iBufNoServ;

            iFragBegin = 0;
            iFragBeginIgn = 0;
            iFragEndIgn = 0;
            iFragConc = 0;
            pFrag = reinterpret_cast<sMbsBufFrag*>(&piBuf[3]);
            if (pFrag->cBuf_fragBegin) {
                iFragBegin = 1;   // keep info for next buffer
                iFragBeginIgn++;
            }
            if (pFrag->cBuf_fragEnd) {
                iFragEndIgn++;
            }

        }   // (iEvtNo == 0)
    }       // continue with current buffer

    iEvtNo++;   // total event no.
    psNextEvt = reinterpret_cast<short*>(piNextEvt);
    pEvtHead = reinterpret_cast<sMbsEv101*>(piNextEvt);
    ielen = pEvtHead->iMbsEv101_dlen;
    pSEvtHead = reinterpret_cast<sMbsSev101*>(&piNextEvt[4]);
    pshort = reinterpret_cast<short*>(pSEvtHead);

    pEvt->nSubEvt = 0;

    if ((iDebug == 1) || (iDebug == 5)) {
        iselen1 = pSEvtHead->iMbsSev101_dlen;

        pEvt->nSubEvt += 1;
        pEvt->subEvtSize[0] = pSEvtHead->iMbsSev101_dlen / 2 - 1;
        pEvt->subEvtType[0] = pSEvtHead->sMbsSev101_type;
        pEvt->subEvtSubType[0] = pSEvtHead->sMbsSev101_subtype;
        pEvt->subEvtProcId[0] = pSEvtHead->sMbsSev101_procid;
        pEvt->subEvtSubCrate[0] = pSEvtHead->cMbsSev101_subcrate;
        pEvt->subEvtControl[0] = pSEvtHead->cMbsSev101_control;
        pEvt->pSubEvt[0] = reinterpret_cast<Int_t*>(&pshort[6]);

        /*
    std::stringstream ss
    ss <<  "    evt " << iEvtNo << " (" << piNextEvt[3]
         << "), len " << pEvtHead->iMbsEv101_dlen
         << ", type " << pEvtHead->sMbsEv101_type
         << "." << pEvtHead->sMbsEv101_subtype
         << ", trigger " << pEvtHead->sMbsEv101_trigger;
    ss <<  ", SE1 len " << iselen1
         << " procid " << pSEvtHead->sMbsSev101_procid;
*/
        ielen -= (iselen1 + 8);

        ii = 1;
        iselen = iselen1;
        while (ielen > 0) {
            ii++;
            //          if (ii > 3) break;
            pshort += iselen + 4;
            pSEvtHead = reinterpret_cast<sMbsSev101*>(pshort);
            iselen = pSEvtHead->iMbsSev101_dlen;
            //      ss <<  ", SE" << ii << " " << iselen
            //           << " " << pSEvtHead->sMbsSev101_procid;
            ielen -= (iselen + 4);

            pEvt->nSubEvt += 1;
            pEvt->subEvtSize[ii - 1] = pSEvtHead->iMbsSev101_dlen / 2 - 1;
            pEvt->subEvtType[ii - 1] = pSEvtHead->sMbsSev101_type;
            pEvt->subEvtSubType[ii - 1] = pSEvtHead->sMbsSev101_subtype;
            pEvt->subEvtProcId[ii - 1] = pSEvtHead->sMbsSev101_procid;
            pEvt->subEvtSubCrate[ii - 1] = pSEvtHead->cMbsSev101_subcrate;
            pEvt->subEvtControl[ii - 1] = pSEvtHead->cMbsSev101_control;
            pEvt->pSubEvt[ii - 1] = reinterpret_cast<Int_t*>(&pshort[6]);
        }
        //    LOG(debug) << ss.str();
    }

    // fill event header
    iHead[0] = piNextEvt[0];   // event length
    iHead[1] = piNextEvt[3];   // event number
    pEvt->ReFillHead(iHead);

    // fill event data
    pEvt->ReFillData(piNextEvt);

    if (imySig == -1) {
        LOG(info) << "\n"
                  << "-D- CTL C specified";
        if (iDebug) {
            LOG(debug) << " (at end RevGet)";
        } else {
            LOG(info) << "\n";
        }
        goto gEndGet;
    }

    if (iEvtNo == iEvtMax) {
        LOG(info) << "\n"
                  << "-I- all required events (" << iEvtMax << ") received: " << iBufNo << " buffers (" << iBufNo1
                  << " - " << iBufNo2 << ")";
        LOG(info) << "    fragments found: " << iFragBeginIgn << " begin, " << iFragEndIgn << " end";
        if (iFragConc)
            LOG(info) << "    " << iFragConc << " events not concatenated from fragments";
    }

    iStatus = 0;   // last event request successfull
    return (pEvt);

gEndGet:
    if ((iError) || (imySig == -1)) {
        if (iDebug) {
            LOG(debug) << "    RevGet: closing connection to server";
        }
        iRC = rclose(&iSocket, 2);
        if ((iDebug) && (iRC == 0)) {
            LOG(debug) << " - done";
        }

        if (imySig == -1) {
            iStatus = 5;
        }   // user break (CTL C)
        else {
            iStatus = 6;
        }             // failure
        imySig = 0;   // notify CTL C handler
    } else if (iDebug == 1) {
        LOG(debug) << "    RevGet: keeping connection to server";
    }

    return 0;

}   // RevGet

Int_t MRevBuffer::RevBufsize() { return iBufSize; }   // RevBufsize

void MRevBuffer::RevBufWait(Int_t iWait)
{
    if (iWait > 0) {
        sleep(iWait);
    }
}   // RevBufWait

Int_t MRevBuffer::RevStatus(Int_t iOut)
{
    if (iOut)
        switch (iStatus) {
            case 0:
                LOG(info) << "-I- *** Last request for events was successfull";
                break;
            case 1:
                LOG(info) << "-I- *** Remote event server not yet connected";
                break;
            case 2:
                LOG(info) << "-I- *** Remote event server connected, but still no request for events";
                break;
            case 3:
                LOG(info) << "-I- *** Connection to remote event server okay, but currently no DAQ events";
                break;
            case 4:
                LOG(info) << "-I- *** Connection to remote event server closed";
                break;
            case 5:
                LOG(info) << "-I- *** Connection to remote event server closed after user break (CTL C)";
                break;
            case 6:
                LOG(info) << "-I- *** Connection to remote event server closed after failure";
                break;
            default:
                LOG(info) << "-E- Invalid status remote event server found: " << iStatus;
        }
    return iStatus;

}   // RevStatus

void MRevBuffer::RevClose(TSocket* pSocket)
{
    int iRC;
    Int_t* piComm;
    srevComm sComm;
    Int_t iCommSize = sizeof(sComm);   // size comm. buffer (byte)

    if (imySig < 0) {
        return;
    }   // CTL Y: connection closed elsewhere
    if (iSocket == 0) {
        return;
    }

    // tell server that no more events needed
    piComm = &(sComm.iSize);                        // communication buffer
    sComm.iSize = htonl(iCommSize - sizeof(int));   // size of data following
    sComm.iMode = htonl(1);                         // required: get events
    sComm.iIdent = 1;                               // required: tell endian type
    sComm.iBufRequ = htonl(0);                      // no more event buffers

    if (iDebug == 1)
        LOG(debug) << "-D- send close request (data size " << ntohl(sComm.iSize) << " byte): " << ntohl(sComm.iMode)
                   << ", " << ntohl(sComm.iBufRequ);

    iRC = pSocket->SendRaw(piComm, iCommSize, kDefault);
    if (iRC < 0)
        LOG(info) << "-E- sending close request to server, rc = " << iRC;
    else if (iDebug == 1) {
        LOG(debug) << "    close request sent";
    }

    if (iDebug) {
        LOG(debug) << "    RevClose: closing connection to server";
    }
    iRC = rclose(&iSocket, 2);
    if ((iDebug) && (iRC == 0)) {
        LOG(debug) << " - done";
    }

    iStatus = 4;   // connection to server closed
    imySig = 0;    // notify CTL C handler
    LOG(info) << "-I- connection to server closed";

}   // RevClose

/////////////////////////////////////////////////////////////////////

REvent::REvent()
    : TObject()
    , iSize(0)
    , iNumb(0)
    , piData(nullptr)
    , nSubEvt(0)
    , subEvtSize()
    , subEvtType()
    , subEvtSubType()
    , pSubEvt()
{
    // LOG(info) <<  "    REvent() ...";
    //  iNumb = 0;
    //  piData = 0;
}

REvent::~REvent()
{
    // LOG(info) <<  "    ~REvent() ...";
}

void REvent::ReFillHead(Int_t* pHead)
{
    iSize = pHead[0];   // event size without header in 2-byte-words
    iNumb = pHead[1];
}

void REvent::ReFillData(Int_t* pdata) { piData = pdata; }

Int_t REvent::ReGetNumb() { return iNumb; }

Int_t REvent::ReGetSize() { return iSize; }

Int_t REvent::ReGetData(Int_t iChan)
{
    Int_t iValue;
    Int_t* pint;

    // if ( (iChan < 1) || (iChan > iSize/( (signed) sizeof(int))) )
    if ((iChan < 1) || (iChan > (iSize + 4) / (static_cast<signed>(sizeof(short))))) {
        LOG(info) << "-E- event parameter number " << iChan << " out of range ("
                  << (iSize + 4) / (static_cast<signed>(sizeof(short))) << " long words)";
        return (-1);
    }
    pint = piData;
    iValue = pint[iChan - 1];
    // LOG(info) <<  "    param " <<  iChan << ": " << iValue;
    return iValue;
}
