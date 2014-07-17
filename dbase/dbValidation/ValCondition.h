/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef VALCONDITION_H
#define VALCONDITION_H

#include "TObject.h"                    // for TObject

#include "DataType.h"                    // for DataType_t
#include "ValTimeStamp.h"               // for ValTimeStamp, operator==, etc
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Bool_t, Option_t, etc

#include <iostream>                     // for ostream

class ValCondition : public TObject
{

  public:

    ValCondition();                        // necessary for streamer io
    ValCondition(const Detector::Detector_t& detector,
                 const DataType::DataType_t mcflag,
                 const ValTimeStamp& time);
    virtual ~ValCondition();

    /// Return a formatted string of the contents of this object
    /// User should copy result because it points to a
    /// statically allocated string.
    const char* AsString(Option_t* option = "") const;

    Detector::Detector_t     GetDetector()  const { return fDetector;}
    DataType::DataType_t       GetDataType()   const { return fDataType;}
    ValTimeStamp             GetTimeStamp() const { return fTimeStamp;}

    /// Return true if this was initialized by default ctor
    /// we can only test experiment type and datatype
    Bool_t                   IsNull() const;
    /// Return opposite of IsNull()
    Bool_t                   IsValid() const { return !IsNull(); }

    void                     Print(Option_t* option = "") const;

    friend Bool_t operator< (const ValCondition& lhs, const ValCondition& rhs);
    friend Bool_t operator==(const ValCondition& lhs, const ValCondition& rhs);
    friend Bool_t operator!=(const ValCondition& lhs, const ValCondition& rhs);
    friend Bool_t operator<=(const ValCondition& lhs, const ValCondition& rhs);
    friend Bool_t operator> (const ValCondition& lhs, const ValCondition& rhs);
    friend Bool_t operator>=(const ValCondition& lhs, const ValCondition& rhs);

  protected:

    Detector::Detector_t       fDetector;
    DataType::DataType_t         fDataType;
    ValTimeStamp               fTimeStamp;

  private:

    ClassDef(ValCondition,1)  // COMBO (Detector,DataType, TimeStamp)

};

std::ostream& operator<<(std::ostream& os, const ValCondition& vldc);

#ifndef __CINT__

inline Bool_t operator< (const ValCondition& lhs, const ValCondition& rhs)
{
  if ( lhs.fTimeStamp  < rhs.fTimeStamp ) { return true; }
  if ( lhs.fTimeStamp == rhs.fTimeStamp ) {
    if ( lhs.fDetector  < rhs.fDetector ) { return true; }
    if ( lhs.fDetector == rhs.fDetector ) {
      if (lhs.fDataType  < rhs.fDataType ) { return true; }
    }
  }
  return false;
}

inline Bool_t operator==(const ValCondition& lhs, const ValCondition& rhs)
{
  return (
           lhs.fDetector  == rhs.fDetector &&
           lhs.fDataType   == rhs.fDataType  &&
           lhs.fTimeStamp == rhs.fTimeStamp );

}

inline Bool_t operator!=(const ValCondition& lhs, const ValCondition& rhs)
{

  return (
           lhs.fDetector  != rhs.fDetector ||
           lhs.fDataType   != rhs.fDataType  ||
           lhs.fTimeStamp != rhs.fTimeStamp );
}

inline Bool_t operator<=(const ValCondition& lhs, const ValCondition& rhs)
{
  return (lhs<rhs) || (lhs==rhs);
}

inline Bool_t operator>(const ValCondition& lhs, const ValCondition& rhs)
{
  return !(lhs<rhs) && !(lhs==rhs);
}

inline Bool_t operator>=(const ValCondition& lhs, const ValCondition& rhs)
{
  return !(lhs<rhs);
}

#endif
#endif // VALCONDITION_H
