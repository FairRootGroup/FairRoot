#ifndef FAIRDBOBJTABLEMAP_H
#define FAIRDBOBJTABLEMAP_H

#include "TObject.h"                    // for TObject

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

    FairDbResult* GetOwner() const { return fOwner; }
    virtual FairDbObjTableMap* CreateObjTableMap() const {return NULL;};
    virtual       UInt_t GetIndex(UInt_t defIndex) const {return defIndex;}


    void SetOwner(FairDbResult* owner) {fOwner = owner;}

    // I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec) {assert(0);};
    virtual void Store(FairDbOutTableBuffer& /* ors */,
                       const FairDbValRecord* /* vrec */) const { assert(0); }

    // Validity frame functions
    virtual  Int_t GetAggregateNo() const { return -1; }
    virtual  Int_t GetVersion() const { return  fVersion; }
    void  SetVersion(Int_t vers) { fVersion=vers; }

    // Data Transmission Fidelity
    virtual ValCondition GetContextDTF(UInt_t rid) { return ValCondition();}
    virtual std::string GetTableDescr(const char* alternateName = 0) {return NULL;}
    // <DB> add ons GlobalSeqNo
    virtual UInt_t GetSeqNoDTF() { return 999999990; }

    virtual ValInterval GetRangeDTF(UInt_t rid) {
      ValCondition context = GetContextDTF(rid);
      ValTimeStamp tsStart = context.GetTimeStamp();

      return ValInterval(context.GetDetector(),
                         context.GetDataType(),
                         tsStart,
                         ValTimeStamp::GetEOT(),
                         "Data Transmission Fidelity.");
    }

    //
    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    Detector::Detector_t     GetDetector()  const { return fDetType; }
    DataType::DataType_t       GetDataType()   const { return fSimType; }


  protected:
    Int_t fVersion;
    //
    ValTimeStamp             fTimeStart;
    ValTimeStamp             fTimeEnd;
    Detector::Detector_t     fDetType;
    DataType::DataType_t       fSimType;


  private:
    FairDbResult* fOwner;

    ClassDef(FairDbObjTableMap,0)   // FairDbObjTableMap for a specific database table.

};


#endif  // FAIRDBOBJTABLEMAP_H
