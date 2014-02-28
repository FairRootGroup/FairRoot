#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include <iostream>
#include <sstream>
//#include <memory>
//#include <chrono>

#ifndef __CINT__ // Boost serialization 
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif //__CINT__

#include "TMath.h"
#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairMQLogger.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"

#include "FairTestDetectorRecoTask.h"
#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"




using std::cout;
using std::endl;


class TClonesArray;
template <typename TIn, typename TOut, typename TBoostIArchive, typename TBoostOArchive>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    /** Default constructor **/
    FairTestDetectorMQRecoTask(): fRecoTask(NULL){}
    FairTestDetectorMQRecoTask(Int_t verbose): fRecoTask(NULL){}


    /** Destructor **/
    virtual ~FairTestDetectorMQRecoTask()
    {
        fRecoTask->fDigiArray->Delete();
        fRecoTask->fHitArray->Delete();
        delete fRecoTask;
        if(fDigiVector.size()>0) fDigiVector.clear();
        if(fHitVector.size()>0) fHitVector.clear();
    }


    /** Virtual method Init **/
    virtual InitStatus Init()
    {
        fRecoTask = new FairTestDetectorRecoTask();
        fRecoTask->fDigiArray = new TClonesArray("FairTestDetectorDigi");
        fRecoTask->fHitArray = new TClonesArray("FairTestDetectorHit");

        return kSUCCESS;
    }


    /** Virtual method Exec **/
    virtual void Exec(FairMQMessage* msg, Option_t* opt);

  private:
    FairTestDetectorRecoTask* fRecoTask;
    #ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
    std:: vector<TIn >  fDigiVector;
    std:: vector<TOut>  fHitVector;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & fDigiVector;
        ar & fHitVector;
    }
    #endif // for BOOST serialization
};


////////// Template implementation of exec in FairTestDetectorMQRecoTask.tpl :
#include "FairTestDetectorMQRecoTask.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */
