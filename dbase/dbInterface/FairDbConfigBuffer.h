/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCONFIGBUFFER_H
#define FAIRDBCONFIGBUFFER_H

#include "FairDb.h"                     // for Version
#include "FairDbConfigData.h"            // for FairDbConfigData
#include "FairDbReader.h"               // for FairDbReader
#include "FairDbValRecord.h"          // for FairDbValRecord
#include "ValCondition.h"                 // for ValCondition

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Bool_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairRegistry;

class FairDbConfigBuffer
{


  public:

    static      ValCondition fgDefaultContext;

    FairDbConfigBuffer();
    FairDbConfigBuffer(const std::string& SoftwName,
                       const std::string& ConfigName="default",
                       ValCondition vc = FairDbConfigBuffer::fgDefaultContext,
                       FairDb::Version task=0,
                       const std::string& tableName="SOFTWARE_CONF");
    virtual ~FairDbConfigBuffer();

    const FairDbConfigBuffer& operator>>(FairRegistry* reg);
    const FairDbConfigData* GetConfigData() const { return fCFSet; }


    FairDbConfigBuffer& operator<<(const FairRegistry* reg);
    Bool_t IsEmpty() { return fCFSet == 0; }
    FairDbValRecord& GetValidityRec() { return fVRec; }
    Bool_t Write(UInt_t dbNo = 0,
                 const std::string& logComment = "",
                 Bool_t localTest = false);

  private:

    FairDbConfigBuffer(const FairDbConfigBuffer&);
    FairDbConfigBuffer operator=(const FairDbConfigBuffer&);


    const FairDbConfigData* fCFSet;
    FairDbReader<FairDbConfigData> fCFSetTable;
    FairDbConfigData fCFSetModified;
    FairDbValRecord fVRec;
    std::string    fConfigName;
    std::string    fSoftwName;

    ClassDef(FairDbConfigBuffer,0)

};

ostream& operator<<(ostream& s, const FairDbConfigBuffer& cfStream);

#endif  // FAIRDBCONFIGBUFFER_H
