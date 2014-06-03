/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBVALRECORDMAP
#define FAIRDBVALRECORDMAP

#include "Rtypes.h"                     // for UInt_t, etc

#include <map>                          // for map
#include <string>                       // for string

class FairDbResult;
class FairDbValRecord;

class FairDbValRecordMap
{

  public:
    FairDbValRecordMap(const std::string& tableName,UInt_t dbNo,UInt_t seqNo=0);
    virtual ~FairDbValRecordMap();

    UInt_t GetDbNo() const { return fDbNo; }
    UInt_t GetNumRows() const;
    const std::string GetTableName() const;
    const FairDbValRecord* GetObjTableMap(UInt_t rowNum) const;
    const FairDbValRecord* GetObjTableMapBySeqNo(UInt_t seqNo) const;


  private:

    UInt_t fDbNo;
    FairDbResult* fResult;
    mutable std::map<UInt_t,const FairDbValRecord*>fSeqNoToRec;

    FairDbValRecordMap(const FairDbValRecordMap&);
    FairDbValRecordMap operator=(const FairDbValRecordMap&);

    ClassDef(FairDbValRecordMap,0)     //  A map list of FairDbValRecords

};


#endif  // FAIRDBVALRECORDMAP
