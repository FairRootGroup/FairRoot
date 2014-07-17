/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTABLEBUFFER_H
#define FAIRDBTABLEBUFFER_H

#include "Rtypes.h"                     // for UInt_t, Bool_t, etc

#include <string>                       // for string

class FairDbFieldType;
class FairDbTableMetaData;

class FairDbTableBuffer
{
  public:

    FairDbTableBuffer(const FairDbTableMetaData* metaData);
    virtual ~FairDbTableBuffer();

    virtual const FairDbFieldType& ColFieldType(UInt_t col) const;
    virtual const FairDbFieldType& GetColumnFieldType(UInt_t col) const {return ColFieldType(col);}
    virtual       std::string ColName(UInt_t col) const;
    virtual       std::string GetColumnName(UInt_t col) const {return ColName(col);}
    virtual const FairDbFieldType& CurColFieldType() const;
    virtual const FairDbFieldType& GetCurrrentColumnFieldType() const {return CurColFieldType();}
    virtual       std::string CurColName() const;
    virtual       std::string GetCurrentColumnName() const {return CurColName();}
    virtual       UInt_t CurColNum() const {return fCurCol;}
    virtual       UInt_t GetCurrentColumnNo() const {return fCurCol;}
    Bool_t HasRowCounter() const { return fHasRowCounter; }
    Bool_t HasRowId() const { return fHasRowCounter; }
    virtual       UInt_t NumCols() const;
    virtual       UInt_t GetNumOfColumns() const {return NumCols();}
    virtual       std::string TableName() const;
    virtual       std::string GetTableName() const {return TableName();}
    virtual       std::string TableNameTc() const;
    virtual       std::string GetTableNameTc() const {return TableNameTc();}

    virtual const FairDbTableMetaData*
    MetaData() const { return fMetaData; }


    virtual    void DecrementCurCol() {
      fCurCol = (fCurCol <= 1) ? 1 : fCurCol -1;
    }
    virtual    void GetPreviousCurrentColumn() {return DecrementCurCol();}

    virtual    void IncrementCurCol() { ++fCurCol; }
    virtual    void GetNextCurrentColumn() {return IncrementCurCol();}

    protected:

    virtual    void ClearCurCol() { fCurCol = 1; }
    virtual    void ResetCurrentColumn() { fCurCol = 1; }

  private:

    UShort_t fCurCol;
    Bool_t fHasRowCounter;
    const FairDbTableMetaData* fMetaData;

    FairDbTableBuffer(const FairDbTableBuffer&);
    FairDbTableBuffer operator=(const FairDbTableBuffer&);

    ClassDef(FairDbTableBuffer,0)     // Table Row Buffer
};

#endif  // FAIRDBTABLEBUFFER_H
