



#ifndef MQPOLICYDEF_H
#define MQPOLICYDEF_H

#include <memory>
#include <boost/version.hpp>
#if BOOST_VERSION < 105600
#include "fairroot_null_deleter.h"
typedef fairroot::null_deleter empty_deleter_t;
#else
#include <boost/core/null_deleter.hpp>
typedef boost::null_deleter empty_deleter_t;
#endif

// helper class to define types
namespace fairmq
{
    namespace policy
    {
        // flag to handle ptr, ref, val... types
        struct pointer_type{};
        struct reference_type{};
        struct value_type{};
        struct unique_ptr_type{};
        struct shared_ptr_type{};
        
        template<typename flag, typename T>
        struct select_type
        {
            typedef T data_type;
        };

        template<typename T>
        struct select_type<pointer_type,T>
        {
            typedef T* type;
        };

        template<typename T>
        struct select_type<reference_type,T>
        {
            typedef T& type;
        };

        template<typename T>
        struct select_type<value_type,T>
        {
            typedef T type;
        };

        template<typename T>
        struct select_type<unique_ptr_type,T>
        {
            typedef std::unique_ptr<T> type;
        };


        template<typename T>
        struct select_type<shared_ptr_type,T>
        {
            typedef std::shared_ptr<T> type;
        };

        ////////////////////////////////////////////

        template<typename T, typename flag_type>
        struct data_type_interface
        {
            //void Create()
            //typedef typename select_type<flag_type>::type data_type;
        };
        ////////////////////////////////////////////
        // allocator_type
        struct OpNewCreator
        {   
            template<typename T, typename... Args>
            static void Create_impl(T*& input, Args&&... args)
            {
                input = new T(std::forward<Args>(args)...);
            }
        };

        struct NullptrCreator
        {   
            template<typename T, typename... Args>
            static void Create_impl(T*& input, Args&&... args)
            {
                input=nullptr;
            }
        };
        struct EmptyCreator
        {
            template<typename... Args>
            static void Create_impl(Args&&... args)
            {}
        };

        template<typename Deleter>
        struct SmartPtrCreator
        {
            template<typename T, typename... Args>
            static void Create_impl(std::unique_ptr<T>& input, Args&&... args)
            {
                input=std::unique_ptr<T>(new T(std::forward<Args>(args)...),Deleter());
            }

            template<typename T, typename... Args>
            static void Create_impl(std::shared_ptr<T>& input, Args&&... args)
            {
                input=std::shared_ptr<T>(new T(std::forward<Args>(args)...),Deleter());
            }
        };

        struct SmartPtrCreator_default
        {
            template<typename T, typename... Args>
            static void Create_impl(std::unique_ptr<T>& input, Args&&... args)
            {
                input=std::unique_ptr<T>(new T(std::forward<Args>(args)...));
            }

            template<typename T, typename... Args>
            static void Create_impl(std::shared_ptr<T>& input, Args&&... args)
            {
                input=std::shared_ptr<T>(new T(std::forward<Args>(args)...));
            }
        };
        ////////////////////////////////////////////
        // initializer_type
        struct NullptrInitializer
        {   
            template<typename T, typename... Args>
            static void Initialize_impl(T*& input, Args&&... args)
            {
                input=nullptr;
            }
            template<typename T, typename... Args>
            static void Initialize_impl(std::unique_ptr<T>& input, Args&&... args)
            {
                input=nullptr;
            }
            template<typename T, typename... Args>
            static void Initialize_impl(std::shared_ptr<T>& input, Args&&... args)
            {
                input=nullptr;
            }

        };
        struct EmptyInitializer
        {   
            template<typename... Args>
            static void Initialize_impl(Args&&... args)
            {
            }
        };


        ////////////////////////////////////////////
        // deleter_type
        struct EmptyDeleter
        {
            template<typename... Args>
            static void Destroy_impl(Args&&... args)
            {
            }
        };

        struct RawPtrDeleter
        {
            template<typename T>
            static void Destroy_impl(T* input)
            {
                if(input)
                {
                    delete input;
                    input=nullptr;
                }
            }
        };
        

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Input policy factory
        template<   typename deserializer_type, 
                    typename data_type, 
                    typename flag_type,
                    typename allocator_type,
                    typename initializer_type,
                    typename deleter_type
                >
        class InputPolicyFactory : public deserializer_type
        {
        public:
            typedef deserializer_type deserialization_type;
            typedef typename select_type<flag_type,data_type>::type data_t;
            InputPolicyFactory() : deserializer_type() 
            {
                initializer_type::Initialize_impl(fInput);
            }            

            template<typename... Args>
            void Create(Args&&... args)
            {
                allocator_type::template Create_impl(fInput,std::forward<Args>(args)...);
            }

        protected:
            ~InputPolicyFactory() 
            {
                Destroy();
            }

            void Destroy()
            {
                deleter_type::template Destroy_impl(fInput);
                LOG(TRACE)<<"Destroy input policy";
            }
            
