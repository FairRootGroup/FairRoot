

#ifndef BASICSERIALIZEREXAMPLE2_H
#define BASICSERIALIZEREXAMPLE2_H

#include <memory>
#include <string>
#include <sstream>

#include "TMessage.h"
#include "TClonesArray.h"
#include "MyHit.h"

#include "FairMQMessage.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>

struct Ex2Header
{
    int EventNumber=0;
    int DetectorId=0;
};


class FairTMessage : public TMessage
{
  public:
    FairTMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void *data, void *hint)
{
    delete (TMessage*)hint;
}

struct SerializerEx2
{

    void Serialize(FairMQMessage& msg, TClonesArray* input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input);
        msg.Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }

    void Deserialize(FairMQMessage& msg, Ex2Header*& header)
    {
        //Ex2Header* header_ptr = static_cast<Ex2Header*>(msg.GetData());
        //header.EventNumber = header_ptr->EventNumber;
        //header.DetectorId = header_ptr->DetectorId;
        header=static_cast<Ex2Header*>(msg.GetData());
    }
    
    void Deserialize(FairMQMessage& msg, TClonesArray*& output)
    {
        if(output) delete output;
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output = static_cast<TClonesArray*>(tm.ReadObject(tm.GetClass()));
    }

};


namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive & ar, Ex2Header& header, const unsigned int version)
        {
            ar & header.EventNumber;
            ar & header.DetectorId;
        }
    } // namespace serialization
} // namespace boost



struct SerializerEx2Boost
{
    typedef boost::archive::binary_iarchive         BoostBinArchIn;
    typedef boost::archive::binary_oarchive         BoostBinArchOut;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Header
    void Serialize(FairMQMessage& msg, const Ex2Header& header)
    {
        
        std::ostringstream buffer;
        BoostBinArchOut OutputArchive(buffer);
        OutputArchive << header;
        std::string* strMsg = new std::string(buffer.str());
        msg.Rebuild(const_cast<char*>(strMsg->c_str()), strMsg->length(), [](void* data, void* hint)
                    {
                        delete static_cast<std::string*>(hint);
                    }, strMsg);
    }

    void Deserialize(FairMQMessage& msg, Ex2Header& header)
    {
        
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        BoostBinArchIn InputArchive(buffer);
        InputArchive >> header;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // TClonesArray (Note : TClonesArray is converted to boost serializable object std::vector<T>
    

    void Serialize(FairMQMessage& msg, TClonesArray* input)
    {
        // first copy the data to a std::vector
        std::vector<MyHit> input_vector;
        for (Int_t i = 0; i < input->GetEntriesFast(); ++i)
        {
            MyHit* data = reinterpret_cast<MyHit*>(input->At(i));
            if (!data)
            {
                continue;
            }
            input_vector.push_back(*data);
        }
        Serialize(msg,input_vector);//serialize vector<MyHit>
    }

    void Deserialize(FairMQMessage& msg, TClonesArray* input)
    {
        std::vector<MyHit> input_vector;
        Deserialize(msg,input_vector);// deserialize msg into vector
        // fill TClonesArray from vector
        if (input)
        {
            input->Delete();
            for (unsigned int i = 0; i < input_vector.size(); ++i)
            {
                new ((*input)[i]) MyHit(input_vector.at(i));
            }
            if (input->IsEmpty())
            {
                LOG(DEBUG) << "BoostDeserializer::deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input): No Output array!";
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // vector<data>
    void Deserialize(FairMQMessage& msg, std::vector<MyHit>& input)
    {
        if (input.size() > 0)
        {
            input.clear();
        }
        std::string msgStr(static_cast<char*>(msg.GetData()), msg.GetSize());
        std::istringstream buffer(msgStr);
        BoostBinArchIn InputArchive(buffer);
        InputArchive >> input;
    }

    void Serialize(FairMQMessage& msg, const std::vector<MyHit>& DataVector)
    {
        std::ostringstream buffer;
        BoostBinArchOut OutputArchive(buffer);
        OutputArchive << DataVector;
        int size = buffer.str().length();
        msg.Rebuild(size);
        std::memcpy(msg.GetData(), buffer.str().c_str(), size);
    }
};

#endif


