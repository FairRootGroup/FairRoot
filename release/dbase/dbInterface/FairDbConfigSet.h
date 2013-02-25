#ifndef FAIRDBCONFIGSET_H
#define FAIRDBCONFIGSET_H


#include <string>
using std::string;

#include <vector>
using std::vector;

#include "FairDbTableRow.h"
#include "FairDbFieldType.h"
#include <iosfwd>

class FairDbConfigSet;
class FairDbValidityRec;

std::ostream& operator<<(std::ostream& s, const FairDbConfigSet& cfSet);

class FairDbConfigSet : public FairDbTableRow
{

  public:

// Constructors and destructors.
    FairDbConfigSet() : fParams(), fAggregateNo(-2) { ; }
    virtual ~FairDbConfigSet();

// State testing member functions

    virtual FairDbTableRow* CreateTableRow() const {
      return new FairDbConfigSet;
    }
    Int_t GetAggregateNo() const { return fAggregateNo; }
    UInt_t GetNumParams() const { return fParams.size(); }
    string GetParamName(UInt_t parNo) const;
    FairDbFieldType GetParamType(UInt_t parNo) const;
    string GetParamValue(UInt_t parNo) const;

// State changing member functions
    void Clear(const Option_t* = "") { fParams.clear(); }
    void PushBack(const string& name,
                  const string& value,
                  const FairDbFieldType& type);
    void SetAggregateNo(Int_t aggNo) { fAggregateNo = aggNo; }

// I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec);
    virtual void Store(FairDbOutRowStream& ors,
                       const FairDbValidityRec* vrec) const;

  private:
// Constructors and destructors.
    FairDbConfigSet(const FairDbConfigSet& from); // No! { LEA_CTOR; *this = from; }


// Internal structures.

    struct Param {
      Param() : Name(), Value(), Type() {}
      Param(const Param& that) : Name(that.Name), Value(that.Value), Type(that.Type) {
        *this = that;
      }
      Param(const string& name,
            const string& value,
            const FairDbFieldType& type) : Name(name), Value(value), Type(type) {
      }
      ~Param() { }

      string Name;
      string Value;
      FairDbFieldType Type;
    };

    vector<Param*> fParams;

    Int_t fAggregateNo;

    ClassDef(FairDbConfigSet,0)    // Configuration data.

};


#endif  // FAIRDBCONFIGSET_H
