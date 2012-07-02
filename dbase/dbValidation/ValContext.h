#ifndef VALCONTEXT_H
#define VALCONTEXT_H

#include "TObject.h"
#include "Experiment.h"
#include "Detector.h"
#include "SimFlag.h"
#include "ValTimeStamp.h"

#include <iostream>
using namespace std;

class ValContext;

std::ostream& operator<<(std::ostream& os, const ValContext& vldc);

class ValContext : public TObject
{

  public:

    ValContext();                        // necessary for streamer io
    ValContext(const Detector::Detector_t& detector,
               const SimFlag::SimFlag_t mcflag,
               const ValTimeStamp& time);
    virtual ~ValContext();

    /// Return a formatted string of the contents of this object
    /// User should copy result because it points to a
    /// statically allocated string.
    const char* AsString(Option_t* option = "") const;

    Detector::Detector_t     GetDetector()  const { return fDetector;}
    SimFlag::SimFlag_t       GetSimFlag()   const { return fSimFlag;}
    ValTimeStamp             GetTimeStamp() const { return fTimeStamp;}

    /// Return true if this was initialized by default ctor
    /// we can only test experiment type and simflag
    Bool_t                   IsNull() const;
    /// Return opposite of IsNull()
    Bool_t                   IsValid() const { return !IsNull(); }

    void                     Print(Option_t* option = "") const;

    friend Bool_t operator< (const ValContext& lhs, const ValContext& rhs);
    friend Bool_t operator==(const ValContext& lhs, const ValContext& rhs);
    friend Bool_t operator!=(const ValContext& lhs, const ValContext& rhs);
    friend Bool_t operator<=(const ValContext& lhs, const ValContext& rhs);
    friend Bool_t operator> (const ValContext& lhs, const ValContext& rhs);
    friend Bool_t operator>=(const ValContext& lhs, const ValContext& rhs);

  protected:

    Detector::Detector_t       fDetector;
    SimFlag::SimFlag_t         fSimFlag;
    ValTimeStamp               fTimeStamp;

  private:

    ClassDef(ValContext,1)  // ValTimeStamp+Detector+SimFlag

};

#ifndef __CINT__

inline Bool_t operator< (const ValContext& lhs, const ValContext& rhs)
{
  // sorting is a little tricky with three fields
  // this sorts first by time then experiment then simflag
  // *WARNING* be very careful if you change this
  if ( lhs.fTimeStamp  < rhs.fTimeStamp ) { return true; }
  if ( lhs.fTimeStamp == rhs.fTimeStamp ) {
    if ( lhs.fDetector  < rhs.fDetector ) { return true; }
    if ( lhs.fDetector == rhs.fDetector ) {
      if (lhs.fSimFlag  < rhs.fSimFlag ) { return true; }
    }
  }
  return false;
}

inline Bool_t operator==(const ValContext& lhs, const ValContext& rhs)
{
  // equal if all components match
  return
    lhs.fDetector  == rhs.fDetector &&
    lhs.fSimFlag   == rhs.fSimFlag  &&
    lhs.fTimeStamp == rhs.fTimeStamp;
}

inline Bool_t operator!=(const ValContext& lhs, const ValContext& rhs)
{
  // not equal if any component doesn't match
  return
    lhs.fDetector  != rhs.fDetector ||
    lhs.fSimFlag   != rhs.fSimFlag  ||
    lhs.fTimeStamp != rhs.fTimeStamp;
}

inline Bool_t operator<=(const ValContext& lhs, const ValContext& rhs)
{
  return (lhs<rhs) || (lhs==rhs);
}

inline Bool_t operator>(const ValContext& lhs, const ValContext& rhs)
{
  return !(lhs<rhs) && !(lhs==rhs);
}

inline Bool_t operator>=(const ValContext& lhs, const ValContext& rhs)
{
  return !(lhs<rhs);
}


#endif /* __CINT__ */
#endif // VALCONTEXT_H
