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
    virtual Double_t GetTimeStamp()             const { return fTimeStamp; };
    virtual Double_t GetTimeStampError()     const { return fTimeStampError;};
    virtual FairLink GetEntryNr() const {return fEntryNr;}
    /** Modifiers **/
    virtual void SetTimeStamp(Double_t t) { fTimeStamp = t; }
    virtual void SetTimeStampError(Double_t t) {fTimeStampError = t;}
    virtual void SetEntryNr(FairLink entry) {fEntryNr = entry;}
    virtual Int_t Compare(const TObject* obj) const {
      if (this == obj) { return 0; }
      FairTimeStamp* tsobj = (FairTimeStamp*)obj;
      Double_t ts = tsobj->GetTimeStamp();
      Double_t tserror = tsobj->GetTimeStampError();
      if (fTimeStamp < ts) { return -1; }
      else if (fTimeStamp == ts && fTimeStampError < tserror) { return -1; }
      else if (fTimeStamp == ts && fTimeStampError == tserror) { return 0; }
      else { return 1; }
    }


    void Print(std::ostream& out = std::cout) const;
    virtual Bool_t IsSortable() const { return kTRUE;};


    virtual bool equal(FairTimeStamp* data) {
      return (fTimeStamp == data->GetTimeStamp() && fTimeStampError == data->GetTimeStampError());
    }

    friend std::ostream& operator<< (std::ostream& out, const FairTimeStamp& link) {
      link.Print(out);
      return out;
    }


  protected:
    Double_t fTimeStamp;        /** Time of digit or Hit  [ns] */
    Double_t fTimeStampError;     /** Error on time stamp */
    FairLink fEntryNr; //!  indicates where the data is stored in the branch

    ClassDef(FairTimeStamp,2);
};

#endif
