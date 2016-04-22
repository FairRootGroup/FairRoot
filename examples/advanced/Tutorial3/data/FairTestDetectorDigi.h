/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigi.h
 *
 *  Created on: 20.07.2012
 *      Author: stockman
 */

#ifndef FAIRTESTDETECTORDIGI_H_
#define FAIRTESTDETECTORDIGI_H_

#include "FairTimeStamp.h" // for FairTimeStamp

#include "Riosfwd.h" // for ostream
#include "Rtypes.h"  // for Int_t, etc

#include <iostream> // for operator<<, basic_ostream, etc
#include <string>
#include <sstream>

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class FairTestDetectorDigi : public FairTimeStamp
{
 public:
    FairTestDetectorDigi();
    FairTestDetectorDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp);
    virtual ~FairTestDetectorDigi();

    void SetXYZ(Int_t x, Int_t y, Int_t z)
    {
        SetX(x);
        SetY(y);
        SetZ(z);
    }
    void SetX(Int_t x)
    {
        fX = x;
    }
    void SetY(Int_t y)
    {
        fY = y;
    }
    void SetZ(Int_t z)
    {
        fZ = z;
    }

    Int_t GetX() const
    {
        return fX;
    }
    Int_t GetY() const
    {
        return fY;
    }
    Int_t GetZ() const
    {
        return fZ;
    }

    // temporary to avoid serialisation of the parent class
    virtual bool equal(FairTimeStamp* data)
    {
        FairTestDetectorDigi* myDigi = dynamic_cast<FairTestDetectorDigi*>(data);
        if (myDigi != 0)
        {
            if (fX == myDigi->GetX())
                if (fY == myDigi->GetY())
                    if (fZ == myDigi->GetZ())
                    {
                        return true;
                    }
        }
        return false;
    }

    virtual bool operator<(const FairTestDetectorDigi& myDigi) const
    {
        if (fX < myDigi.GetX())
        {
            return true;
        }
        else if (fX > myDigi.GetX())
        {
            return false;
        }
        if (fY < myDigi.GetY())
        {
            return true;
        }
        else if (fY > myDigi.GetY())
        {
            return false;
        }
        if (fZ < myDigi.GetZ())
        {
            return true;
        }
        else if (fZ > myDigi.GetZ())
        {
            return false;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, FairTestDetectorDigi& digi)
    {
        out << "FairTestDetectorDigi at:"
            << " (" << digi.GetX() << "/" << digi.GetY() << "/" << digi.GetZ() << ") "
            << " with TimeStamp: " << digi.GetTimeStamp() << std::endl;
        return out;
    }

    template <class T>
    std::string ToString (const T& value)
    {
      std::stringstream ss;
      ss.precision(5);
      ss << value;
      return ss.str();
    }

    std::string ToString()
    {
      std::string out = "FairTestDetectorDigi at: (" + ToString(GetX()) 
  	    + "/" + ToString(GetY()) + "/" + ToString(GetZ()) 
 	    + ") " + " with TimeStamp: " + ToString(GetTimeStamp());
      return out;
    }

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
        ar& fX;
        ar& fY;
        ar& fZ;
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Int_t fX;
    Int_t fY;
    Int_t fZ;

    ClassDef(FairTestDetectorDigi, 1);
};

#endif /* FAIRTESTDETECTORDIGI_H_ */
