/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBVALRECORD_H
#define FAIRDBVALRECORD_H

#include "FairDbObjTableMap.h"

#include "FairDb.h"                      // for Version
#include "ValInterval.h"                    // for ValInterval
#include "ValTimeStamp.h"                // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, UInt_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairDbBufferFile;
class FairDbTableInterface;
class FairDbOutTableBuffer;
class FairDbResultPool;
class ValCondition;

class FairDbValRecord : public FairDbObjTableMap
{

  public:

    FairDbValRecord(Int_t dbNo = -1, Bool_t isGap = kTRUE);
    FairDbValRecord(const FairDbValRecord& from);
    FairDbValRecord(const ValInterval& range,
                    FairDb::Version task,
                    Int_t aggNo,
                    UInt_t seqNo,
                    Int_t dbNo = -1,
                    Bool_t isGap = kFALSE,
                    ValTimeStamp time = ValTimeStamp());

    FairDbValRecord& operator=(const FairDbValRecord& from);

    virtual ~FairDbValRecord();

    virtual FairDbObjTableMap* CreateObjTableMap() const {
      return new FairDbValRecord;
    }
    Int_t GetAggregateNo() const { return fAggregateNo; }
    ValTimeStamp GetCreationDate() const { return fCreationDate; }
    UInt_t GetDbNo() const { return fDbNo; }
    ValTimeStamp GetInsertDate() const { return fInsertDate; }
    FairDb::Version GetVersion() const { return fVersion; }
    std::string GetCacheName() const;
    UInt_t GetSeqNo() const { return fSeqNo; }
    const FairDbTableInterface* GetTableInterface() const { return fTableInterface; }
    const ValInterval& GetValInterval() const { return fValInterval;}
    Bool_t HasExpired(const FairDbValRecord& other) const;
    Bool_t HasExpired(const ValCondition& vc,
                      const FairDb::Version& task) const;
    Bool_t IsCompatible(const ValCondition& vc,
                        const FairDb::Version& task) const;
    Bool_t IsGap() const { return fIsGap; }

    static     std::string GetCacheName(UInt_t seqLo, UInt_t seqHi, ValTimeStamp ts);


    void AndTimeWindow(const ValTimeStamp& start,
                       const ValTimeStamp& end);
    void SetAggregateNo(Int_t aggNo) { fAggregateNo = aggNo; }
    void SetDbNo(Int_t dbNo) { fDbNo = dbNo; }
    void SetTableInterface(const FairDbTableInterface* tp) { fTableInterface = tp; }
    void SetTimeWindow(const ValTimeStamp& start,
                       const ValTimeStamp& end);
    void SetValInterval(const ValInterval& range) { fValInterval=range;}
    void Trim(const ValTimeStamp& queryTime,
              const FairDbValRecord& other);

// I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec);
    virtual void Store(FairDbOutTableBuffer& ors,
                       const FairDbValRecord* vrec) const;
    void Streamer(FairDbBufferFile& file);

  private:
    Int_t fAggregateNo;
    ValTimeStamp fCreationDate;
    Int_t fDbNo;
    ValTimeStamp fInsertDate;
    Bool_t fIsGap;
    FairDb::Version fVersion;
    Int_t fSeqNo;
    const FairDbTableInterface* fTableInterface;
    ValInterval fValInterval;



    ClassDef(FairDbValRecord,0)  // Validity interval table row.

};

ostream& operator<<(ostream& s, const FairDbValRecord& vRec);


#endif  // FAIRDBVALRECORD_H
