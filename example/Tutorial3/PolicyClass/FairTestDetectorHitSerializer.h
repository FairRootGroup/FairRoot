/* 
 * File:   FairTestDetectorHitSerializer.h
 * Author: winckler
 *
 * Created on October 14, 2014, 5:32 PM
 */


#ifndef FAIRTESTDETECTORHITSERIALIZER_H
#define	FAIRTESTDETECTORHITSERIALIZER_H

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
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"


typedef FairTestDetectorHit TDataClass;// non pod data
typedef TestDetectorPayload::Hit TPayload;// pod/trivially copyable data


class FairTestDetectorHitSerializer : public BinaryBaseClassSerializer<TPayload>
{
public:
    
    FairTestDetectorHitSerializer() : BinaryBaseClassSerializer<TPayload>(), fOutputContainer(NULL) {;}
    ~FairTestDetectorHitSerializer(){;}
    
    
    void InitTClonesArray(const std::string &ClassName)
    {
        fOutputContainer = new TClonesArray(ClassName.c_str());
    }
    
    
    TClonesArray* message(FairMQMessage* msg)
    {
        GetPointerToPayload(msg);
        
        if(fOutputContainer)
        {
            fOutputContainer->Delete();
            for (Int_t i = 0; i < fNumInput; ++i)
            {
                TVector3 pos(fPtrToPayload[i].posX, fPtrToPayload[i].posY, fPtrToPayload[i].posZ);
                TVector3 dpos(fPtrToPayload[i].dposX, fPtrToPayload[i].dposY, fPtrToPayload[i].dposZ);
                new ((*fOutputContainer)[i]) TDataClass(fPtrToPayload[i].detID, fPtrToPayload[i].mcindex, pos, dpos);
            }
            
            if (fOutputContainer->IsEmpty())
            {
                MQLOG(ERROR) << "FairTestDetectorHitSerializer::message(): No Output array!";
            }
        }
        return fOutputContainer;
    }
    
    
    
    
protected:
    
    TClonesArray* fOutputContainer;

};


#endif	/* FAIRTESTDETECTORHITSERIALIZER_H */

