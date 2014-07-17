/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCONFIGDATA_H
#define FAIRDBCONFIGDATA_H

#include "FairDbObjTableMap.h"             // for FairDbObjTableMap

#include "FairDbFieldType.h"            // for FairDbFieldType

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for UInt_t, Int_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string, basic_string
#include <vector>                       // for vector

class FairDbOutTableBuffer;
class FairDbResultPool;
class FairDbValRecord;

class FairDbConfigData : public FairDbObjTableMap
{

  public:

    FairDbConfigData() : fParams(), fAggregateNo(-2) { ; }
    virtual ~FairDbConfigData();

    virtual FairDbObjTableMap* CreateObjTableMap() const {
      return new FairDbConfigData;
    }
    Int_t GetAggregateNo() const { return fAggregateNo; }
    UInt_t GetNumParams() const { return fParams.size(); }
    std::string GetParamName(UInt_t parNo) const;
    FairDbFieldType GetParamType(UInt_t parNo) const;
    std::string GetParamValue(UInt_t parNo) const;


    void Clear(const Option_t* = "") { fParams.clear(); }
    void PushBack(const std::string& name,
                  const std::string& value,
                  const FairDbFieldType& type);
    void SetAggregateNo(Int_t aggNo) { fAggregateNo = aggNo; }

// I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec);
    virtual void Store(FairDbOutTableBuffer& ors,
                       const FairDbValRecord* vrec) const;

  private:

    FairDbConfigData(const FairDbConfigData& from);

    struct Param {
      Param() : Name(), Value(), Type() {}
      Param(const Param& that) : Name(that.Name), Value(that.Value), Type(that.Type) {
        *this = that;
      }
      Param(const std::string& name,
            const std::string& value,
            const FairDbFieldType& type) : Name(name), Value(value), Type(type) {
      }
      ~Param() { }

      std::string Name;
      std::string Value;
      FairDbFieldType Type;
    };

    std::vector<Param*> fParams;
    Int_t fAggregateNo;

    ClassDef(FairDbConfigData,0)    // Configuration data.

};

std::ostream& operator<<(std::ostream& s, const FairDbConfigData& cfSet);

#endif  // FAIRDBCONFIGDATA_H
