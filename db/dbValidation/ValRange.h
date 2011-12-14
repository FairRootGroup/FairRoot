
#ifndef VALRANGE_H
#define VALRANGE_H

#include "TObject.h"
#include "TString.h"
#include "Detector.h"
#include "ValTimeStamp.h"
#include <iostream>

using namespace std;

class ValContext;

class ValRange;
std::ostream& operator<<(std::ostream& os, const ValRange& vldr);


class ValRange : public TObject
{

  public:

    ValRange();
    ValRange(const Int_t detMask, const Int_t simMask,
             const ValTimeStamp& tstart, const ValTimeStamp& tend,
             const TString& source);
    virtual ~ValRange();

    /** Return the ValRange as a string
     *
     * Result is a pointer to a statically allocated string.
     * User should copy this into their own buffer before calling
     * this method again.
     *
     * option "a": give detector/simflag masks as alpha chars
     * option "c": compact (single line)
     * option "s": drop nsec part of times
     * option "1": include only "start time"
     * option "-": don't include "source" info
     */
    const char* AsString(Option_t* option = "") const;

    /** Compare ValContext with this ValRange to see if the
     * the tagged set is compatible.*/
    Bool_t IsCompatible(const ValContext& vldc) const;
    /** Compare ValContext with this ValRange to see if the
     * the tagged set is compatible.*/
    Bool_t IsCompatible(const ValContext* vldc) const;

    Int_t  GetDetectorMask()    const { return fDetectorMask; }
    Int_t  GetSimMask()         const { return fSimMask; }
    ValTimeStamp GetTimeStart() const { return fTimeStart; }
    ValTimeStamp GetTimeEnd()   const { return fTimeEnd; }
    TString GetDataSource()     const { return fDataSource; }

    /// Print to stdout.  See AsString()  for options.
    void Print(Option_t* option = "") const;

    /// Trim this range to the intersection (ie. more restricted)
    /// limits of it's initial value and that of the argument
    void TrimTo(const ValRange& vldr);
    void SetTimeStart(const ValTimeStamp& tstart) { fTimeStart = tstart; }
    void SetTimeEnd(const ValTimeStamp& tend) { fTimeEnd = tend; }

  protected:

    Int_t              fDetectorMask; /// or's Detector::Detector_t
    Int_t              fSimMask;      /// or's of data/mc conditions
    ValTimeStamp       fTimeStart;
    ValTimeStamp       fTimeEnd;
    TString            fDataSource;

  private:

    ClassDef(ValRange,1)  // ValRange version 1
};

#endif // VALRANGE_H
