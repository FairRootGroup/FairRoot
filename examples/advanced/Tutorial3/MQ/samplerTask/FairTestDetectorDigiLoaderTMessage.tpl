/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Root TMessage transport data format

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>::Exec(Option_t* /*opt*/)
{
    TMessage* message = new TMessage(kMESS_OBJECT);
    message->WriteObject(fInput);
    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage(message->Buffer(),
                                                                 message->BufferSize(),
                                                                 [](void* /*data*/, void* obj){ delete static_cast<TMessage*>(obj); },
                                                                 message));
}
