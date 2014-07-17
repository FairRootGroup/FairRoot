/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTABLEMETADATA_H
#define FAIRDBTABLEMETADATA_H

#include "FairDb.h"                     // for DataTypes::kUnknown, etc
#include "FairDbFieldType.h"            // for FairDbFieldType

#include "Rtypes.h"                     // for Int_t, Bool_t, UInt_t, etc

#include <string>                       // for string, operator==, etc
#include <vector>                       // for vector

class FairDbTableMetaData
{

    friend class FairDbProxy;  //

  public:

    FairDbTableMetaData(const std::string& tableName = "Unknown");
    virtual ~FairDbTableMetaData();

    // Return SQL string to create table.
    std::string Sql(FairDb::DbTypes dbType = FairDb::kMySQL) const;

    std::string TableName() const { return fTableName; }
    Bool_t HasRowCounter() const {return  this->NumCols() >=2 && this->ColName(2) == "ROW_ID"; }
    UInt_t NumCols() const { return fNumCols;}


    const FairDbFieldType& ColFieldType(Int_t colNum) const    { return GetAttributes(colNum).Type;}
    UInt_t ColFieldConcept(Int_t colNum) const { return GetAttributes(colNum).Concept;}
    Bool_t ColIsNullable(Int_t colNum) const   { return GetAttributes(colNum).IsNullable;}
    Bool_t ColMustDelimit(Int_t colNum) const  { return GetAttributes(colNum).MustDelimit;}
    std::string ColName(Int_t colNum) const         { return GetAttributes(colNum).Name;}

    void SetFromSql(const std::string& sql, FairDb::DbTypes dbtype);

  protected:

    void Clear();
    void SetColIsNullable(Int_t colNum, Bool_t isNullable = true) { SetAttributes(colNum).IsNullable = isNullable;}
    void SetColName(const std::string& name, Int_t colNum)             { SetAttributes(colNum).Name = name;}
    void SetColFieldType(const FairDbFieldType& type, Int_t colNum);

  private:

    static std::string GetToken(const char*& strPtr);

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
      std::string Name;
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
    std::string fTableName;

    ClassDef(FairDbTableMetaData,0)     //TableMetaData for database table

};


#endif  // FAIRDBTABLEMETADATA_H
