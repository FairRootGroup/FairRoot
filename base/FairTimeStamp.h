#ifndef FAIRTIMESTAMP_H
#define FAIRTIMESTAMP_H
#include "FairMultiLinkedData.h"
/**
 * Base class for Time stamp information
 ** Aug. 2010
 **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairTimeStamp : public FairMultiLinkedData
{
  public:
    /** Default constructor **/
    FairTimeStamp();
    /** Constructor with time **/
    FairTimeStamp(Double_t time);
    /** Constructor with time and time error **/
    FairTimeStamp(Double_t time, Double_t timeerror);

    /** Destructor **/
    virtual ~FairTimeStamp();
    /** Accessors **/
    Double_t GetTimeStamp()             const { return fTimeStamp; };
    Double_t GetTimeStampError()     const { return fTimeStampError;};
    /** Modifiers **/
    void SetTimeStamp(Double_t t) { fTimeStamp = t; }
    void SetTimeStampError(Double_t t) {fTimeStampError = t;}

    Int_t Compare(const TObject* obj) const {
      if (this == obj) { return 0; }
      FairTimeStamp* tsobj = (FairTimeStamp*)obj;
      Double_t ts = tsobj->GetTimeStamp();
      if (fTimeStamp < ts) { return -1; }
      else if (fTimeStamp == ts) { return 0; }
      else { return 1; }
    }

    Bool_t IsSortable() const { return kTRUE;};

  protected:
    Double_t fTimeStamp;        /** Time of digit or Hit  [ns] */
    Double_t fTimeStampError;     /** Error on time stamp */

    ClassDef(FairTimeStamp,1);
};

#endif
