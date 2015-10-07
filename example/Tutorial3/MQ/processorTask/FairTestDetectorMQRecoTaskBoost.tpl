/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Boost transport data format

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
void FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::Exec(Option_t* opt)
{
    if (fHasBoostSerialization)
    {
        int inputSize = fPayload->GetSize();

        // prepare boost input archive
        string msgStr(static_cast<char*>(fPayload->GetData()), fPayload->GetSize());
        istringstream ibuffer(msgStr);
        TPayloadIn InputArchive(ibuffer);
        try
        {
            InputArchive >> fDigiVector; // get input Archive
        }
        catch (boost::archive::archive_exception& e)
        {
            LOG(ERROR) << e.what();
        }
        fRecoTask->fDigiArray->Delete();
        int numInput = fDigiVector.size();

        for (int i = 0; i < numInput; ++i)
        {
            new ((*fRecoTask->fDigiArray)[i]) TIn(fDigiVector.at(i));
        }

        if (!fRecoTask->fDigiArray)
        {
            LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
        }

        fRecoTask->Exec(opt);
        int numOutput = numInput;

        if (inputSize > 0)
        {
            for (int i = 0; i < numOutput; ++i)
            {
                TOut* hit = (TOut*)fRecoTask->fHitArray->At(i);
                if (hit)
                {
                    fHitVector.push_back(*hit);
                }
            }
        }

        // prepare boost output archive
        ostringstream obuffer;
        TPayloadOut OutputArchive(obuffer);
        OutputArchive << fHitVector;
        int outputSize = obuffer.str().length();
        fPayload->Rebuild(outputSize);
        memcpy(fPayload->GetData(), obuffer.str().c_str(), outputSize);
        if (fDigiVector.size() > 0)
        {
            fDigiVector.clear();
        }
        if (fHitVector.size() > 0)
        {
            fHitVector.clear();
        }
    }
    else
    {
        LOG(ERROR) << "Boost Serialization not ok";
    }
}
