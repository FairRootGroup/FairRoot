/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Root TMessage transport data format

// special class to expose protected TMessage constructor
class TestDetectorTMessage : public TMessage
{
  public:
    TestDetectorTMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void *data, void *hint)
{
    delete static_cast<TMessage*>(hint);
}

template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage, TMessage>::Exec(Option_t* opt)
{
    TestDetectorTMessage tm(fPayload->GetData(), fPayload->GetSize());

    fRecoTask->fDigiArray = (TClonesArray*)(tm.ReadObject(tm.GetClass()));

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    delete fRecoTask->fDigiArray;

    TMessage* out = new TMessage(kMESS_OBJECT);
    out->WriteObject(fRecoTask->fHitArray);
    fPayload->Rebuild(out->Buffer(), out->BufferSize(), free_tmessage, out);
}
