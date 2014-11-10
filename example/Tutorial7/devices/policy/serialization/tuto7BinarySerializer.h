/* 
 * File:   tuto7BinarySerializer.h
 * Author: winckler
 *
 * Created on December 8, 2014, 2:15 PM
 */

#ifndef TUTO7BINARYSERIALIZER_H
#define	TUTO7BINARYSERIALIZER_H



// std
#include <vector>
#include <string>
#include <sstream>

// ROOT
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "TVector3.h"
#include "BinaryBaseClassSerializer.h"

template <typename PodData>
class tuto7BinarySerializer : public BinaryBaseClassSerializer<PodData>
{
public:
    
    tuto7BinarySerializer() : BinaryBaseClassSerializer<PodData>(), fContainer(nullptr) {;}
    ~tuto7BinarySerializer(){;}
    using BinaryBaseClassSerializer<PodData>::fMessage;
    void Init()
    {
        //InitContainer();
    }
    
    void InitContainer(const std::string &ClassName)
    {
        fContainer = new TClonesArray(ClassName.c_str());
    }
    
    void InitContainer(TClonesArray* array)
    {
        fContainer = array;
    }
    
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // serialize
    
    virtual FairMQMessage* message(TClonesArray* array)
    {
        DoSerialization(array);
        return fMessage;
    }
    
    virtual void DoSerialization(TClonesArray* array) = 0; 
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // deserialize
    
    virtual TClonesArray* message(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        return fContainer;
    }
    
    virtual void DoDeSerialization(FairMQMessage* msg) = 0;
    
protected:
    
    TClonesArray* fContainer;

};




#endif	/* TUTO7BINARYSERIALIZER_H */

