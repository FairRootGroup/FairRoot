/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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
// MRevBuffer.h
//   description of class MRevBuffer
//   ROOT client package for multithreaded remote event server (MBS)
//////////////////////////////////////////////////////////////////////
// 20. 8.1999, H.G.: MRevBuffer::RevGetI added
//  6. 3.2000, H.G.: new member function RevStatus
//////////////////////////////////////////////////////////////////////

#ifndef MRevBuffer_H
#define MRevBuffer_H

#include <Rtypes.h>    // for Int_t, ClassDef, etc
#include <TObject.h>   // for TObject

class TSocket;

class REvent : public TObject
{
  private:
    Int_t iSize;     // event size (byte)
    Int_t iNumb;     // event number
    Int_t* piData;   // event parameter

    REvent(const REvent&);
    REvent& operator=(const REvent&);

  public:
    REvent();
    ~REvent() override = default;

    void ReFillHead(Int_t* pHead);   // unpack and fill event header
    void ReFillData(Int_t* pData);   // unpack and fill event data

    Int_t ReGetNumb();              // get event number
    Int_t ReGetSize();              // get event size
    Int_t ReGetData(Int_t ichan);   // get event parameter ichan
    Int_t* GetData() { return piData; }

    Int_t nSubEvt;
    Int_t subEvtSize[100];
    Short_t subEvtType[100];
    Short_t subEvtSubType[100];
    Short_t subEvtProcId[100];
    Short_t subEvtSubCrate[100];
    Short_t subEvtControl[100];
    Int_t* pSubEvt[100];

    ClassDefOverride(REvent, 0);
};

class MRevBuffer : public TObject
{
  private:
    TSocket* pTSocket;   // ptr socket of channel to event server
    Int_t iSocket;       // socket id of channel to event server
    Int_t iBufNo1;       // first buffer no. received (test)
    Int_t iBufNo2;       // last buffer no. received (test)
    Int_t iDebug;        // verbosity level (test)
    Int_t iSwap;         // > 0: swap event data
    Int_t iStatus;       // current status of server

    Int_t iBufSizeAlloc;   // allocated buffer size
    Int_t iBufSize;        // size current buffer
    Int_t iBufNo;          // current buffer no.
    Int_t iFragBegin;      // > 0: last buffer ended with fragment
    Int_t iFragConc;       // no. of concatenated fragments
    Int_t iFragBeginIgn;   // no. of ignored fragment begins
    Int_t iFragEndIgn;     // no. of ignored fragment ends

    Int_t iHeadPar;     // no. of (4 byte) parms buffer header
    Int_t iEvtMax;      // no. of events requested
    Int_t iEvtNo;       // last event no. handled
    Int_t iEvtRel;      // rel. event no. in buffer
    Int_t iEvtBuf;      // no. of events in current buffer
    Int_t iEvtPar;      // no. of parameters in event (incl. len)
    Int_t* piBuf;       // ptr event buffer
    Int_t* piNextEvt;   // ptr first element next event
    REvent* pEvt;       // ptr event class

    MRevBuffer(const MRevBuffer&);
    MRevBuffer& operator=(const MRevBuffer&);

  public:
    MRevBuffer(Int_t iMode);   // constructor
    ~MRevBuffer() override;

    TSocket* RevOpen(char* pNode, Int_t iPort, Int_t iEvent);
    // input: node name and port number server, req. no. of events
    // returns Socket ptr of server connection

    Int_t* RevGetI(TSocket* pSocket, Int_t iFlush);
    // get next event (pointer) from buffer, input:
    // Socket ptr,
    // iFlush = 1: skip current buffer (not impl)

    REvent* RevGet(TSocket* pSocket, Int_t iFlush, Int_t iSkip);
    // get next event (pointer) from buffer, input:
    // Socket ptr,
    // iFlush = 1: skip current buffer (not impl)
    // iSkip > 0: take only each iSkip event (not impl)

    Int_t RevStatus(Int_t iOut);
    // get status information (iOut = 1: also message to stdout)
    // = 0: last event request successfull
    // = 1: server not yet connected
    // = 2: server connected, but still no request for events
    // = 3: server connection okay, but currently no DAQ events
    // = 4: connection to server closed
    // = 5: connection to server closed after user break (CTL C)
    // = 6: connection to server closed after failure

    void RevBufWait(Int_t iWait);
    // wait for iWait seconds

    Int_t RevBufsize();
    // get size of current buffer (byte)

    void RevClose(TSocket* pSocket);   // input Socket ptr

    ClassDefOverride(MRevBuffer, 0);
};

#endif   // !MRevBuffer_H
