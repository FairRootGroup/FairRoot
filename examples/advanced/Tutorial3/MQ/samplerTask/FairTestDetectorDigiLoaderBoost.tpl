/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Default implementation of FairTestDetectorDigiLoader::Exec() with Boost transport data format

void freeStringBuffer(void* /*data*/, void* hint)
{
    delete static_cast<std::string*>(hint);
}

// example TOut: FairTestDetectorDigi
// example TPayloadOut: boost::archive::binary_oarchive, boost::archive::text_oarchive
template <typename TOut, typename TPayloadOut>
void FairTestDetectorDigiLoader<TOut, TPayloadOut>::Exec(Option_t* /*opt*/)
{
    // Write some data to check it on the receiver side
    // (*fBigBuffer)[7] = 'c';

    std::ostringstream oss;
    TPayloadOut OutputArchive(oss);
    for (int i = 0; i < fInput->GetEntriesFast(); ++i)
    {
        TOut* digi = static_cast<TOut*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        fDigiVector.push_back(*digi);
    }

    OutputArchive << fDigiVector;
    // OutputArchive << boost::serialization::make_binary_object(fBigBuffer->data(), sizeof(*fBigBuffer));
    std::string* strMsg = new std::string(oss.str());
    fOutput = fTransportFactory->CreateMessage(const_cast<char*>(strMsg->c_str()), strMsg->length(), freeStringBuffer, strMsg);

    fDigiVector.clear();
}
