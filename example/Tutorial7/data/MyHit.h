/* 
 * File:   MyHit.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:40 PM
 */

#ifndef MYHITDATA_H
#define	MYHITDATA_H

#include "FairHit.h" // for FairHit

#include "Rtypes.h" // for MyHit::Class, etc

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class MyHit : public FairHit
{
  public:
    /** Default constructor **/
    MyHit();

    /** Constructor **/
    MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~MyHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;

#endif // for BOOST serialization

    ClassDef(MyHit, 1);
};


#endif	/* MYHITDATA_H */

