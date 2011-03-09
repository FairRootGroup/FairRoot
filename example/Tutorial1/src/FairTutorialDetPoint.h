#ifndef FAIRTUTORIALDETPOINT_H
#define FAIRTUTORIALDETPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class FairTutorialDetPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairTutorialDetPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDetPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                         Double_t tof, Double_t length, Double_t eLoss);


    /** Copy constructor **/
    FairTutorialDetPoint(const FairTutorialDetPoint& point) { *this = point; };


    /** Destructor **/
    virtual ~FairTutorialDetPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    ClassDef(FairTutorialDetPoint,1)

};

#endif
