/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBOBJTABLEMAP_H
#define FAIRDBOBJTABLEMAP_H

#include "TObject.h"                    // for TObject
#include "FairDb.h"
#include "DataType.h"                    // for DataType_t
#include "ValCondition.h"                 // for ValCondition
#include "ValInterval.h"                   // for ValInterval
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector, etc

#include "Rtypes.h"                     // for UInt_t, Int_t, etc

#include <stddef.h>                     // for NULL
#include <cassert>                      // for assert
#include <string>                       // for string

class FairDbOutTableBuffer;
class FairDbResult;
class FairDbResultPool;
class FairDbValRecord;

class FairDbObjTableMap : public TObject
{
  public:

    FairDbObjTableMap();
    FairDbObjTableMap(const FairDbObjTableMap& from);
    FairDbObjTableMap& operator=(const FairDbObjTableMap&);
    virtual ~FairDbObjTableMap();

    virtual       Bool_t CanCache() const { return kFALSE; }

    void SetOwner(FairDbResult* owner) {fOwner = owner;}
    FairDbResult* GetOwner() const { return fOwner; }

    virtual FairDbObjTableMap* CreateObjTableMap() const {return NULL;};
    virtual       UInt_t GetIndex(UInt_t defIndex) const {return defIndex;}

    // I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec) {assert(0);};
    virtual void Store(FairDbOutTableBuffer& /* res_out */,
                       const FairDbValRecord* /* valrec */) const { assert(0); }

    // Validity frame functions
    virtual  Int_t GetAggregateNo() const { return GetComboNo(); }
    virtual  Int_t GetComboNo() const { return fCombo; }
    void    SetComboNo(Int_t combo) { fCombo=combo; }

    virtual  FairDb::Version GetVersion() const { return  fVersion; }
    void  SetVersion(FairDb::Version vers) { fVersion=vers; }

    virtual  FairDb::Version GetDbEntry() const { return  fDbEntry; }
    void  SetDbEntry(Int_t db) { fDbEntry=db; }

    virtual std::string GetLogTitle() const {return fLogTitle;}
    void SetLogTitle(std::string logTitle) {fLogTitle = logTitle;}


    // Condition definition
    virtual ValCondition GetContext(UInt_t rid) { return ValCondition();}
    virtual std::string GetTableDefinition(const char* alternateName = 0) {return NULL;}
    // <DB> add ons GlobalSeqNo
    virtual UInt_t GetSeqNo() { return 999999990; }

    virtual ValInterval GetValInterval(UInt_t rid) {
      ValCondition context = GetContext(rid);
      ValTimeStamp tsStart = context.GetTimeStamp();

      return ValInterval(context.GetDetector(),
                         context.GetDataType(),
                         tsStart,
                         ValTimeStamp::GetEOT(),
                         "Condition Meta Data");
    }

    //
    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    Detector::Detector_t     GetDetector()  const { return fDetType; }
    DataType::DataType_t     GetDataType()   const { return fSimType; }


  protected:
    //
    FairDb::Version fVersion;
    Int_t fDbEntry;
    std::string fLogTitle;
    Int_t fCombo;
    //
    ValTimeStamp               fTimeStart;
    ValTimeStamp               fTimeEnd;
    Detector::Detector_t       fDetType;
    DataType::DataType_t       fSimType;
    //

  private:
    FairDbResult* fOwner;

    ClassDef(FairDbObjTableMap,0)   // FairDbObjTableMap for a specific database table.

};


#endif  // FAIRDBOBJTABLEMAP_H
