/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runGenericFileSink.cxx
 * Author: winckler
 *
 * Created on November 12, 2014, 6:39 PM
 */

// FairRoot - FairMQ
#include "GenericFileSink.h"

// FairRoot - base/MQ
#include "BoostSerializer.h"
#include "RootOutFileManager.h"

// Alternative storage policies:
// #include "BinaryOutFileManager.h" // store data in binary file using one of the policy:
// 1) //#include "TriviallyCopyableDataSaver.h" // policy that store data using binary
// 2) //#include "BoostDataSaver.h" // policy that store data using boost serialization

// FairRoot - Tutorial7
#include "tuto7FileSinkFunctions.h"


// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"

// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorHit                         THit;    // non POD/complex data
typedef BoostDeSerializer<THit,TClonesArray*>       TInputPolicy; // boost non pod, return TClonesArray*
typedef RootOutFileManager<THit>                    TOutputPolicy; // root non pod
typedef GenericFileSink<TInputPolicy,TOutputPolicy> TSink;    // rootfile/non pod/Boost deserialize/TClonesArray* API

int main(int argc, char** argv)
{
    try
    {
        TSink filesink;
        if (runFileSink<TSink, BoostFileSinkPolicyFlag>(filesink, argc, argv))
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