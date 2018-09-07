/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Root TMessage transport data format

#include "RootSerializer.h"

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>::Exec(Option_t* /*opt*/)
{
    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage());
    RootSerializer().Serialize(*fPayload, fInput);
}
