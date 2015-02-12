/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** 
 *  FairDbTutPar2.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 

#ifndef FAIRDBTUTPAR2_H
#define FAIRDBTUTPAR2_H

#include "FairDbParSet.h"          // for FairParGenericSet
#include "DataType.h"                    // for EDataType::kData
#include "ValCondition.h"                 // for ValCondition
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for FairDbDetector, etc

#include "Rtypes.h"                     // for Double_t, Int_t, UInt_t, etc

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <string>                       // for string

#include "FairDbWriter.h"
#include "FairDbReader.h"


using namespace std;

class FairDbOutTableBuffer;
class FairDbResultPool;
class FairDbObjTableMap;
class FairDbValRecord;
class FairParamList;


class FairDbTutPar2 : public FairDbParSet
{
  public :
    FairDbTutPar2 (const char* name="FairDbTutPar2",
                  const char* title="Tutorial  parameter",
                  const char* context="TestDefaultContext",
                  Bool_t own=kTRUE);
    virtual ~FairDbTutPar2(void);
    void clear(void);
    void   putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    void Print();
    /** Accessor functions **/
    Double_t GetTopPitch()        const {return fTopPitch;}
    Double_t GetTopAnchor()       const {return fTopAnchor;}
    Int_t    GetNrTopFE()         const {return fTopNrFE;}
    std::string   GetFeType()           const {return fFeType;}

    void SetTopPitch(Double_t x)  {fTopPitch = x;}
    void SetTopAnchor(Double_t x) {fTopAnchor = x;}
    void SetNrTopFE(Int_t x)      {fTopNrFE = x;}
    void SetFeType(std::string x)     {fFeType = x;}


    // Add-ons: SQL descriptors for the parameter class
    virtual std::string GetTableDefinition(const char* Name = 0);

    
    virtual FairDbObjTableMap* CreateObjTableMap() const {
       FairDbTutPar2* p = new FairDbTutPar2();
      return dynamic_cast<FairDbObjTableMap*> (p);
    }
    
    // Atomic IO (intrinsic)
    virtual void Fill(FairDbResultPool& res_in,
                      const FairDbValRecord* valrec);
    virtual void Store(FairDbOutTableBuffer& res_out,
                       const FairDbValRecord* valrec) const;
    // Global IO using run_id
    virtual void fill(UInt_t rid);
    virtual void store(UInt_t rid);

    // Validity frame definition
    virtual ValCondition GetContext(UInt_t rid) {
      return ValCondition(FairDbDetector::kGfi,
                          DataType::kData,
                          ValTimeStamp(rid));
    }

    
    // SQL-IO Meta-Class Getters
    FairDbReader<FairDbTutPar2>* GetParamReader();
    FairDbWriter<FairDbTutPar2>* GetParamWriter();

  private:
    // Strip Data Parameters
    Double_t fTopPitch;         // Strip pitch on top wafer side
    Double_t fTopAnchor;        // Anchor point of top strip#0
    Int_t    fTopNrFE;          // Number of FE attached to top wafer side
    std::string    fFeType;     // Frontend type name


    // Database Pool Index
    Int_t fDbEntry; //!
    // Parameter Container SQL Writer Meta-Class
    FairDbWriter<FairDbTutPar2>* fParam_Writer; //!
    // Parameter Container SQL Writer Meta-Class
    FairDbReader<FairDbTutPar2>* fParam_Reader; //!
    // Connection Pool
    FairDbConnectionPool* fMultConn;  //!

    ClassDef(FairDbTutPar2,1); // Tutorial5 FairDbTutPar2 Parameter Container example
};

#endif /* !FAIRDBTUTPAR_H*/

inline  FairDbReader<FairDbTutPar2>* FairDbTutPar2::GetParamReader()
{
  if (fParam_Reader) { return fParam_Reader; }
  else {
    fParam_Reader = new  FairDbReader<FairDbTutPar2>();
    return fParam_Reader;
  }
}

inline FairDbWriter<FairDbTutPar2>* FairDbTutPar2::GetParamWriter()
{
  if (fParam_Writer) { return fParam_Writer; }
  else {
    fParam_Writer = new  FairDbWriter<FairDbTutPar2>();
    return fParam_Writer;
  }
}
