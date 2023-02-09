/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairTestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Root TMessage transport data format

#include "RootSerializer.h"

template<>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>::Exec(Option_t* /*opt*/)
{
    fPayload = fTransportFactory->CreateMessage();
    RootSerializer().Serialize(*fPayload, fInput);
}
