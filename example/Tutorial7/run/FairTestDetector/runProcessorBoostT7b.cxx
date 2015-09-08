/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runProcessorBoost.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

// FairRoot - FairMQ
#include "GenericProcessor.h"

// FairRoot - base/MQ
#include "BoostSerializer.h"

// FairRoot - Tutorial7 
#include "tuto7ProcessorFunctions.h"
#include "DigiToHitTask.h"

// FairRoot - Tutorial3 
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"

// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorDigi              TDigi; 
typedef FairTestDetectorHit               THit;

// policy classes
typedef BoostDeSerializer<TDigi>          TInputPolicy;   // deserialize digi
typedef BoostSerializer<THit>             TOutputPolicy;  // serialize Hit
typedef DigiToHitTask<TDigi,THit>         TTaskPolicy;    // process deserialized digi and fill Hit

typedef GenericProcessor<TInputPolicy,TOutputPolicy,TTaskPolicy> TProcessor;

int main(int argc, char** argv)
{
    try
    {
        TProcessor processor;
        if (runProcessor<TProcessor, BoostProcessorPolicyFlag>(processor, argc, argv))
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
