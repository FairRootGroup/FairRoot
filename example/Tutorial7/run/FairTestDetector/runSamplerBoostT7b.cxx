/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerBoostT7b.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 10:45 PM
 */

// FairRoot - FairMQ
#include "GenericSampler.h"

// FairRoot - Base/MQ
// sampler & serialization policies
#include "SimpleTreeReader.h"
#include "BoostSerializer.h"

// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "FairTestDetectorDigi.h"

// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorDigi                            TDigi;
// sampler and serialization policy
typedef SimpleTreeReader<TClonesArray>                  TSamplerPolicy;
typedef BoostSerializer<TDigi>                          TSerializePolicy;
// build sampler type
typedef GenericSampler<TSamplerPolicy, TSerializePolicy> TSampler;

int main(int argc, char** argv)
{
    try
    {
        TSampler sampler;
        if (runSampler(sampler, argc, argv))
        {
            return 1;
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
