/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyDigi.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:31 PM
 */

#ifndef MYDIGI_H
#define MYDIGI_H

#include <FairTimeStamp.h>   // for FairTimeStamp
#include <FairTimeStampBoostSerializationSupport.h>
#include <Rtypes.h>   // for Int_t, etc
#include <iosfwd>     // for ostream
#include <iostream>   // for operator<<, basic_ostream, etc

namespace boost {
namespace serialization {
class access;
}
}   // namespace boost
#include <boost/serialization/base_object.hpp>

class MyDigi : public FairTimeStamp
{
  public:
    MyDigi() = default;

    MyDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp, Double_t timeStampError = 0.0)
        : FairTimeStamp(timeStamp, timeStampError)
        , fX(x)
        , fY(y)
        , fZ(z)
    {}

    ~MyDigi() override = default;

    void SetXYZ(Int_t x, Int_t y, Int_t z)
    {
        SetX(x);
        SetY(y);
        SetZ(z);
    }
    void SetX(Int_t x) { fX = x; }
    void SetY(Int_t y) { fY = y; }
    void SetZ(Int_t z) { fZ = z; }

    Int_t GetX() const { return fX; }
    Int_t GetY() const { return fY; }
    Int_t GetZ() const { return fZ; }

    // temporary to avoid serialisation of the parent class
    bool equal(FairTimeStamp* data) override
    {
        MyDigi* myDigi = dynamic_cast<MyDigi*>(data);
        if (myDigi != 0) {
            if (fX == myDigi->GetX())
                if (fY == myDigi->GetY())
                    if (fZ == myDigi->GetZ()) {
                        return true;
                    }
        }
        return false;
    }

    virtual bool operator<(const MyDigi& myDigi) const
    {
        if (fX < myDigi.GetX()) {
            return true;
        } else if (fX > myDigi.GetX()) {
            return false;
        }
        if (fY < myDigi.GetY()) {
            return true;
        } else if (fY > myDigi.GetY()) {
            return false;
        }
        if (fZ < myDigi.GetZ()) {
            return true;
        } else if (fZ > myDigi.GetZ()) {
            return false;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, MyDigi& digi)
    {
        out << "MyDigi at:"
            << " (" << digi.GetX() << "/" << digi.GetY() << "/" << digi.GetZ() << ") "
            << " with TimeStamp: " << digi.GetTimeStamp() << std::endl;
        return out;
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
        ar& fX;
        ar& fY;
        ar& fZ;
    }

  private:
    friend class boost::serialization::access;

    Int_t fX = 0;
    Int_t fY = 0;
    Int_t fZ = 0;

    ClassDefOverride(MyDigi, 1);
};

#endif /* MYDIGI_H */
