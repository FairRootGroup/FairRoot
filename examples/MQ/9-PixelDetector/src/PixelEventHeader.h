/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelEventHeader.h
 *
 *  Created on: 18.03.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELEVENTHEADER_H_
#define PIXELEVENTHEADER_H_

#include "FairEventHeader.h"     // for FairEventHeader

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class PixelEventHeader : public FairEventHeader
{
  public:
    /** Default constructor **/
    PixelEventHeader();

    /** Destructor **/
    virtual ~PixelEventHeader();

    void  SetPartNo(Int_t ipart) { fPartNo = ipart;}
    Int_t GetPartNo()            { return fPartNo; }

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairEventHeader>(*this);
    }

  private:
    Int_t fPartNo;

#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    ClassDef(PixelEventHeader, 1);
};

#endif /* PIXELEVENTHEADER_H_ */
