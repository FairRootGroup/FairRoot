/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Default implementation of FairTestDetectorDigiLoader::Exec() with Boost transport data format

#include "BoostSerializer.h"

// example TOut: FairTestDetectorDigi
// example TPayloadOut: boost::archive::binary_oarchive
template <typename TOut, typename TPayloadOut>
void FairTestDetectorDigiLoader<TOut, TPayloadOut>::Exec(Option_t* /*opt*/)
{
    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage());
    BoostSerializer<TOut>().Serialize(*fPayload, fInput);
}
