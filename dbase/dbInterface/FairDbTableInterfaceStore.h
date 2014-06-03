/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBTABLEINTERFACESTORE_H
#define FAIRDBTABLEINTERFACESTORE_H

#include "FairDbConfigurable.h"         // for FairDbConfigurable

#include "FairDbRollbackTimes.h"        // for FairDbRollbackTimes
#include "FairDbDataTypeUnion.h"   // for FairDbDataTypeUnion

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Bool_t, etc
#endif

#include <map>                          // for map
#include <string>                       // for string

class FairDbConnectionPool;
class FairDbTableInterface;
class FairDbObjTableMap;

class FairDbTableInterfaceStore : public FairDbConfigurable
{

  public:

    void ShowStatistics() const;

    static FairDbTableInterfaceStore& Instance();
    static       Bool_t IsActive() { return fgInstance ? kTRUE: kFALSE; }

    void Config();
    void ClearRollbackTimes();
    void ClearDataTypeUnion();
    FairDbConnectionPool& GetConnectionPool() { return *fConnectionPool; }
    FairDbTableInterface& GetTableInterface(const std::string& tableName,
                                            const FairDbObjTableMap* tableRow) ;
    Bool_t HasRowCounter(const std::string& tableName);
    void PurgeCaches();
    void RefreshMetaData(const std::string& tableName);
    void SetSqlCondition(const std::string& sql="");

    void SetVerbosity(Int_t level ) {fVerbosity = level; SetLoggingStreams();}
  protected:

    FairDbTableInterfaceStore();
    virtual ~FairDbTableInterfaceStore();

  private:
    void SetLoggingStreams();
    void SetConfigFromEnvironment();

  public:

    struct Cleaner {
      static int fgCount; // counts #includes
      Cleaner() { this->Increment(); }
      ~Cleaner() {
        if (--fgCount==0 && FairDbTableInterfaceStore::fgInstance!=0) {
          delete FairDbTableInterfaceStore::fgInstance;
          FairDbTableInterfaceStore::fgInstance = 0;
        }
      }
      void Increment() { ++fgCount; };
    };
    friend struct Cleaner;

    FairDbConnectionPool* fConnectionPool;


  private:


    FairDbTableInterfaceStore(const FairDbTableInterfaceStore&);
    FairDbTableInterfaceStore& operator=(const FairDbTableInterfaceStore&);


    void ApplySqlCondition() const;
    void ApplySqlCondition(FairDbTableInterface* proxy) const;

// Data members

    std::string fSqlCondition;

#ifndef __CINT__
    std::map<std::string,FairDbTableInterface*> fTPmap;
#endif  // __CINT__   

    FairDbRollbackTimes fRollbackTimes;
    FairDbDataTypeUnion fDataTypeAss;
    TString fLogName;
    Int_t   fVerbosity;
    static FairDbTableInterfaceStore* fgInstance;

    ClassDef(FairDbTableInterfaceStore,0)   // Singleton storing FairDbTableInterface.

};

#ifndef __CINT__
static struct FairDbTableInterfaceStore::Cleaner __fairdb_cleaner;
#endif

#endif  // FAIRDBTABLEINTERFACESTORE_H
