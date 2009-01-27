// --------------------------------------------------------------------------
// -----          Header for the FairTutorialDetDigitizer               ------
// -----              Created 06.06.08 by F.Uhlig                      ------
// --------------------------------------------------------------------------



#ifndef CBMTUTORIALDETDIGITIZER_H
#define CBMTUTORIALDETDIGITIZER_H


#include "FairTask.h"

#include "TVector3.h"

class TClonesArray;

class FairTutorialDetDigiPar;

    class FairTutorialDetDigitizer : public FairTask {
public:

    

    /** Default constructor **/
    FairTutorialDetDigitizer();

    /** Standard constructor **/
    FairTutorialDetDigitizer(const char *name, const char *title="CBM Task");

    /** Destructor **/
    virtual ~FairTutorialDetDigitizer();

    /** Initialisation **/
    virtual InitStatus ReInit();
    virtual InitStatus Init();
    virtual void SetParContainers();

    /** Executed task **/
    virtual void Exec(Option_t * option);

    /** Finish task **/
    virtual void Finish();

    void AddHit(TVector3 &posHit, TVector3 &posHitErr,
		Int_t TrackID, Int_t PlaneID, Int_t ref, Double_t ELoss,
		Double_t ELossTR, Double_t ELossdEdX);
    void Register();

private:

    TClonesArray *fTutorialDetPoints; //! Tutorial Det MC points
    //    TClonesArray *fDigiCollection; //! TRD hits
    //TClonesArray *fListStack;         //Tracks

    FairTutorialDetDigiPar *fDigiPar;

    //    Double_t fDx;               //!
    //Double_t fDy;               //!
    //Int_t fNHits;

    ClassDef(FairTutorialDetDigitizer,1)

    };
#endif //CBMTUTORIALDETDIGITIZER_H
