//
// C++ Interface: FairDbTutParBin
//
#ifndef FAIRDBTUTPARBIN_H
#define FAIRDBTUTPARBIN_H


#include "TObject.h"
#include "Rtypes.h"
#include <TVector3.h>
#include <TObjString.h>
#include <TH1F.h>
#include "TBufferFile.h"


#include "Detector.h"
#include "DataType.h"
#include "FairDbObjTableMap.h"
#include "ValCondition.h"
#include "ValInterval.h"
#include "ValTimeStamp.h"

#include "FairParGenericSet.h"
#include "FairParamList.h"
#include <string>
#include <memory>

using std::string;
using std::auto_ptr;

class FairDbValRecord;

class FairDbTutParBin : public FairParGenericSet
{
  public :
    FairDbTutParBin (const char* name="FairDbTutParBin",
                     const char* title="Tutorial  parameter",
                     const char* context="TestDefaultContext");
    virtual ~FairDbTutParBin(void);
    void clear(void);
    void   putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    void Print();
    /** Accessor functions **/
    Double_t GetTopPitch()        const {return fTopPitch;}
    Double_t GetTopAnchor()       const {return fTopAnchor;}
    Int_t    GetNrTopFE()         const {return fTopNrFE;}
    string   GetFeType()          const {return fFeType;}
    Int_t*   GetMyIArray()         {return fMyIArray;}
    Double_t*   GetMyDArray()         {return fMyDArray;}
    TH1F*    GetMyHisto()         {return fMyHisto;}


    void SetTopPitch(Double_t x)  {fTopPitch = x;}
    void SetTopAnchor(Double_t x) {fTopAnchor = x;}
    void SetNrTopFE(Int_t x)      {fTopNrFE = x;}
    void SetFeType(string x)     {fFeType = x;}
    void SetMyIArray(Int_t val, Int_t i) {fMyIArray[i]= val;}
    void SetMyDArray(Double_t val, Int_t i) {fMyDArray[i]= val;}


    // SQL descriptors
    virtual string GetTableDescr(const char* alternateName = 0);
    virtual FairDbObjTableMap* CreateObjTableMap() const {
      return new FairDbTutParBin();
    }

    // I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec);
    virtual void Store(FairDbOutTableBuffer& ors,
                       const FairDbValRecord* vrec) const;

    virtual void fill(UInt_t rid);
    virtual void store(UInt_t rid);

    // Validity frame definition
    virtual ValCondition GetContextDTF(UInt_t rid) {
      return ValCondition(Detector::kGfi,
                          DataType::kData,
                          ValTimeStamp(rid));
    }

    virtual void print() {Print();}

    void FillDummy();

  private:
    // Example Strip Parameters
    Double_t fTopPitch;     // Strip pitch on top wafer side
    Double_t fTopAnchor;    // Anchor point of top strip#0
    Int_t    fTopNrFE;      // Number of FE attached to top wafer side
    string   fFeType;       // Frontend type name
    Int_t    fMyIArray[3];   // Array of Int_t fixed values
    Double_t fMyDArray[10];  // Array of Double_t fixed values
    TH1F*   fMyHisto;      // An Histogram

    ClassDef(FairDbTutParBin,1); //
};

#endif /* !FAIRDBTUTPARBIN_H*/

