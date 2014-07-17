/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   TestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef TESTDETECTORDIGILOADER_H
#define TESTDETECTORDIGILOADER_H

#include "FairMQSamplerTask.h"

#include "FairMQLogger.h"
#include <boost/timer/timer.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "TMessage.h"

#include "FairTestDetectorPayload.h"
#include <iostream>

#if __cplusplus >= 201103L
#include "has_BoostSerialization.h"
#include <type_traits>
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////

////////// Base template header <T1,T2>
template <typename T1, typename T2>
class TestDetectorDigiLoader : public FairMQSamplerTask
{
  public:
    TestDetectorDigiLoader();
    virtual ~TestDetectorDigiLoader();
    virtual void Exec(Option_t* opt);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fDigiVector;
    }

  private:
    friend class boost::serialization::access;
    std::vector<T1> fDigiVector;
    bool fHasBoostSerialization;
};

////////// Template implementation is in TestDetectorDigiLoader.tpl :
#include "TestDetectorDigiLoader.tpl"

#endif /* TESTDETECTORDIGILOADER_H */
