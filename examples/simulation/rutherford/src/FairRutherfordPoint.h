/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDPOINT_H
#define CBMRUTHERFORDPOINT_H 1

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, Double32_t, etc
#include "TVector3.h"                   // for TVector3

class FairRutherfordPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairRutherfordPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairRutherfordPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                        Double_t tof, Double_t length, Double_t eLoss,
                        Double_t radius, Double_t phi, Double_t theta);




    /** Destructor **/
    virtual ~FairRutherfordPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:

    Double32_t fRadius, fPhi, fTheta;

    /** Copy constructor **/
    FairRutherfordPoint(const FairRutherfordPoint& point);
    FairRutherfordPoint operator=(const FairRutherfordPoint& point);

    ClassDef(FairRutherfordPoint,1)

};

#endif
