/* 
 * File:   Tuto7Helper.h
 * Author: winckler
 *
 * Created on July 3, 2015, 2:56 PM
 */

#ifndef TUTO7HELPER_H
#define TUTO7HELPER_H

#include <type_traits>
#include <string>

///////////////////// HELPER functions to handle different API in the  runprocessor template function (c.f. runGenericDevices.h)

struct BoostProcessorPolicyFlag {};
struct BoostFileSinkPolicyFlag {};
struct NoSpecFlag {};

template<typename SpecializationFlag=NoSpecFlag>
struct PolicyInit
{
    template <typename T>
    void InputContainer(T& Device, const std::string& classname)
    {
        Device.InitInputContainer(classname);
    }

    template <typename T>
    void Task(T& Device, const std::string& classname)
    {
        Device.InitTask(classname);
    }
};

template<>
struct PolicyInit<BoostProcessorPolicyFlag>
{
    template<typename T>
    void InputContainer(T& Device, const std::string& classname) {}

    template <typename T>
    void Task(T& Device, const std::string& classname) {}
};

template<>
struct PolicyInit<BoostFileSinkPolicyFlag>
{
    template<typename T>
    void InputContainer(T& Device, const std::string& classname)
    {
        Device.InitInputContainer(classname.c_str());
    }
};

#endif /* TUTO7HELPER_H */
