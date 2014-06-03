/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbValRecordMap.h"

#include "FairDbProxy.h"                // for FairDbProxy
#include "FairDbResult.h"               // for FairDbResult, etc
#include "FairDbTableInterface.h"           // for FairDbTableInterface
#include "FairDbTableInterfaceStore.h"   // for FairDbTableInterfaceStore
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "FairDbValRecord.h"          // for FairDbValRecord

#include <stddef.h>                     // for NULL
#include <utility>                      // for pair

using std::string;
using std::map;

ClassImp(FairDbValRecordMap)



FairDbValRecordMap::FairDbValRecordMap(const string& tableName,UInt_t dbNo,UInt_t seqNo) :
  fDbNo(dbNo),
  fResult(NULL),
  fSeqNoToRec()
{

  FairDbValRecord pet;
  const FairDbProxy& proxy = FairDbTableInterfaceStore::Instance()
                             .GetTableInterface(tableName,&pet)
                             .GetDBProxy();


  FairDbResultPool* rset = proxy.QueryAllValidities(dbNo,seqNo);
  fResult = new FairDbResultNonCombo(rset,&pet,0,kFALSE);
  delete rset;


}



FairDbValRecordMap::~FairDbValRecordMap()
{

  delete fResult;

}


UInt_t FairDbValRecordMap::GetNumRows() const
{

  return fResult ? fResult->GetNumRows() : 0;
}


const string FairDbValRecordMap::GetTableName() const
{

  return fResult ? fResult->TableName() : "Unknown";
}


const FairDbValRecord* FairDbValRecordMap::GetObjTableMap(UInt_t rowNum) const
{

  return fResult ?
         dynamic_cast<const FairDbValRecord*>(fResult->GetObjTableMap(rowNum))
         : 0;
}


const FairDbValRecord* FairDbValRecordMap::GetObjTableMapBySeqNo(UInt_t seqNo
                                                                ) const
{

  UInt_t numRows = GetNumRows();
  if ( numRows == 0 ) { return 0; }

// Create look-up table if not already done
  if ( fSeqNoToRec.size() == 0 ) {
    for ( UInt_t irow = 0; irow < numRows; ++irow) {
      const FairDbValRecord* vrec = GetObjTableMap(irow);
      fSeqNoToRec[vrec->GetSeqNo()] = vrec;
    }
  }

  map<UInt_t,const FairDbValRecord*>::const_iterator itr = fSeqNoToRec.find(seqNo);
  return ( itr == fSeqNoToRec.end() ) ? 0 : itr->second;

}

