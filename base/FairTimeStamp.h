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
    /** Destructor **/
    virtual ~FairTimeStamp();
    /** Accessors **/
    Double_t GetTimeStamp()             const { return fTimeStamp; };
    /** Modifiers **/
    void SetTimeStamp(Double_t t) { fTimeStamp = t; }
  protected:
    Double_t fTimeStamp;        /** Time of digit or Hit  [ns] */
    ClassDef(FairTimeStamp,1);
};

#endif
