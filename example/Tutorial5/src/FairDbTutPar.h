//
// C++ Interface: FairDbTutPar
//
#ifndef FAIRDBTUTPAR_H
#define FAIRDBTUTPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet
#include "SimFlag.h"                    // for ESimFlag::kData
#include "ValContext.h"                 // for ValContext
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector, etc

#include "Rtypes.h"                     // for Double_t, Int_t, UInt_t, etc

#include <string>                       // for string

class FairDbOutRowStream;
class FairDbResultSet;
class FairDbTableRow;
class FairDbValidityRec;
class FairParamList;

class FairDbTutPar : public FairParGenericSet
{
  public :
    FairDbTutPar (const char* name="FairDbTutPar",
                  const char* title="Tutorial  parameter",
                  const char* context="TestDefaultContext");
    virtual ~FairDbTutPar(void) {};
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


    // SQL descriptors
    virtual std::string GetTableDescr(const char* alternateName = 0);
    virtual FairDbTableRow* CreateTableRow() const {
      return new FairDbTutPar();
    }

    // I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec);
    virtual void Store(FairDbOutRowStream& ors,
                       const FairDbValidityRec* vrec) const;
    virtual void Fill(UInt_t rid);
    virtual void Store(UInt_t rid);

    // Validity frame definition
    virtual ValContext GetContextDTF(UInt_t rid) {
      return ValContext(Detector::kGfi,
                        SimFlag::kData,
                        ValTimeStamp(rid));
    }


  private:
    // Example Strip Parameters
    Double_t fTopPitch;     // Strip pitch on top wafer side
    Double_t fTopAnchor;    // Anchor point of top strip#0
    Int_t    fTopNrFE;      // Number of FE attached to top wafer side
    std::string    fFeType;       // Frontend type name

    ClassDef(FairDbTutPar,1); //
};

#endif /* !FAIRDBTUTPAR_H*/

