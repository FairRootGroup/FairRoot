/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBVALRECORDFACTORY_H
#define FAIRDBVALRECORDFACTORY_H

#include "FairDb.h"                     // for Version
#include "FairDbValRecord.h"          // for FairDbValRecord

#include "Rtypes.h"                     // for Int_t, UInt_t, Bool_t, etc

#include <map>                          // for map
#include <string>                       // for string
#include <vector>                       // for vector

class FairDbProxy;
class ValCondition;


class FairDbValRecordFactory
{


  public:
    enum { kMAX_AGGREGATE_NO = 1000 };

    FairDbValRecordFactory(const FairDbProxy& proxy,
                           const ValCondition& vc,
                           const FairDb::Version& task,
                           Int_t selectDbNo = -1,
                           Bool_t findFullTimeWindow = true);
    FairDbValRecordFactory(const FairDbProxy& proxy,
                           const std::string& context,
                           const FairDb::Version& task);
    FairDbValRecordFactory(const FairDbValRecord& vr,
                           const std::string tableName);

    virtual ~FairDbValRecordFactory();

    std::string GetCacheName() const;
    FairDb::Version GetVersion() const { return fVersion; }
    UInt_t GetNumValidityRec() const {
      return fVRecs.size();
    }

    Int_t IndexOfAggno(Int_t aggNo) const;
    Bool_t IsExtendedContext() const {
      return fIsExtendedContext;
    }
    const FairDbValRecord& GetValidityRec(Int_t rowNo) const;
    const FairDbValRecord& GetValidityRecFromAggNo(Int_t aggNo) const {
      return this->GetValidityRec(this->IndexOfAggno(aggNo));
    }
    const FairDbValRecord& GetValidityRecFromSeqNo(UInt_t SeqNo) const;
    Bool_t NonAggregated() const {
      return  ! this->IsExtendedContext()
              && this->GetNumValidityRec() == 1;
    }


  private:

    UInt_t AddNewAgg(const FairDbValRecord& vrec,Int_t aggNo);
    UInt_t AddNewGap(Int_t aggNo);

    void MakeGapRec(const ValCondition& vc,
                    const std::string& tableName,
                    Bool_t findFullTimeWindow = true);


    FairDbValRecord fGap;
    Bool_t fIsExtendedContext;
    FairDb::Version fVersion;

    std::vector<FairDbValRecord> fVRecs;
    std::map<Int_t,UInt_t>  fAggNoToIndex;

    ClassDef(FairDbValRecordFactory,0) // Factory for  Validity Records

};

#endif  // FAIRDBVALRECORDFACTORY_H
