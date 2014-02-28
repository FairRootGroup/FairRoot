/**
 * File:   TestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef TESTDETECTORDIGILOADER_H
#define	TESTDETECTORDIGILOADER_H

#include "FairMQSamplerTask.h"

#include "FairMQLogger.h"
#include <boost/timer/timer.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "FairTestDetectorPayload.h"
#include <iostream> 

////////// Base template header <T1,T2>
template <typename T1, typename T2>//=boost::archive::text_oarchive>
class TestDetectorDigiLoader : public FairMQSamplerTask
{ 
public : 
 
    TestDetectorDigiLoader() : FairMQSamplerTask("Load Digi class T1") {}
    virtual ~TestDetectorDigiLoader()
    {
        if(fDigiVector.size()>0) fDigiVector.clear();
    }
    virtual void Exec(Option_t* opt);
    
private :
        
    friend class boost::serialization::access;
    std::vector<T1> fDigiVector;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & fDigiVector;
    }
    
}; 


////////// Partial specialisation header <T1,boost::archive::text_oarchive>
template <typename T1>
class TestDetectorDigiLoader<T1, boost::archive::text_oarchive> : public FairMQSamplerTask
{ 
public : 
 
    TestDetectorDigiLoader() : FairMQSamplerTask("Load Digi class T1") {}
    virtual ~TestDetectorDigiLoader()
    {
        fDigiVector.clear();
    }
    virtual void Exec(Option_t* opt);
    
private :
        
    friend class boost::serialization::access;
    std:: vector<T1> fDigiVector;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & fDigiVector;
    }
    
}; 

////////// Template implementation is in TestDetectorDigiLoader.tpl :
#include "TestDetectorDigiLoader.tpl"

#endif /* TESTDETECTORDIGILOADER_H */

