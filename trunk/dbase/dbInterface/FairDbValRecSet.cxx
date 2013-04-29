
#include "FairDbProxy.h"
#include "FairDbResult.h"
#include "FairDbTableProxy.h"
#include "FairDbTableProxyRegistry.h"
#include "FairDbValidityRec.h"
#include "FairDbValRecSet.h"

ClassImp(FairDbValRecSet)



FairDbValRecSet::FairDbValRecSet(const string& tableName,UInt_t dbNo,UInt_t seqNo) :
  fDbNo(dbNo),
  fResult(NULL),
  fSeqNoToRec()
{
// Get Db proxy for the table.
  FairDbValidityRec pet;
  const FairDbProxy& proxy = FairDbTableProxyRegistry::Instance()
                             .GetTableProxy(tableName,&pet)
                             .GetDBProxy();

// Collect up all validity records.
  FairDbResultSet* rset = proxy.QueryAllValidities(dbNo,seqNo);
  fResult = new FairDbResultNonAgg(rset,&pet,0,kFALSE);
  delete rset;


}



FairDbValRecSet::~FairDbValRecSet()
{

  delete fResult;

}


UInt_t FairDbValRecSet::GetNumRows() const
{

  return fResult ? fResult->GetNumRows() : 0;
}


const string FairDbValRecSet::GetTableName() const
{

  return fResult ? fResult->TableName() : "Unknown";
}


const FairDbValidityRec* FairDbValRecSet::GetTableRow(UInt_t rowNum) const
{

  return fResult ?
         dynamic_cast<const FairDbValidityRec*>(fResult->GetTableRow(rowNum))
         : 0;
}


const FairDbValidityRec* FairDbValRecSet::GetTableRowBySeqNo(UInt_t seqNo
                                                            ) const
{

  UInt_t numRows = GetNumRows();
  if ( numRows == 0 ) { return 0; }

// Create look-up table if not yet built.

  if ( fSeqNoToRec.size() == 0 ) {
    for ( UInt_t irow = 0; irow < numRows; ++irow) {
      const FairDbValidityRec* vrec = GetTableRow(irow);
      fSeqNoToRec[vrec->GetSeqNo()] = vrec;
    }
  }

  map<UInt_t,const FairDbValidityRec*>::const_iterator itr = fSeqNoToRec.find(seqNo);
  return ( itr == fSeqNoToRec.end() ) ? 0 : itr->second;

}

