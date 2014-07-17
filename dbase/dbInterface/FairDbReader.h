/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBREADER_H
#define FAIRDBREADER_H

#include <map>
#include <vector>
#include <string>

#include "FairDb.h"
#include "FairDbResult.h"
#include "FairDbValRecord.h"
#include "ValCondition.h"

class FairDbResult;
class FairDbResultKey;
class FairDbExtSqlContent;
class FairDbTableInterface;

using std::vector;


template <class T> class FairDbReader
{
  public:
    FairDbReader();
    FairDbReader(const FairDbReader& that);
    FairDbReader(const ValCondition& vc,
                 FairDb::Version task = FairDb::kDefaultVersion,
                 FairDb::AbortTest abortTest = FairDb::kTableMissing,
                 Bool_t findFullTimeWindow = true);
    FairDbReader(const std::string& tableName,
                 const ValCondition& vc,
                 FairDb::Version task = FairDb::kDefaultVersion,
                 FairDb::AbortTest abortTest = FairDb::kTableMissing,
                 Bool_t findFullTimeWindow = true);
    FairDbReader(const std::string& tableName,
                 const FairDbExtSqlContent& context,
                 const FairDb::Version& task = FairDb::kAnyVersion,
                 const std::string& data = "",
                 const std::string& fillOpts = "",
                 FairDb::AbortTest abortTest = FairDb::kTableMissing);
    FairDbReader(const std::string& tableName,
                 const FairDbValRecord& vrec,
                 FairDb::AbortTest abortTest = FairDb::kTableMissing);
    FairDbReader(const std::string& tableName,
                 UInt_t seqNo,
                 UInt_t dbNo,
                 FairDb::AbortTest abortTest = FairDb::kTableMissing);
    virtual ~FairDbReader();

    UInt_t Activate(const ValCondition& vc,
                    FairDb::Version task = FairDb::kDefaultVersion,
                    FairDb::AbortTest abortTest = FairDb::kTableMissing,
                    Bool_t findFullTimeWindow = true);


    const FairDbResultKey* GetKey() const;
    UInt_t GetNumRows() const;
    const FairDbResult* GetResult() const { return fResult; }
    Int_t GetResultID() const;
    const T* GetRow(UInt_t rowNum) const;
    const T* GetRowByIndex(UInt_t index) const;
    const FairDbValRecord* GetValidityRec(const FairDbObjTableMap* row=0) const;
    FairDbTableInterface& TableInterface() const;
    Bool_t ResultsFromDb() const;

    static FairDbTableInterface& GetTableInterface();
    static FairDbTableInterface& GetTableInterface(const std::string& tableName);


    UInt_t NextQuery(Bool_t forwards = kTRUE);
    UInt_t NewQuery(ValCondition vc,
                    FairDb::Version task=0,
                    Bool_t findFullTimeWindow = true);
    UInt_t NewQuery(const FairDbExtSqlContent& context,
                    const FairDb::Version& task = 0,
                    const std::string& data = "",
                    const std::string& fillOpts = "");
    UInt_t NewQuery(const FairDbValRecord& vrec);
    UInt_t NewQuery(UInt_t seqNo,UInt_t dbNo);
    void   Reset() {;}

  private:
    void Disconnect();
    void SetContext(const FairDbValRecord& vrec);
    Bool_t ApplyAbortTest();

    FairDbReader& operator=(const FairDbReader&);

    FairDb::AbortTest fAbortTest;
    FairDbTableInterface& fTableInterface;
    const FairDbResult* fResult;
    Detector::Detector_t fDetType;
    DataType::DataType_t fSimType;

#ifndef __CINT__
    static std::map<std::string,FairDbTableInterface*> fgNameToProxy;
#endif  // __CINT__      
    static             FairDbTableInterface* fgTableInterface;

    // First add-on for memory management
    //static std::vector<T*>   fListOfT;

    ClassDefT(FairDbReader<T>,0)  // Reader pointer to specific database table.


};
ClassDefT2(FairDbReader,T)

#endif  // FAIRDBREADER_H
