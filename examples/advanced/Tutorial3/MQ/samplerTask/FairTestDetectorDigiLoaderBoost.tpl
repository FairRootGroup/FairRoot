/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Default implementation of FairTestDetectorDigiLoader::Exec() with Boost transport data format

// example TOut: FairTestDetectorDigi
// example TPayloadOut: boost::archive::binary_oarchive, boost::archive::text_oarchive
template <typename TOut, typename TPayloadOut>
void FairTestDetectorDigiLoader<TOut, TPayloadOut>::Exec(Option_t* /*opt*/)
{
    std::ostringstream oss;
    TPayloadOut outputArchive(oss);
    for (int i = 0; i < fInput->GetEntriesFast(); ++i)
    {
        TOut* digi = static_cast<TOut*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        fDigiVector.push_back(*digi);
    }

    outputArchive << fDigiVector;
    std::string* strMsg = new std::string(oss.str());
    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage(const_cast<char*>(strMsg->c_str()), // data
                                                                                   strMsg->length(), // size
                                                                                   [](void* /*data*/, void* object){ delete static_cast<std::string*>(object); },
                                                                                   strMsg)); // object that manages the data

    fDigiVector.clear();
}
