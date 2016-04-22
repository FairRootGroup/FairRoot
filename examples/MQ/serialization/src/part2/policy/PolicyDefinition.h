



#ifndef TUTO7_TYPE_DEFINITION_H
#define TUTO7_TYPE_DEFINITION_H


#include "MQPolicyDef.h"

class MyHit;
class MyDigi;
class TClonesArray;


#include "BoostSerializer.h"
#include "RootSerializer.h"

#include "MyDigiSerializer.h"
#include "MyHitSerializer.h"

#include "MyDigiSerializer_protobuff.h"
#include "MyHitSerializer_protobuff.h"



namespace fairroot{
namespace examples{


template<typename deserializer>
using RawPtrDefaultInputPolicy_t = RawPtrDefaultInputPolicy<deserializer,TClonesArray>;
template<typename serializer>
using RawPtrDefaultOutputPolicy_t = RawPtrDefaultOutputPolicy<serializer,TClonesArray>;

template<typename deserializer>
using UniquePtrDefaultInputPolicy_t = UniquePtrDefaultInputPolicy<deserializer,TClonesArray>;
template<typename serializer>
using UniquePtrDefaultOutputPolicy_t = UniquePtrDefaultOutputPolicy<serializer,TClonesArray>;


/////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////////
	// SAMPLER
	namespace sampler_policy
	{
		// ROOT /////////////////////////////////////////////////////////////////////
		namespace root
		{
			namespace r_ptr
			{
				//typedef RawPtrDefaultInputPolicy_t<RootDeserializer> input;
				typedef RawPtrNoOwnershipOutputPolicy<RootSerializer,TClonesArray> output;
			}
			namespace u_ptr
			{
				//typedef UniquePtrDefaultInputPolicy_t<RootDeserializer> input;
				typedef UniquePtrDefaultOutputPolicy_t<RootSerializer>  output;
			}
		}
		// BIN /////////////////////////////////////////////////////////////////////
		namespace binary
		{
			namespace r_ptr
			{
				//typedef RawPtrDefaultInputPolicy_t<MyDigiDeserializer_t> input;
				typedef RawPtrNoOwnershipOutputPolicy<MyDigiSerializer_t,TClonesArray>  output;
			}
			/*
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyDigiDeserializer_t> input;
				typedef UniquePtrDefaultOutputPolicy_t<MyHitSerializer_t>  output;
			}//*/
		}
		// Protocol Buffer /////////////////////////////////////////////////////////////////////
		namespace proto
		{
			namespace r_ptr
			{
				//typedef RawPtrDefaultInputPolicy_t<MyDigiProtoDeserializer> input;
				typedef RawPtrNoOwnershipOutputPolicy<MyDigiProtoSerializer,TClonesArray>  output;
			}
			/*namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyDigiProtoDeserializer> input;
				typedef UniquePtrDefaultOutputPolicy_t<MyHitProtoSerializer>  output;
			}//*/
		}
		// Boost /////////////////////////////////////////////////////////////////////
		namespace boost
		{
			namespace r_ptr
			{
				//typedef RawPtrDefaultInputPolicy_t<BoostDeSerializer<MyDigi>> input;
				typedef RawPtrNoOwnershipOutputPolicy<BoostSerializer<MyDigi>,TClonesArray>  output;
			}
			/*namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<BoostDeSerializer<MyDigi>> input;
				typedef UniquePtrDefaultOutputPolicy_t<BoostSerializer<MyHit>>  output;
			}*/
		}
	}// end namespace processor_policy

/////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////////
	// PROCESSOR
	namespace processor_policy
	{
		// ROOT /////////////////////////////////////////////////////////////////////
		namespace root
		{
			namespace r_ptr
			{
				typedef RawPtrNoOwnershipInputPolicy<RootDeserializer,TClonesArray> input;
				//typedef RawPtrDefaultInputPolicy_t<RootDeserializer> input;
				typedef RawPtrDefaultOutputPolicy_t<RootSerializer>  output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<RootDeserializer> input;
				typedef UniquePtrDefaultOutputPolicy_t<RootSerializer>  output;
			}
		}
		// BIN /////////////////////////////////////////////////////////////////////
		namespace binary
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<MyDigiDeserializer_t> input;
				typedef RawPtrDefaultOutputPolicy_t<MyHitSerializer_t> 	output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyDigiDeserializer_t> input;
				typedef UniquePtrDefaultOutputPolicy_t<MyHitSerializer_t>  output;
			}
		}
		// Protocol Buffer /////////////////////////////////////////////////////////////////////
		namespace proto
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<MyDigiProtoDeserializer> input;
				typedef RawPtrDefaultOutputPolicy_t<MyHitProtoSerializer>  output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyDigiProtoDeserializer> input;
				typedef UniquePtrDefaultOutputPolicy_t<MyHitProtoSerializer>  output;
			}
		}
		// Boost /////////////////////////////////////////////////////////////////////
		namespace boost
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<BoostDeSerializer<MyDigi>> input;
				typedef RawPtrDefaultOutputPolicy_t<BoostSerializer<MyHit>>  output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<BoostDeSerializer<MyDigi>> input;
				typedef UniquePtrDefaultOutputPolicy_t<BoostSerializer<MyHit>>  output;
			}
		}
	}// end namespace processor_policy

/////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////////
	// SINK
	namespace sink_policy
	{
		// ROOT /////////////////////////////////////////////////////////////////////
		namespace root
		{
			namespace r_ptr
			{
				typedef RawPtrNoOwnershipInputPolicy<RootDeserializer,TClonesArray> input;
				//typedef RawPtrDefaultInputPolicy_t<RootDeserializer> input;
				//typedef RawPtrDefaultOutputPolicy_t<RootSerializer>  output;
			}
			
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<RootDeserializer> input;
				//typedef UniquePtrDefaultOutputPolicy_t<RootSerializer>  output;
			}
		}
		// BIN /////////////////////////////////////////////////////////////////////
		namespace binary
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<MyHitDeserializer_t> input;
				//typedef RawPtrDefaultOutputPolicy_t<MyHitSerializer_t> 	output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyHitDeserializer_t> input;
				//typedef UniquePtrDefaultOutputPolicy_t<MyHitSerializer_t>  output;
			}
		}
		// Protocol Buffer /////////////////////////////////////////////////////////////////////
		namespace proto
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<MyHitProtoDeserializer> input;
				//typedef RawPtrDefaultOutputPolicy_t<MyHitProtoSerializer>  output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<MyHitProtoDeserializer> input;
				//typedef UniquePtrDefaultOutputPolicy_t<MyHitProtoSerializer>  output;
			}
		}
		// Boost /////////////////////////////////////////////////////////////////////
		namespace boost
		{
			namespace r_ptr
			{
				typedef RawPtrDefaultInputPolicy_t<BoostDeSerializer<MyHit>> input;
				//typedef RawPtrDefaultOutputPolicy_t<BoostSerializer<MyHit>>  output;
			}
			namespace u_ptr
			{
				typedef UniquePtrDefaultInputPolicy_t<BoostDeSerializer<MyHit>> input;
				//typedef UniquePtrDefaultOutputPolicy_t<BoostSerializer<MyHit>>  output;
			}
		}
	}// end namespace processor_policy

}// end namespace examples
}// end namespace fairroot


#endif