/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBWRITER_H
#define FAIRDBWRITER_H

#include <list>
#include <string>

#include "FairDb.h"
#include "FairDbLogEntry.h"
#include "FairDbTableInterfaceStore.h"
#include "ValInterval.h"
#include "ValTimeStamp.h"

class FairDbSqlValidityData;
class FairDbTableInterface;
class FairDbValRecord;

template <class T> class FairDbWriter
{

  public:

    FairDbWriter();

    FairDbWriter(const ValInterval& vr,
                 Int_t aggNo,
                 FairDb::Version task,
                 ValTimeStamp creationDate,
                 const std::string& dbName,
                 const std::string& logComment = "",
                 const std::string& tableName = "");

    FairDbWriter(const ValInterval& vr,
                 Int_t aggNo,
                 FairDb::Version task = 0,
                 ValTimeStamp creationDate = ValTimeStamp(0,0),
                 UInt_t dbNo = 0,
                 const std::string& logComment = "",
                 const std::string& tableName = "");

    FairDbWriter(const FairDbValRecord& vrec,
                 const std::string& dbName,
                 const std::string& logComment = "");

    FairDbWriter(const FairDbValRecord& vrec,
                 UInt_t dbNo = 0,
                 const std::string& logComment = "");


    virtual ~FairDbWriter();

    FairDbTableInterface& TableInterface() const;

    Bool_t IsOpen(Bool_t reportErrors = kTRUE) const;
    Bool_t CanOutput(Bool_t reportErrors = kTRUE) const;

    void SetDbEntry(UInt_t dbNo) { fDbNo = dbNo;}
    void SetDbNo(UInt_t dbNo) { fDbNo = dbNo;}
    void SetDbName(const std::string& dbName);
    void SetLogComment(const std::string& reason);

    // Setters
    void SetComboNo(Int_t combo) {fAggregateNo = combo;}
    void SetVersion(FairDb::Version vers) {fVersion = vers;}
    void SetLogTitle(std::string logTitle) {fLogTitle=logTitle;}

    void SetRequireGlobalSeqno(Int_t requireGlobal) {fRequireGlobalSeqno = requireGlobal;}
    void SetOverlayCreationDate() {fUseOverlayCreationDate = kTRUE;}

    //  I/O functions
    void Abort() { Reset(); }
    Bool_t Close(const char* fileSpec=0);
    Bool_t Open(const ValInterval& vr,
                Int_t aggNo,
                FairDb::Version task,
                ValTimeStamp creationDate,
                const std::string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const ValInterval& vr,
                Int_t aggNo,
                FairDb::Version task = 0,
                ValTimeStamp creationDate = ValTimeStamp(),
                UInt_t dbNo = 0,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValRecord& vrec,
                const std::string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValRecord& vrec,
                UInt_t dbNo = 0,
                const std::string& logComment = "");

    Bool_t Activate(const ValInterval& vr,
                    Int_t aggNo = -2,
                    FairDb::Version vers = 0,
                    Int_t dbEntry = 0,
                    const std::string& logTitle = "",
                    ValTimeStamp creationDate = ValTimeStamp(0,0));

    void Reset();

    FairDbWriter<T>& operator<<(const T& row);

  private:

    Bool_t NeedsLogEntry() const;
    Bool_t WritingToMaster() const;

    FairDbWriter(const FairDbWriter&); // Do not use
    FairDbWriter& operator=(const FairDbWriter&); // Do not use

    void CompleteOpen(UInt_t dbNo = 0,
                      const std::string& logComment = "");


    static FairDbTableInterface& GetTableInterface();
    static FairDbTableInterface& GetTableInterface(const std::string& tableName);


    Int_t fAggregateNo;
    UInt_t fDbNo;
    FairDbSqlValidityData* fPacket;
    Int_t fRequireGlobalSeqno;
    FairDbTableInterface* fTableInterface;
    std::string fTableName;
    Bool_t fUseOverlayCreationDate;
    FairDbValRecord* fValidRec;
    FairDbLogEntry fLogEntry;
    FairDb::Version fVersion;
    std::string fLogTitle;


    ClassDefT(FairDbWriter<T>,0)          // Generic Writer to  database payload table.

};
ClassDefT2(FairDbWriter,T)

#endif  // FAIRDBWRITER_H
