/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Root TMessage transport data format

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void *data, void *hint)
{
    delete static_cast<TMessage*>(hint);
}

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>::Exec(Option_t* opt)
{
    TMessage* message = new TMessage(kMESS_OBJECT);
    message->WriteObject(fInput);
    fOutput = fTransportFactory->CreateMessage(message->Buffer(), message->BufferSize(), free_tmessage, message);
}