            data_t fInput;
        };


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Output policy factory
        template<   typename serializer_type, 
                    typename data_type, 
                    typename flag_type,
                    typename allocator_type,
                    typename initializer_type,
                    typename deleter_type
                >
        class OutputPolicyFactory : public serializer_type
        {
        public:
            typedef serializer_type serialization_type;
            typedef typename select_type<flag_type,data_type>::type data_t;
            OutputPolicyFactory() : serializer_type() 
            {
                initializer_type::Initialize_impl(fOutput);
            }            

            template<typename... Args>
            void Create(Args&&... args)
            {
                allocator_type::template Create_impl(fOutput,std::forward<Args>(args)...);
            }

        protected:
            ~OutputPolicyFactory() 
            {
                Destroy();
            }

            void Destroy()
            {
                deleter_type::template Destroy_impl(fOutput);
                LOG(TRACE)<<"Destroy Output policy";
            }
            
            data_t fOutput;
        };

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // helper for data type handler
        template<   
                    typename T,
                    typename U,
                    typename V,
                    typename W
                >
        struct DataTypeHandler
        {
            typedef T flag_type;
            typedef U allocator_type;
            typedef V initializer_type;
            typedef W deleter_type;
        };
        


    }// end namespace policy
}// end namespace fairmq



///////////////////////////////////////////////////////////////////////////////////////////////////////////
// raw ptr default policy

//define type handler for convenience
typedef fairmq::policy::DataTypeHandler
                        <
                        fairmq::policy::pointer_type,
                        fairmq::policy::OpNewCreator,
                        fairmq::policy::NullptrInitializer,
                        fairmq::policy::RawPtrDeleter
                        > 
                        RawPtrDefaultPolicy;

// raw ptr data type : Default
template<typename deserializer_type, typename data_type>
using RawPtrDefaultInputPolicy = fairmq::policy::InputPolicyFactory
        <
        deserializer_type,
        data_type,
        RawPtrDefaultPolicy::flag_type,
        RawPtrDefaultPolicy::allocator_type,
        RawPtrDefaultPolicy::initializer_type,
        RawPtrDefaultPolicy::deleter_type
        >;

template<typename serializer_type, typename data_type>
using RawPtrDefaultOutputPolicy = fairmq::policy::OutputPolicyFactory
        <
        serializer_type,
        data_type,
        RawPtrDefaultPolicy::flag_type,
        RawPtrDefaultPolicy::allocator_type,
        RawPtrDefaultPolicy::initializer_type,
        RawPtrDefaultPolicy::deleter_type
        >;



///////////////////////////////////////////////////////////////////////////////////////////////////////////
// raw ptr no ownership policy
typedef fairmq::policy::DataTypeHandler
                        <
                        fairmq::policy::pointer_type,
                        fairmq::policy::EmptyCreator,
                        fairmq::policy::NullptrInitializer,
                        fairmq::policy::EmptyDeleter
                        > 
                        RawPtrNoOwnershipPolicy;

// raw ptr data type : Default
template<typename deserializer_type, typename data_type>
using RawPtrNoOwnershipInputPolicy = fairmq::policy::InputPolicyFactory
        <
        deserializer_type,
        data_type,
        RawPtrNoOwnershipPolicy::flag_type,
        RawPtrNoOwnershipPolicy::allocator_type,
        RawPtrNoOwnershipPolicy::initializer_type,
        RawPtrNoOwnershipPolicy::deleter_type
        >;

template<typename serializer_type, typename data_type>
using RawPtrNoOwnershipOutputPolicy = fairmq::policy::OutputPolicyFactory
        <
        serializer_type,
        data_type,
        RawPtrNoOwnershipPolicy::flag_type,
        RawPtrNoOwnershipPolicy::allocator_type,
        RawPtrNoOwnershipPolicy::initializer_type,
        RawPtrNoOwnershipPolicy::deleter_type
        >;




///////////////////////////////////////////////////////////////////////////////////////////////////////////
// below defines some template alias with default data nanagement types, e.g. for raw pointer and unique pointer
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// unique ptr data type : default


// unique_ptr default policy
typedef fairmq::policy::DataTypeHandler
                        <
                        fairmq::policy::unique_ptr_type,
                        fairmq::policy::SmartPtrCreator_default, // construction with default destructor
                        fairmq::policy::NullptrInitializer,
                        fairmq::policy::EmptyDeleter // does nothing and leave the work to the unique_ptr or shared_ptr internal default destructor (defined in constructor)
                        > 
                        UniquePtrDefaultPolicy;


template<typename deserializer_type, typename data_type>
using UniquePtrDefaultInputPolicy = fairmq::policy::InputPolicyFactory
        <
        deserializer_type,
        data_type,
        UniquePtrDefaultPolicy::flag_type,
        UniquePtrDefaultPolicy::allocator_type,
        UniquePtrDefaultPolicy::initializer_type,
        UniquePtrDefaultPolicy::deleter_type
        >;

template<typename serializer_type, typename data_type>
using UniquePtrDefaultOutputPolicy = fairmq::policy::OutputPolicyFactory
        <
        serializer_type,
        data_type,
        UniquePtrDefaultPolicy::flag_type,
        UniquePtrDefaultPolicy::allocator_type,
        UniquePtrDefaultPolicy::initializer_type,
        UniquePtrDefaultPolicy::deleter_type
        >;


#endif