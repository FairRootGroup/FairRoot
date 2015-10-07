/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   FairTestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef FAIRTESTDETECTORDIGILOADER_H
#define FAIRTESTDETECTORDIGILOADER_H

#include <iostream>
#include <type_traits>

#include <boost/timer/timer.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "TMessage.h"

#include "FairTestDetectorPayload.h"
#include "FairTestDetectorDigi.h"

#include "FairMQSamplerTask.h"
#include "FairMQLogger.h"

#include "baseMQtools.h"

using namespace std;

template <typename T1, typename T2>
class FairTestDetectorDigiLoader : public FairMQSamplerTask
{
  public:
    FairTestDetectorDigiLoader()
        : FairMQSamplerTask("Load class T1")
        , fDigiVector()
        , fHasBoostSerialization(false)
    {
        using namespace baseMQ::tools::resolve;
        // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
        if (is_same<T2, boost::archive::binary_oarchive>::value || is_same<T2, boost::archive::text_oarchive>::value)
        {
            if (has_BoostSerialization<T1, void(T2&, const unsigned int)>::value == 1)
            {
                fHasBoostSerialization = true;
            }
        }
    }

    virtual ~FairTestDetectorDigiLoader()
    {
        if (fDigiVector.size() > 0)
        {
            fDigiVector.clear();
        }
    }

    virtual void Exec(Option_t* opt);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& fDigiVector;
    }

  private:
    friend class boost::serialization::access;
    vector<T1> fDigiVector;
    bool fHasBoostSerialization;
};

// Template implementation is in FairTestDetectorDigiLoader.tpl :
#include "FairTestDetectorDigiLoaderBoost.tpl"
#include "FairTestDetectorDigiLoaderBin.tpl"
#include "FairTestDetectorDigiLoaderProtobuf.tpl"
#include "FairTestDetectorDigiLoaderTMessage.tpl"

#endif /* FAIRTESTDETECTORDIGILOADER_H */
