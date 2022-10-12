/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORPOINT_H_
#define FAIRTESTDETECTORPOINT_H_

#include "FairMCPoint.h"   // for FairMCPoint

#include <Rtypes.h>     // for Double_t, Double32_t, etc
#include <TVector3.h>   // for TVector3

class FairTestDetectorPoint : public FairMCPoint
{
  public:
    /** Default constructor **/
    FairTestDetectorPoint();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTestDetectorPoint(Int_t trackID,
                          Int_t detID,
                          TVector3 pos,
                          TVector3 mom,
                          TVector3 posOut,
                          TVector3 momOut,
                          Double_t tof,
                          Double_t length,
                          Double_t eLoss);

    /** Destructor **/
    ~FairTestDetectorPoint() override;

    /** Output to screen **/
    void Print(const Option_t* opt) const override;

    /** Accessors **/
    Double_t GetXIn() const { return fX; }
    Double_t GetYIn() const { return fY; }
    Double_t GetZIn() const { return fZ; }
    Double_t GetXOut() const { return fX_out; }
    Double_t GetYOut() const { return fY_out; }
    Double_t GetZOut() const { return fZ_out; }
    Double_t GetPxOut() const { return fPx_out; }
    Double_t GetPyOut() const { return fPy_out; }
    Double_t GetPzOut() const { return fPz_out; }
    Double_t GetPxIn() const { return fPx; }
    Double_t GetPyIn() const { return fPy; }
    Double_t GetPzIn() const { return fPz; }

    void PositionOut(TVector3& pos) const { pos.SetXYZ(fX_out, fY_out, fZ_out); }
    void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPx_out, fPy_out, fPz_out); }

  private:
    Double32_t fX_out;
    Double32_t fY_out;
    Double32_t fZ_out;
    Double32_t fPx_out;
    Double32_t fPy_out;
    Double32_t fPz_out;

    /** Copy constructor **/
    FairTestDetectorPoint(const FairTestDetectorPoint&);
    FairTestDetectorPoint operator=(const FairTestDetectorPoint&);

    ClassDefOverride(FairTestDetectorPoint, 2);
};

#endif /* FAIRTESTDETECTORPOINT_H_ */
