/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConfigData.h"

#include "FairDb.h"                     // for DataTypes::kUnknown
#include "FairDbOutTableBuffer.h"         // for FairDbOutTableBuffer
#include "FairDbReader.h"               // for FairDbReader
#include "FairDbResult.h"               // for FairDbResultPool
#include "FairDbValRecord.h"          // for FairDbValRecord
#include "FairDbWriter.h"               // for FairDbWriter

#include <map>                          // for map
#include <iostream>                     // for operator<<, basic_ostream, etc

using std::vector;
using std::map;

ClassImp(FairDbConfigData)



#include "FairDbReader.tpl"            // IWYU pragma: keep
template class  FairDbReader<FairDbConfigData>;

#include "FairDbWriter.tpl"           // IWYU pragma: keep
template class  FairDbWriter<FairDbConfigData>;


FairDbConfigData::~FairDbConfigData()
{

  for ( vector<Param*>::iterator itr = fParams.begin();
        itr != fParams.end();
        ++itr ) { delete (*itr); }

}


ostream& operator<<(ostream& s, const FairDbConfigData& cfSet)
{

  s << "FairDbConfigData: Number of parameters: "
    << cfSet.GetNumParams() << endl;

  for ( UInt_t iParam = 0; iParam < cfSet.GetNumParams(); ++iParam) {
    s << "   "  << cfSet.GetParamName(iParam) << ":  "
      << cfSet.GetParamValue(iParam) << " ("
      << cfSet.GetParamType(iParam).AsString() << ")" << endl;
  }

  return s;

}




void FairDbConfigData::Fill(FairDbResultPool& rs,
                            const FairDbValRecord* vrec)
{
  // Skip First slot SeqNo in column.
  UInt_t numParams = rs.NumCols()-1;
  // Skip  also ROW_ID if existing
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

string FairDbConfigData::GetParamName(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Name : "";

}

FairDbFieldType FairDbConfigData::GetParamType(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Type : FairDbFieldType(FairDb::kUnknown);

}

string FairDbConfigData::GetParamValue(UInt_t parNo) const
{

  return ( parNo <= GetNumParams() ) ?
         fParams[parNo]->Value : "";

}


void FairDbConfigData::PushBack(const string& name,
                                const string& value,
                                const FairDbFieldType& type)
{

  fParams.push_back(new Param(name,value,type));
}


void FairDbConfigData::Store(FairDbOutTableBuffer& ors,
                             const FairDbValRecord* /* vrec */) const
{

  for ( vector<Param*>::const_iterator itr = fParams.begin();
        itr != fParams.end();
        ++itr ) { ors.Store((*itr)->Value.c_str()); }

}

