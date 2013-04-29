// --------------------------------------------------------------------------
// -----          Header for the FairTutorialDet2Digitizer               ------
// -----              Created 06.06.08 by F.Uhlig                      ------
// --------------------------------------------------------------------------



#ifndef FAIRTUTORIALDET2DIGITIZER_H
#define FAIRTUTORIALDET2DIGITIZER_H


#include "FairTask.h"

#include "TVector3.h"

class TClonesArray;

class FairTutorialDet2DigiPar;

class FairTutorialDet2Digitizer : public FairTask
{
  public:



    /** Default constructor **/
    FairTutorialDet2Digitizer();

    /** Standard constructor **/
    FairTutorialDet2Digitizer(const char* name, const char* title="FAIR Task");

    /** Destructor **/
    virtual ~FairTutorialDet2Digitizer();

    /** Initialisation **/
    virtual InitStatus ReInit();
    virtual InitStatus Init();
    virtual void SetParContainers();

    /** Executed task **/
    virtual void Exec(Option_t* option);

    /** Finish task **/
    virtual void Finish();

    /*
    void AddHit(TVector3& posHit, TVector3& posHitErr,
                Int_t TrackID, Int_t PlaneID, Int_t ref, Double_t ELoss,
                Double_t ELossTR, Double_t ELossdEdX);
    */
    void Register();

  private:

    TClonesArray* fTutorialDetPoints; //! Tutorial Det MC points
    //    TClonesArray *fDigiCollection; //! TRD hits
    //TClonesArray *fListStack;         //Tracks

    FairTutorialDet2DigiPar* fDigiPar;

    //    Double_t fDx;               //!
    //Double_t fDy;               //!
    //Int_t fNHits;

    FairTutorialDet2Digitizer(const FairTutorialDet2Digitizer&);
    FairTutorialDet2Digitizer& operator=(const FairTutorialDet2Digitizer&);

    ClassDef(FairTutorialDet2Digitizer,1)

};
#endif //FAIRTUTORIALDETDIGITIZER_H
