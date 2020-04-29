/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2POINT_H
#define FAIRTUTORIALDET2POINT_H 1

#include "FairMCPoint.h"

#include <Rtypes.h>
#include <TVector3.h>

class FairTutorialDet2Point : public FairMCPoint
{
  public:
    /** Default constructor **/
    FairTutorialDet2Point();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Coordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDet2Point(Int_t trackID,
                          Int_t detID,
                          TVector3 pos,
                          TVector3 mom,
                          Double_t tof,
                          Double_t length,
                          Double_t eLoss);

    /** Copy constructor **/
    // FairTutorialDet2Point(const FairTutorialDet2Point& point) { *this = point; };

    /** Destructor **/
    virtual ~FairTutorialDet2Point() {}

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

    ClassDef(FairTutorialDet2Point, 1);
};

// a custom class holding some data
// mainly to demonstrate that we don't need TObject inheritance
class CustomClass
{
  public:
    CustomClass() {}
    CustomClass(double x, int q)
        : fX(x)
        , fQ(q)
    {}
    double GetX() const { return fX; }
    int GetQ() const { return fQ; }

  private:
    double fX = 0.;   // x position
    int fQ = 0;       // charge
    ClassDefNV(CustomClass, 1);
};

#endif
