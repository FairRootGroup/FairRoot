/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runProcessorBin.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

// FairRoot - FairMQ
#include "GenericProcessor.h"

// FairRoot - Tutorial7 
#include "tuto7ProcessorFunctions.h"
#include "MyDigiSerializer.h"
#include "MyHitSerializer.h"
#include "DigiToHitTask.h"

// FairRoot - Tutorial3 
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"


// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorDigi              TDigi;
typedef FairTestDetectorHit               THit;

// policy classes
typedef Tuto3DigiDeSerializer_t           TInputPolicy;
typedef Tuto3HitSerializer_t              TOutputPolicy;
typedef DigiToHitTask_TCA<TDigi,THit>     TTaskPolicy; // process deserialized digi and fill Hit

typedef GenericProcessor<TInputPolicy,TOutputPolicy,TTaskPolicy> TProcessor;

int main(int argc, char** argv)
{
    try
    {
        TProcessor processor;
        if (runProcessor(processor, argc, argv))
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

