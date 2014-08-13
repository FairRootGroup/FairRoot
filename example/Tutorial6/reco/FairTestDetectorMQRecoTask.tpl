/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

////////// Base template class <T1,T2>

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::FairTestDetectorMQRecoTask()
    : fRecoTask(NULL), fRtdb(NULL)
{
    fHasBoostSerialization = true;

#if __cplusplus >= 201103L

    bool checkInputClass = false;
    bool checkOutputClass = false;
    fHasBoostSerialization = false;

    if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
    {
        if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            checkInputClass = true;
    }

    if (std::is_same<TPayloadOut, boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut, boost::archive::text_oarchive>::value)
    {
        if (has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 1)
            checkOutputClass = true;
    }

    if (checkInputClass && checkOutputClass)
        fHasBoostSerialization = true;
#endif
}

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::FairTestDetectorMQRecoTask(Int_t verbose)
    : fRecoTask(NULL) , fRtdb(NULL)
{
    fHasBoostSerialization = true;
#if __cplusplus >= 201103L
    bool checkInputClass = false;
    bool checkOutputClass = false;
    fHasBoostSerialization = false;

    if (std::is_same<TPayloadIn, boost::archive::binary_iarchive>::value || std::is_same<TPayloadIn, boost::archive::text_iarchive>::value)
    {
        if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            checkInputClass = true;
        else
            LOG(ERROR) << "Method 'void serialize(TIn & ar, const unsigned int version)' was not found in input class";
    }
    else
    {
        LOG(ERROR) << "Output payload is not of supported boost archive type";
        LOG(ERROR) << "Boost inpput archive type supported : ";
        LOG(ERROR) << "boost::archive::binary_iarchive and boost::archive::text_iarchive";
    }

    if (std::is_same<TPayloadOut, boost::archive::binary_oarchive>::value || std::is_same<TPayloadOut, boost::archive::text_oarchive>::value)
    {
        if (has_BoostSerialization<TOut, void(TPayloadOut&, const unsigned int)>::value == 1)
            checkOutputClass = true;
        else
            LOG(ERROR) << "Method 'void serialize(TOut & ar, const unsigned int version)' was not found in input class";
    }
    else
    {
        LOG(ERROR) << "Output payload is not of supported boost archive type";
        LOG(ERROR) << "Boost output archive type supported : ";
        LOG(ERROR) << "boost::archive::binary_oarchive and boost::archive::text_oarchive";
    }

    if (checkInputClass && checkOutputClass)
        fHasBoostSerialization = true;

#endif
}

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::~FairTestDetectorMQRecoTask()
{
    fRecoTask->fDigiArray->Delete();
    fRecoTask->fHitArray->Delete();
    if (fRecoTask->fEvtHeader) delete fRecoTask->fEvtHeader;
    delete fRecoTask;
    if (fRtdb) delete fRtdb;
 
   if (fDigiVector.size() > 0)
        fDigiVector.clear();
    if (fHitVector.size() > 0)
        fHitVector.clear();
}

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
InitStatus FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::Init()
{
    fRecoTask = new FairTestDetectorRecoTask();
    fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
    fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");
    fRecoTask->fEvtHeader = new FairEventHeader();

    return kSUCCESS;
}

// ----- Implementation of FairTestDetectorMQRecoTask::Exec() with Boost transport data format -----

template <typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
void FairTestDetectorMQRecoTask<TIn, TOut, TPayloadIn, TPayloadOut>::Exec(Option_t* opt)
{
    if (fHasBoostSerialization)
    {
        int inputSize = fPayload->GetSize();

        // prepare boost input archive
        std::string msgStr(static_cast<char*>(fPayload->GetData()), fPayload->GetSize());
        std::istringstream ibuffer(msgStr);
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
        std::ostringstream obuffer;
        TPayloadOut OutputArchive(obuffer);
        OutputArchive << fHitVector;
        int outputSize = obuffer.str().length();
        fPayload->Rebuild(outputSize);
        std::memcpy(fPayload->GetData(), obuffer.str().c_str(), outputSize);
        if (fDigiVector.size() > 0)
            fDigiVector.clear();
        if (fHitVector.size() > 0)
            fHitVector.clear();
    }
    else
    {
        LOG(ERROR) << " Boost Serialization not ok";
    }
}

// ----- Implementation of FairTestDetectorMQRecoTask::Exec() with pure binary transport data format -----

