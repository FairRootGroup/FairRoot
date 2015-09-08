/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runProcessorRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 4:05 PM
 */

// FairRoot - FairMQ
#include "GenericProcessor.h"

// FairRoot - base/MQ
#include "RootSerializer.h"

// FairRoot - Tutorial7 
#include "tuto7ProcessorFunctions.h"
#include "DigiToHitTask.h"
#include "MyDigi.h"
#include "MyHit.h"



// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyDigi              TDigi; 
typedef MyHit               THit;
// build policy classes
//typedef MyDigiSerializer_t TInputPolicy;
typedef RootDeSerializer TInputPolicy;
typedef RootSerializer   TOutputPolicy;
typedef DigiToHitTask_TCA<TDigi,THit> TTaskPolicy; // process deserialized digi and fill Hit

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


