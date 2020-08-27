/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPPOINT_H
#define FAIRTUTPROPPOINT_H 1

#include "FairMCPoint.h"

class TVector3;

class FairTutPropPoint : public FairMCPoint
{

  public:
    /** Default constructor **/
    FairTutPropPoint();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutPropPoint(Int_t trackID,
                     Int_t detID,
                     TVector3 pos,
                     TVector3 mom,
                     Double_t tof,
                     Double_t length,
                     Double_t eLoss);

    /** Destructor **/
    virtual ~FairTutPropPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    /** Copy constructor **/
    FairTutPropPoint(const FairTutPropPoint& point);
    FairTutPropPoint operator=(const FairTutPropPoint& point);

    ClassDef(FairTutPropPoint, 1);
};

#endif   // FAIRTUTPROPPOINT_H
