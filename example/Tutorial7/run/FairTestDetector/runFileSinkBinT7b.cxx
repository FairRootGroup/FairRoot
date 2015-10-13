/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runFileSinkBin.cxx
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
#include "MyHitSerializer.h"

// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"

// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorHit                         THit;
typedef Tuto3HitDeSerializer_t                      TInputPolicy;
typedef RootOutFileManager<THit>                    TOutputPolicy;
typedef GenericFileSink<TInputPolicy,TOutputPolicy> TSink;

int main(int argc, char** argv)
{
    try
    {
        TSink filesink;
        if (runFileSink(filesink, argc, argv))
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
