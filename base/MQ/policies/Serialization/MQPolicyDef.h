#ifndef MQPOLICYDEF_H
#define MQPOLICYDEF_H

#include <memory>

namespace fair
{
namespace mq
{
namespace policy
{

// PassTypes
struct PointerType {};
struct ReferenceType {};
struct ValueType {};
struct UniquePtrType {};
struct SharedPtrType {};

// PassType
template<typename flag, typename T>
struct SelectPassType;

// PassType
template<typename T>
struct SelectPassType<PointerType, T>
{
    using Type = T*;
};

// PassType
template<typename T>
struct SelectPassType<ReferenceType, T>
{
    using Type = T&;
};

// PassType
template<typename T>
struct SelectPassType<ValueType, T>
{
    using Type = T;
};

// PassType
template<typename T>
struct SelectPassType<UniquePtrType, T>
{
    using Type = std::unique_ptr<T>;
};

// PassType
template<typename T>
struct SelectPassType<SharedPtrType, T>
{
    using Type = std::shared_ptr<T>;
};


// AllocatorType
struct OpNewCreator
{
    template<typename T, typename... Args>
    static void CreateImpl(T*& input, Args&&... args)
    {
        input = new T(std::forward<Args>(args)...);
    }
};

// AllocatorType
struct NullptrCreator
{
    template<typename T, typename... Args>
    static void CreateImpl(T*& input, Args&&... args)
    {
        input = nullptr;
    }
};

// AllocatorType
struct EmptyCreator
{
    template<typename... Args>
    static void CreateImpl(Args&&... args)
    {}
};

// AllocatorType
template<typename Deleter>
struct SmartPtrCreator
{
    template<typename T, typename... Args>
    static void CreateImpl(std::unique_ptr<T>& input, Args&&... args)
    {
        input = std::unique_ptr<T>(new T(std::forward<Args>(args)...), Deleter());
    }

    template<typename T, typename... Args>
    static void CreateImpl(std::shared_ptr<T>& input, Args&&... args)
    {
        input = std::shared_ptr<T>(new T(std::forward<Args>(args)...), Deleter());
    }
};


// InitializerType
struct NullptrInitializer
{
    template<typename T, typename... Args>
    static void InitializeImpl(T*& input, Args&&... args)
    {
        input = nullptr;
    }
    template<typename T, typename... Args>
    static void InitializeImpl(std::unique_ptr<T>& input, Args&&... args)
    {
        input = nullptr;
    }
    template<typename T, typename... Args>
    static void InitializeImpl(std::shared_ptr<T>& input, Args&&... args)
    {
        input = nullptr;
    }
};

// InitializerType
struct EmptyInitializer
{
    template<typename... Args>
    static void InitializeImpl(Args&&... args)
    {}
};


// DeleterType
struct EmptyDeleter
{
    template<typename... Args>
    static void DestroyImpl(Args&&... args)
    {}
};

// DeleterType
struct RawPtrDeleter
{
    template<typename T>
    static void DestroyImpl(T* input)
    {
        delete input;
        input = nullptr;
    }
};

// Input Policy
template<typename Deserializer, typename Data, typename PassType, typename AllocatorType, typename InitializerType, typename DeleterType>
class InputPolicy : public Deserializer
{
  public:
    InputPolicy(const InputPolicy&) = delete;
    InputPolicy operator=(const InputPolicy&) = delete;

    using DeserializerType = Deserializer;
    using DataType = typename SelectPassType<PassType, Data>::Type;

    InputPolicy()
        : Deserializer()
        , fInput()
    {
        InitializerType::InitializeImpl(fInput);
    }

    template<typename... Args>
    void Create(Args&&... args)
    {
        AllocatorType::CreateImpl(fInput, std::forward<Args>(args)...);
    }

  protected:
    virtual ~InputPolicy() 
    {
        DeleterType::DestroyImpl(fInput);
    }

    DataType fInput;
};


// Output Policy
template<typename Serializer, typename Data, typename PassType, typename AllocatorType, typename InitializerType, typename DeleterType>
class OutputPolicy : public Serializer
{
  public:
    using SerializerType = Serializer;
    using DataType = typename SelectPassType<PassType, Data>::Type;

    OutputPolicy()
        : Serializer()
    {
        InitializerType::InitializeImpl(fOutput);
    }

    template<typename... Args>
    void Create(Args&&... args)
    {
        AllocatorType::CreateImpl(fOutput, std::forward<Args>(args)...);
    }

  protected:
    ~OutputPolicy()
    {
        DeleterType::DestroyImpl(fOutput);
    }

    DataType fOutput;
};

} // namespace policy
} // namespace mq
} // namespace fair

#endif // MQPOLICYDEF_H
