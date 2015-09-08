/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runFileSinkRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 7:51 PM
 */

// FairRoot - FairMQ
#include "GenericFileSink.h"

// FairRoot - base/MQ
#include "RootSerializer.h"
#include "RootOutFileManager.h"

// FairRoot - Tutorial7
#include "tuto7FileSinkFunctions.h"
#include "MyHit.h"

// alternative to RootOutFileManager : BinaryOutFileManager
// storage policy of BinaryOutFileManager :
//#include "TriviallyCopyableDataSaver.h"
//#include "BoostDataSaver.h"

// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyHit                                        THit;
typedef RootDeSerializer                             TInputPolicy;
typedef RootOutFileManager<THit>                     TOutputPolicy;
typedef GenericFileSink<TInputPolicy,TOutputPolicy>  TSink;


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
