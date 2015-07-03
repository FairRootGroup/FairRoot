/*
 * File:   FairMQFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

template <typename TIn, typename TPayloadIn>
FairMQFileSink<TIn, TPayloadIn>::FairMQFileSink()
    : fOutFile(NULL)
    , fTree(NULL)
    , fOutput(NULL)
    , fHitVector()
    , fHasBoostSerialization()
{
    gSystem->ResetSignal(kSigInterrupt);
    gSystem->ResetSignal(kSigTermination);

    fHasBoostSerialization = true;
#if __cplusplus >= 201103L
    using namespace baseMQ::tools::resolve;
    fHasBoostSerialization = false;
    // coverity[pointless_expression]: suppress coverity warnings on apparant if(const).
    if (is_same<TPayloadIn, boost::archive::binary_iarchive>::value || is_same<TPayloadIn, boost::archive::text_iarchive>::value)
    {
        if (has_BoostSerialization<TIn, void(TPayloadIn&, const unsigned int)>::value == 1)
            fHasBoostSerialization = true;
    }
#endif
}

template <typename TIn, typename TPayloadIn>
FairMQFileSink<TIn, TPayloadIn>::~FairMQFileSink()
{
    fTree->Write();
    fOutFile->Close();
    if (fHitVector.size() > 0)
        fHitVector.clear();
}

template <typename TIn, typename TPayloadIn>
void FairMQFileSink<TIn, TPayloadIn>::InitOutputFile(TString defaultId)
{
    fOutput = new TClonesArray("FairTestDetectorHit");
    char out[256];
    sprintf(out, "filesink%s.root", defaultId.Data());

    fOutFile = new TFile(out, "recreate");
    fTree = new TTree("MQOut", "Test output");
    fTree->Branch("Output", "TClonesArray", &fOutput, 64000, 99);
}

// ----- Implementation of FairMQFileSink::Run() with Boost transport data format -----

template <typename TIn, typename TPayloadIn>
void FairMQFileSink<TIn, TPayloadIn>::Run()
{
    if (fHasBoostSerialization)
    {
        int receivedMsgs = 0;

        // store the channel references to avoid traversing the map on every loop iteration
        FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

        while (CheckCurrentState(RUNNING))
        {
            FairMQMessage* msg = fTransportFactory->CreateMessage();

            if (dataInChannel.Receive(msg) > 0)
            {
                receivedMsgs++;
                string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
                istringstream ibuffer(msgStr);
                TPayloadIn InputArchive(ibuffer);

                try
                {
                    InputArchive >> fHitVector;
                }
                catch (boost::archive::archive_exception& e)
                {
                    LOG(ERROR) << e.what();
                }

                int numInput = fHitVector.size();
                fOutput->Delete();

                for (Int_t i = 0; i < numInput; ++i)
                {
                    new ((*fOutput)[i]) TIn(fHitVector.at(i));
                }

                if (fOutput->IsEmpty())
                {
                    LOG(ERROR) << "FairMQFileSink::Run(): No Output array!";
                }

                fTree->Fill();
            }

            delete msg;

            if (fHitVector.size() > 0)
                fHitVector.clear();
        }

        LOG(INFO) << "I've received " << receivedMsgs << " messages!";
    }
    else
    {
        LOG(ERROR) << " Boost Serialization not ok";
    }
}

// ----- Implementation of FairMQFileSink::Run() with pure binary transport data format -----

template <>
void FairMQFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>::Run()
{
    int receivedMsgs = 0;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

    while (CheckCurrentState(RUNNING))
    {
        FairMQMessage* msg = fTransportFactory->CreateMessage();

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;
            Int_t inputSize = msg->GetSize();
            Int_t numInput = inputSize / sizeof(TestDetectorPayload::Hit);
            TestDetectorPayload::Hit* input = static_cast<TestDetectorPayload::Hit*>(msg->GetData());

            fOutput->Delete();

            for (Int_t i = 0; i < numInput; ++i)
            {
                TVector3 pos(input[i].posX, input[i].posY, input[i].posZ);
                TVector3 dpos(input[i].dposX, input[i].dposY, input[i].dposZ);
                new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairMQFileSink::Run(): No Output array!";
            }

            fTree->Fill();
        }

        delete msg;
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}

// ----- Implementation of FairMQFileSink::Run() with Root TMessage transport data format -----

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

template <>
void FairMQFileSink<FairTestDetectorHit, TMessage>::Run()
{
    int receivedMsgs = 0;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

    while (CheckCurrentState(RUNNING))
    {
        FairMQMessage* msg = fTransportFactory->CreateMessage();

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;
            TestDetectorTMessage tm(msg->GetData(), msg->GetSize());

            fOutput = (TClonesArray*)(tm.ReadObject(tm.GetClass()));

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairMQFileSink::Run(): No Output array!";
            }

            fTree->Fill();

            delete fOutput;
        }

        delete msg;
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}

// ----- Implementation of FairMQFileSink::Run() with Google Protocol Buffers transport data format -----

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"

template <>
void FairMQFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>::Run()
{
    int receivedMsgs = 0;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);

    while (CheckCurrentState(RUNNING))
    {
        FairMQMessage* msg = fTransportFactory->CreateMessage();

        if (dataInChannel.Receive(msg) > 0)
        {
            receivedMsgs++;
            fOutput->Delete();

            TestDetectorProto::HitPayload hp;
            hp.ParseFromArray(msg->GetData(), msg->GetSize());

            int numEntries = hp.hit_size();

            for (int i = 0; i < numEntries; ++i)
            {
                const TestDetectorProto::Hit& hit = hp.hit(i);
                TVector3 pos(hit.posx(), hit.posy(), hit.posz());
                TVector3 dpos(hit.dposx(), hit.dposy(), hit.dposz());
                new ((*fOutput)[i]) FairTestDetectorHit(hit.detid(), hit.mcindex(), pos, dpos);
            }

            if (fOutput->IsEmpty())
            {
                LOG(ERROR) << "FairMQFileSink::Run(): No Output array!";
            }

            fTree->Fill();
        }

        delete msg;
    }

    LOG(INFO) << "I've received " << receivedMsgs << " messages!";
}

#endif /* PROTOBUF */
