/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1POINT_H
#define FAIRTUTORIALDET1POINT_H 1

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, etc
#include "TVector3.h"                   // for TVector3

class FairTutorialDet1Point : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairTutorialDet1Point();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDet1Point(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                          Double_t tof, Double_t length, Double_t eLoss);


    /** Copy constructor **/
    //    FairTutorialDet1Point(const FairTutorialDet1Point& point) { *this = point; };


    /** Destructor **/
    virtual ~FairTutorialDet1Point();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    ClassDef(FairTutorialDet1Point,1)

};

#endif