template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorPayload::Digi, TestDetectorPayload::Hit>::Exec(Option_t* opt)
{
    // // Example how to receive multipart message (uncomment the code lines to test).
    // // 1. receive the first part.
    // std::string test = std::string(static_cast<char*>(fPayload->GetData()), fPayload->GetSize());
    // LOG(ERROR) << test;
    // // Ask Processor for the next part.
    // ReceivePart();

   // Check for Init
   int* ptr =  reinterpret_cast<int*>(fPayload->GetData());
    LOG(INFO) << " FairTestDetectorMQRecoTask RID# "<< *ptr << endl; 

    // Set the runID linked to data
    fRecoTask->InitWithId(*ptr);
    // Get the RuntimeDB
    fRtdb = fRecoTask->GetRtdb();     
 
    if (fRtdb){
       FairDbTutPar* par = (FairDbTutPar*)(fRtdb->getContainer("TUTParDefault"));
       if (par){ 		
          par->Print();	
        } 				
    }

    ptr++;						   

    // Get the actual Paylaod    
    int inputSize = fPayload->GetSize()-sizeof(int);
    int numInput = inputSize / sizeof(TestDetectorPayload::Digi);
    TestDetectorPayload::Digi* input = reinterpret_cast<TestDetectorPayload::Digi*>(ptr);

    fRecoTask->fDigiArray->Delete();

    for (int i = 0; i < numInput; ++i)
    {
        new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(input[i].fX, input[i].fY, input[i].fZ, input[i].fTimeStamp);
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    int numOutput = numInput;
    int outputSize = numOutput * sizeof(TestDetectorPayload::Hit);

    fPayload->Rebuild(outputSize);
    TestDetectorPayload::Hit* output = reinterpret_cast<TestDetectorPayload::Hit*>(fPayload->GetData());

    if (inputSize > 0)
    {
        for (int i = 0; i < numOutput; ++i)
        {
            FairTestDetectorHit* hit = (FairTestDetectorHit*)fRecoTask->fHitArray->At(i);

            output[i].detID = hit->GetDetectorID();
            output[i].posX = hit->GetX();
            output[i].posY = hit->GetY();
            output[i].posZ = hit->GetZ();
            output[i].dposX = hit->GetDx();
            output[i].dposY = hit->GetDy();
            output[i].dposZ = hit->GetDz();
        }
    }
}

// ----- Implementation of FairTestDetectorMQRecoTask::Exec() with Root TMessage transport data format -----

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
void free_tmessage (void *data, void *hint)
{
    delete (TMessage*)hint;
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

// ----- Implementation of FairTestDetectorMQRecoTask::Exec() with Google Protocol Buffers transport data format -----

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"

// helper function to clean up the object holding the data after it is transported.
void free_string (void *data, void *hint)
{
    delete (std::string*)hint;
}

template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorProto::DigiPayload, TestDetectorProto::HitPayload>::Exec(Option_t* opt)
{

    fRecoTask->fDigiArray->Delete();

    TestDetectorProto::DigiPayload dp;
    dp.ParseFromArray(fPayload->GetData(), fPayload->GetSize());

    int numEntries = dp.digi_size();

    for (int i = 0; i < numEntries; ++i)
    {
        const TestDetectorProto::Digi& digi = dp.digi(i);
        new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(digi.fx(), digi.fy(), digi.fz(), digi.ftimestamp());
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    TestDetectorProto::HitPayload hp;

    for (int i = 0; i < numEntries; ++i)
    {
        FairTestDetectorHit* hit = (FairTestDetectorHit*)fRecoTask->fHitArray->At(i);
        if (!hit)
        {
            continue;
        }
        TestDetectorProto::Hit* h = hp.add_hit();
        h->set_detid(hit->GetDetectorID());
        h->set_posx(hit->GetX());
        h->set_posy(hit->GetY());
        h->set_posz(hit->GetZ());
        h->set_dposx(hit->GetDx());
        h->set_dposy(hit->GetDy());
        h->set_dposz(hit->GetDz());
    }

    std::string* str = new std::string();
    hp.SerializeToString(str);
    size_t size = str->length();

    fPayload->Rebuild(const_cast<char*>(str->c_str()), size, free_string, str);
    // fPayload->Rebuild(size);
    // memcpy(fPayload->GetData(), str.c_str(), size);
}

#endif /* PROTOBUF */
