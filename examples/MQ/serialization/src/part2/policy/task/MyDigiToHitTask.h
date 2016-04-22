
#ifndef MYDIGITOHITTASK_H
#define MYDIGITOHITTASK_H

// std
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// root
#include "Rtypes.h"
#include "TMath.h"
#include "TClonesArray.h"

// FairRoot
#include "TVector3.h"

// FairRoot - Tutorial7
#include "FairHit.h"
#include "MyDigi.h"
#include "MyHit.h"



class MyDigiToHitTask 
{

 public:

	/** Default constructor **/
	MyDigiToHitTask(){}

	/** Destructor **/
	virtual ~MyDigiToHitTask(){}

	// MQ
	void Exec(TClonesArray* digis, TClonesArray* hits)
	{
		hits->Delete();
	    for(unsigned int idigi(0);idigi<digis->GetEntriesFast();idigi++)
	    {
	        TVector3 pos;
	        TVector3 dpos;
	        Double_t timestamp=0;
	        Double_t timestampErr=0;

	        MyDigi* digi = static_cast<MyDigi*>(digis->At(idigi));
	        ProcessDigi(*digi, pos, dpos, timestamp, timestampErr);

	        MyHit* hit = new ((*hits)[idigi]) MyHit(fDetID, fMCIndex, pos, dpos);
	        hit->SetTimeStamp(digi->GetTimeStamp());
	        hit->SetTimeStampError(digi->GetTimeStampError());
	    }
	}

	void Exec(const std::unique_ptr<TClonesArray>& digis, std::unique_ptr<TClonesArray>& hits)
	{
		hits->Delete();
		TClonesArray* temp = hits.release();
	    for(unsigned int idigi(0);idigi<digis->GetEntriesFast();idigi++)
	    {
	        TVector3 pos;
	        TVector3 dpos;
	        Double_t timestamp=0;
	        Double_t timestampErr=0;

	        MyDigi* digi = static_cast<MyDigi*>(digis->At(idigi));
	        ProcessDigi(*digi, pos, dpos, timestamp, timestampErr);

	        MyHit* hit = new ((*temp)[idigi]) MyHit(fDetID, fMCIndex, pos, dpos);
	        hit->SetTimeStamp(digi->GetTimeStamp());
	        hit->SetTimeStampError(digi->GetTimeStampError());
	    }
	    hits.reset(temp);
	}


    void ProcessDigi(const MyDigi &Digi, TVector3 &pos, TVector3 &dpos, Double_t &t, Double_t &t_err)
    {
        pos.SetXYZ(Digi.GetX() + 0.5, Digi.GetY() + 0.5, Digi.GetZ() + 0.5);
        dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
        t = Digi.GetTimeStamp();
        t_err = Digi.GetTimeStampError();
    }

private:
	Int_t fDetID=0;
    Int_t fMCIndex=0;
  //void Init(PixelDigiPar* digipar, FairGeoParSet* geopar); 



};



#endif