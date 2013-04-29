
#include "FairDb.h"
#include "FairDbConfigSet.h"
#include "FairDbOutRowStream.h"
#include "FairDbResult.h"

//#include "FairDbResPtr.h"
//#include "FairDbWriter.h"

#include <iostream>

ClassImp(FairDbConfigSet)



#include "FairDbResPtr.tpl"
template class  FairDbResultPtr<FairDbConfigSet>;

#include "FairDbWriter.tpl"
template class  FairDbWriter<FairDbConfigSet>;


FairDbConfigSet::~FairDbConfigSet()
{

  for ( vector<Param*>::iterator itr = fParams.begin();
        itr != fParams.end();
        ++itr ) { delete (*itr); }

}


ostream& operator<<(ostream& s, const FairDbConfigSet& cfSet)
{

  s << "FairDbConfigSet: Number of parameters: "
    << cfSet.GetNumParams() << endl;

  for ( UInt_t iParam = 0; iParam < cfSet.GetNumParams(); ++iParam) {
    s << "   "  << cfSet.GetParamName(iParam) << ":  "
      << cfSet.GetParamValue(iParam) << " ("
      << cfSet.GetParamType(iParam).AsString() << ")" << endl;
  }

  return s;

}




void FairDbConfigSet::Fill(FairDbResultSet& rs,
                           const FairDbValidityRec* vrec)
{

// Don't count leading SeqNo, its already been skipped.
  UInt_t numParams = rs.NumCols()-1;
// Skip the ROW_COUNTER if present
  if (  rs.HasRowCounter() ) { --numParams; }

  for (UInt_t iParam = 0; iParam < numParams; ++iParam ) {
    Param* par = new Param;
    par->Name  = rs.CurColName();
    par->Value = rs.CurColValue();
    par->Type  = rs.CurColFieldType();

    fParams.push_back(par);
    rs.IncrementCurCol();
  }

  fAggregateNo =  vrec->GetAggregateNo ();

}

string FairDbConfigSet::GetParamName(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Name : "";

}

FairDbFieldType FairDbConfigSet::GetParamType(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Type : FairDbFieldType(FairDb::kUnknown);

}

string FairDbConfigSet::GetParamValue(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Value : "";

}


void FairDbConfigSet::PushBack(const string& name,
                               const string& value,
                               const FairDbFieldType& type)
{

  fParams.push_back(new Param(name,value,type));
}


void FairDbConfigSet::Store(FairDbOutRowStream& ors,
                            const FairDbValidityRec* /* vrec */) const
{

  for ( vector<Param*>::const_iterator itr = fParams.begin();
        itr != fParams.end();
        ++itr ) { ors.Store((*itr)->Value.c_str()); }

}

