/*
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Default implementation of FairTestDetectorDigiLoader::Exec() with Boost transport data format
template <typename T1, typename T2>
void FairTestDetectorDigiLoader<T1, T2>::Exec(Option_t* opt)
{
    // Default implementation of the base template Exec function using boost
    // the condition check if the input class has a function member with name
    // void serialize(T2 & ar, const unsigned int version) and if the payload are of boost type

    if (fHasBoostSerialization)
    {
        ostringstream buffer;
        T2 OutputArchive(buffer);
        for (Int_t i = 0; i < fInput->GetEntriesFast(); ++i)
        {
            T1* digi = static_cast<T1*>(fInput->At(i));
            if (!digi)
            {
                continue;
            }
            fDigiVector.push_back(*digi);
        }

        OutputArchive << fDigiVector;
        int size = buffer.str().length();
        fOutput = fTransportFactory->CreateMessage(size);
        memcpy(fOutput->GetData(), buffer.str().c_str(), size);

        // delete the vector content
        if (fDigiVector.size() > 0)
        {
            fDigiVector.clear();
        }
    }
    else
    {
        LOG(ERROR) << "Boost Serialization not available";
    }
}
