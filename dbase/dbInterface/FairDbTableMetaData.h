#ifndef FAIRDBTABLEMETADATA_H
#define FAIRDBTABLEMETADATA_H


#include <string>
using std::string;
#include <vector>

#include "FairDbFieldType.h"

class FairDbTableMetaData
{

    friend class FairDbProxy;  //

  public:

    FairDbTableMetaData(const string& tableName = "Unknown");
    virtual ~FairDbTableMetaData();

    // Return SQL string to create table.
    string Sql(FairDb::DbTypes dbType = FairDb::kMySQL) const;

    string TableName() const { return fTableName; }
    Bool_t HasRowCounter() const {return  this->NumCols() >=2 && this->ColName(2) == "ROW_COUNTER"; }
    UInt_t NumCols() const { return fNumCols;}

    // Column attribute getters (columns number starts from 1 NOT zero)

    const FairDbFieldType& ColFieldType(Int_t colNum) const    { return GetAttributes(colNum).Type;}
    UInt_t ColFieldConcept(Int_t colNum) const { return GetAttributes(colNum).Concept;}
    Bool_t ColIsNullable(Int_t colNum) const   { return GetAttributes(colNum).IsNullable;}
    Bool_t ColMustDelimit(Int_t colNum) const  { return GetAttributes(colNum).MustDelimit;}
    string ColName(Int_t colNum) const         { return GetAttributes(colNum).Name;}

    // Recreate from SQL used to create table.
    void SetFromSql(const string& sql);

  protected:

    void Clear();
    void SetColIsNullable(Int_t colNum, Bool_t isNullable = true) { SetAttributes(colNum).IsNullable = isNullable;}
    void SetColName(const string& name, Int_t colNum)             { SetAttributes(colNum).Name = name;}
    void SetColFieldType(const FairDbFieldType& type, Int_t colNum);

  private:

    static string GetToken(const char*& strPtr);

    //Sanity check: limit number of columns.
    enum { MAXCOL = 1000};

    void ExpandTo(UInt_t colNum);

/// Column attributes
    struct ColumnAttributes {
      ColumnAttributes() : Name("Unknown"), Concept(FairDb::kUnknown),
        MustDelimit(false), IsNullable(false), Type(FairDb::kUnknown) { };
      void SetDefault() {
        Name        = "Unknown";
        Concept     = FairDb::kUnknown;
        MustDelimit = false;
        IsNullable  = false;
        Type        = FairDb::kUnknown;
      }
      string Name;
      Int_t Concept;
      Bool_t MustDelimit;
      Bool_t IsNullable;
      FairDbFieldType Type;
    };

    static ColumnAttributes fgDummy;
    const ColumnAttributes& GetAttributes(Int_t colNum) const;
    ColumnAttributes& SetAttributes(Int_t colNum);

    std::vector<ColumnAttributes> fColAttr;
    UInt_t fNumCols;
    string fTableName;

    ClassDef(FairDbTableMetaData,0)     //TableMetaData for database table

};


#endif  // FAIRDBTABLEMETADATA_H
