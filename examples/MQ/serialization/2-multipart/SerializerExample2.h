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
    int EventNumber = 0;
    int DetectorId = 0;
};

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive& ar, Ex2Header& header, const unsigned int /*version*/)
{
    ar& header.EventNumber;
    ar& header.DetectorId;
}

} // namespace serialization
} // namespace boost

struct SerializerEx2
{
    void Serialize(FairMQMessage& msg, Ex2Header* header)
    {
        msg.Rebuild(header,
                    sizeof(header),
                    [](void* ptr, void* /*hint*/) { delete static_cast<Ex2Header*>(ptr); }
                    );
    }

    void Deserialize(FairMQMessage& msg, Ex2Header*& header)
    {
        header = static_cast<Ex2Header*>(msg.GetData());
    }
};

#endif
