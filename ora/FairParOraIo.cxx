//*-- AUTHOR : Ilse Koenig
//*-- Created : 25/11/2004 by I.Koenig

///////////////////////////////////////////////////////////////////////////////
// FairParOraIo
//
// Interface class to database Oracle
// It is derived from interface base class FairParIo.
///////////////////////////////////////////////////////////////////////////////

using namespace std;
#include "FairParOraIo.h"
#include "FairDetParIo.h"
#include "FairOraInfo.h"
#include "FairGenericParOraIo.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>

ClassImp(FairParOraIo)

FairParOraIo::FairParOraIo()
{
  // default constructor
  // creates the connection class but doesn't open a connection
  pConn=new FairOraConn();
  autoWritable=kFALSE;
}


FairParOraIo::~FairParOraIo()
{
  // default constructor closes an open connection
  close();
  if (pConn) { delete pConn; }
}


Bool_t FairParOraIo::open()
{
  // opens connection to the database db-cbm as user CBM_ANA_PUBLIC
  // user CBM_ANA_PUBLIC has Readonly access to Oracle tables
  // all open()-functions activate the detetctor I/Os
  isConnected=pConn->open();
  return activateDetIo();
}


Bool_t FairParOraIo::open(char* userName)
{
  // opens connection to the database db-cbm for user given by name
  // asks for password
  isConnected=pConn->open(userName);
  return activateDetIo();
}


Bool_t FairParOraIo::open(char* dbName, char* userName)
{
  // opens connection to the database with name dbName for user given by name
  // asks for password
  isConnected=pConn->open(dbName,userName);
  return activateDetIo();
}


Bool_t FairParOraIo::reconnect()
{
  // reopens the connection (only applicable for public user CBM_ANA_PUBLIC)
  isConnected=pConn->reconnect();
  return isConnected;
}


void FairParOraIo::close()
{
  // closes the connection with automatic ROLLBACK
  pConn->close();
  isConnected=kFALSE;
  if (detParIoList) { detParIoList->Delete(); }
  if (pInfo) {
    delete pInfo;
    pInfo=0;
  }
}


void FairParOraIo::disconnect()
{
  pConn->disconnect();
  isConnected=kFALSE;
}


void FairParOraIo::print()
{
  // prints information about the database connection
  pConn->print();
  if (isConnected) {
    TIter next(detParIoList);
    FairDetParIo* io;
    cout<<"detector I/Os: ";
    while ((io=(FairDetParIo*)next())) {
      cout<<" "<<io->GetName();
    }
    cout<<'\n';
  }
}

Bool_t FairParOraIo::setHistoryDate(const char* timestamp)
{
  // Sets the date to retrieve historic data
  // Returns kFALSE when the date string cannot be converted to a valid date.
  return pConn->setHistoryDate(timestamp);
}

Bool_t FairParOraIo::setParamRelease(const char* releaseName)
{
  // Sets the history date to the creation date of the parameter release give by name
  // Returns kFALSE when the release is not found.
  return pConn->setParamRelease(releaseName);
}

Bool_t FairParOraIo::activateDetIo()
{
  // creates the I/O for all detector in the setup
  if (isConnected==kFALSE) { return kFALSE; }
  pInfo=new FairOraInfo(pConn);
  FairDetParIo* io=new FairGenericParOraIo(pConn);
  detParIoList->Add(io);
  return kTRUE;
}

void FairParOraIo::setDetParIo(Text_t* ioName)
{
  // creates the specified I/O
  if (isConnected) {
    TObject* io=detParIoList->FindObject(ioName);
    if (!io) {
      if (strcmp(ioName,"FairGenericParIo")==0) { io=new FairGenericParOraIo(pConn); }
      if (io) { detParIoList->Add(io); }
    }
  }
}

TList* FairParOraIo::getListOfRuns(const char* project,
                                   const char* startAt,const char* endAt)
{
  // returns the list of runs for the specifies experiment and range
  // accepts dates (format DD-MON-YYYY HH24:MI:SS), filenames and run ids
  if (isConnected) {
    return pInfo->getListOfRuns(project,startAt,endAt);
  }
  Error("getListOfRuns","No connection to Oracle");
  return 0;
}
