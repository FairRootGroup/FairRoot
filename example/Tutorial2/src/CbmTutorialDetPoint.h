#ifndef CBMTUTORIALDETPOINT_H
#define CBMTUTORIALDETPOINT_H 1


#include "CbmMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class CbmTutorialDetPoint : public CbmMCPoint
{

 public:

  /** Default constructor **/
  CbmTutorialDetPoint();


  /** Constructor with arguments
   *@param trackID  Index of MCTrack
   *@param detID    Detector ID
   *@param pos      Ccoordinates at entrance to active volume [cm]
   *@param mom      Momentum of track at entrance [GeV]
   *@param tof      Time since event start [ns]
   *@param length   Track length since creation [cm]
   *@param eLoss    Energy deposit [GeV]
   **/
  CbmTutorialDetPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
		      Double_t tof, Double_t length, Double_t eLoss);


  /** Copy constructor **/
  CbmTutorialDetPoint(const CbmTutorialDetPoint& point) { *this = point; };


  /** Destructor **/
  virtual ~CbmTutorialDetPoint();

  /** Output to screen **/
  virtual void Print(const Option_t* opt) const;


  ClassDef(CbmTutorialDetPoint,1)

};

#endif
