/* 
 * File:   runPolicyExample.cxx
 * Author: winckler
 *
 * Created on October 22, 2014, 6:39 PM
 */

// std
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <type_traits>

// boost
#include <boost/serialization/access.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

// ROOT
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"

#include "MyHit.h"
#include "MyPodData.h"

#include "DataTypeInfo.h"
#include "RootOutFileManager.h"
#include "BinaryOutFileManager.h"
#include "TriviallyCopyableDataSaver.h"
#include "BoostDataSaver.h"


/// /////////////////////////////////////////////////////////////////////////////////////////////
/// Use example of 3 OutputPolicy that can be used to store data in the GenericFileSink.
/// a) 1 OutputPolicy is dedicated to root file storage -> RootOutFileManager<TPayload>
/// b) The 2 others OutputPolicy are build from BinaryOutFileManager<TPayload,StoragePolicy>
///     BinaryOutFileManager is itself a policy based design class that uses StoragePolicy
///     plug the type of method (Policy) you want to use to save (or read) data.
///     At the moment 2 StoragePolicy are available for BinaryOutFileManager OutputPolicy, namely :
///         1) TriviallyCopyableDataSaver<TPayload> alias HandStorage -> can store data if they are POD or Trivially copyable
///         2) BoostDataSaver<TPayload>  alias BoostStorage -> can store data if they are boost serializable
/// /////////////////////////////////////////////////////////////////////////////////////////////

// redefine some types
typedef boost::archive::binary_iarchive         TBoostIn;
typedef boost::archive::binary_oarchive         TBoostOut;
typedef MyPodData::Digi                         TPayload;
typedef std::vector<TPayload>                   DataArray;
typedef std::vector<DataArray>                  ArrayContainer;
typedef TriviallyCopyableDataSaver<TPayload>    HandStorage;
typedef BoostDataSaver<TPayload>                BoostStorage;

// function declaration
template <typename Method, typename... Args>      void ReadFile(const std::string &filename, Args&... args);
template <typename TOutManager, typename... Args> void SaveFile(const std::string &filename,TPayload* ObjArray, int size, Args&... args);
void FillData(TPayload* objArray, const int & SIZE, bool print=true);


int main(int argc, char** argv) 
{
    
    
    // check type of data we want to serialize
    DataTypeInfo<MyPodData::TimeStamp>("MyPodData::TimeStamp");
    DataTypeInfo<MyPodData::Digi>("MyPodData::Digi");
    DataTypeInfo<MyPodData::Hit>("MyPodData::Hit");
    
    
    // create an array of object
    int SIZE=3;
    TPayload* ObjArray = new TPayload[SIZE];
    
    // Fill data with dummy numbers
    FillData(ObjArray,SIZE);
    
    
    /////////////////////////////////////////
    // SAVE AND READ FILES WITH HAND METHOD
    MQLOG(INFO)<<"***** Hand method *****";
    std::string filenameBinHand("myHandFile.dat");
    
    typedef BinaryOutFileManager<TPayload,HandStorage> TOutHandManager;
    SaveFile<TOutHandManager>(filenameBinHand,ObjArray,SIZE);
    ReadFile<TOutHandManager>(filenameBinHand);
    MQLOG(INFO)<<"";
    
    /////////////////////////////////////////
    // SAVE AND READ FILES WITH BOOST METHOD
    MQLOG(INFO)<<"***** Boost method *****";
    std::string filenameBinBoost("myBoostFile.dat");
    
    typedef BinaryOutFileManager<TPayload,BoostStorage> TOutBoostManager;
    SaveFile<TOutBoostManager>(filenameBinBoost,ObjArray,SIZE);
    ReadFile<TOutBoostManager>(filenameBinBoost);
    MQLOG(INFO)<<"";
    
    /////////////////////////////////////////
    // SAVE AND READ FILES WITH ROOT METHOD
    MQLOG(INFO)<<"***** ROOT method *****";
    // define parameters specific to root files (stored objects must be define in linkdef)
    std::string filenameRoot("myRootFile.root");
    std::string treename("MyTree");
    std::string branchname("MyBranch");
    std::string classname("MyPodData::Digi");
    std::string fileoption("UPDATE");
    bool useTClonesArray=false;
    
    typedef RootOutFileManager<TPayload> TOutRootManager;
    // use variadic template to plug more parameters in template function
    SaveFile<TOutRootManager>(filenameRoot,ObjArray,SIZE,treename,branchname,classname,fileoption,useTClonesArray);
    ReadFile<TOutRootManager>(filenameRoot,treename,branchname);
    MQLOG(INFO)<<"";
    // */
    return 0;
}


template <typename TOutManager, typename... Args>
void SaveFile(const std::string &filename,TPayload* ObjArray, int size, Args&... args)
{
    MQLOG(INFO)<<"---- WRITE TO FILE"<< filename <<"----";

    TOutManager* OuputMan = new TOutManager();
    OuputMan->SetFileProperties(filename,std::forward<Args>(args)...);
    OuputMan->InitOutFile();
    OuputMan->AddToFile(ObjArray,size);
    delete OuputMan;
}


template <typename TOutManager, typename... Args>
void ReadFile(const std::string &filename, Args&... args)
{
    MQLOG(INFO)<<"---- READ FROM FILE"<< filename <<"----";
    TOutManager OuputMan;
    ArrayContainer mycontainer=OuputMan.GetAllObj(filename, std::forward<Args>(args)...);
    int index=1;
    for(auto& p : mycontainer)
    {
        MQLOG(INFO)<<"The array nr "<< index <<" has "<<p.size()<<" objects.";
        int index2=1;
        for(auto& q : p)
        {
            MQLOG(INFO)<<"Object nr"<< index2;
            MQLOG(INFO)<<"fTimeStamp : "<<q.fTimeStamp;
            MQLOG(INFO)<<"fTimeStampError : "<<q.fTimeStampError;
            MQLOG(INFO)<<"fX : "<<q.fX;
            MQLOG(INFO)<<"fY : "<<q.fY;
            MQLOG(INFO)<<"fZ : "<<q.fZ;
            index2++;
        }
        index++;
    }
}


void FillData(TPayload* ObjArray, const int & SIZE, bool print)
{
    for(int i(0);i<SIZE;i++)
    {
        ObjArray[i].fTimeStamp=(double)(i+1);
        ObjArray[i].fTimeStampError=(double)(i+1);
        ObjArray[i].fX=(double)(i+1);
        ObjArray[i].fY=(double)(i+1);
        ObjArray[i].fZ=(double)(i+1);
    }
    
    if(print)
    {
        MQLOG(INFO)<<"---- Fill Payload ----";
        for(int i(0);i<SIZE;i++)
        {
            MQLOG(INFO)<<"i="<<i<<" fTimeStamp="<<ObjArray[i].fTimeStamp;
            MQLOG(INFO)<<"i="<<i<<" fTimeStampError="<<ObjArray[i].fTimeStampError;
            MQLOG(INFO)<<"i="<<i<<" fX="<<ObjArray[i].fX;
            MQLOG(INFO)<<"i="<<i<<" fY="<<ObjArray[i].fY;
            MQLOG(INFO)<<"i="<<i<<" fZ="<<ObjArray[i].fZ;
        }
    }
}


//*/



