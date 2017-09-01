/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Boost transport data format

void freeStringBuffer(void* /*data*/, void* hint)
{
    delete static_cast<std::string*>(hint);
}

// example TIn: FairTestDetectorDigi
// example TOut: FairTestDetectorHit
// example TPayloadIn: boost::archive::binary_iarchive, boost::archive::text_iarchive
// example TPayloadOut: boost::archive::binary_oarchive, boost::archive::text_oarchive
template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
void FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::Exec(Option_t* opt)
{
    int inputSize = fPayload->GetSize();

    // prepare boost input archive
    std::string msgStr(static_cast<char*>(fPayload->GetData()), fPayload->GetSize());
    std::istringstream iss(msgStr);
    TPayloadIn onputArchive(iss);
    try
    {
        onputArchive >> fDigiVector;
    }
    catch (boost::archive::archive_exception& e)
    {
        LOG(ERROR) << e.what();
    }

    fRecoTask->fDigiArray->Clear();
    int numEntries = fDigiVector.size();

    for (int i = 0; i < numEntries; ++i)
    {
        new ((*fRecoTask->fDigiArray)[i]) TIn(fDigiVector.at(i));
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    if (inputSize > 0)
    {
        for (int i = 0; i < numEntries; ++i)
        {
            TOut* hit = static_cast<TOut*>(fRecoTask->fHitArray->At(i));
            if (hit)
            {
                fHitVector.push_back(*hit);
            }
        }
    }

    // prepare boost output archive
    std::ostringstream oss;
    TPayloadOut outputArchive(oss);
    outputArchive << fHitVector;
    std::string* strMsg = new std::string(oss.str());
    fPayload->Rebuild(const_cast<char*>(strMsg->c_str()), strMsg->length(), freeStringBuffer, strMsg);

    fDigiVector.clear();
    fHitVector.clear();
}
