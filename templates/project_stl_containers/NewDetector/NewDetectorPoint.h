/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef NEWDETECTORPOINT_H
#define NEWDETECTORPOINT_H 1

#include <TVector3.h>

class NewDetectorPoint
{

  public:
    /** Default constructor **/
    NewDetectorPoint();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    NewDetectorPoint(Int_t trackID,
                     Int_t detID,
                     TVector3 pos,
                     TVector3 mom,
                     Double_t tof,
                     Double_t length,
                     Double_t eLoss);

    /** Destructor **/
    virtual ~NewDetectorPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

    /** Accessors */
    int GetTrackID() const { return fTrackID; }
    double GetPx() const { return fPx; }
    double GetPy() const { return fPy; }
    double GetPz() const { return fPz; }
    double GetTime() const { return fTime; }
    double GetLength() const { return fLength; }
    double GetEnergyLoss() const { return fELoss; }
    void Momentum(TVector3& mom) const { mom.SetXYZ(fPx, fPy, fPz); }
    int GetDetectorID() const { return fDetectorID; };
    double GetX() const { return fX; };
    double GetY() const { return fY; };
    double GetZ() const { return fZ; };
    void Position(TVector3& pos) const { pos.SetXYZ(fX, fY, fZ); }

    /** Modifiers **/
    virtual void SetTrackID(int id) { fTrackID = id; }
    void SetTime(double time) { fTime = time; }
    void SetLength(double length) { fLength = length; }
    void SetEnergyLoss(double eLoss) { fELoss = eLoss; }
    void SetMomentum(const TVector3& mom);
    void SetDetectorID(int detID) { fDetectorID = detID; }
    void SetX(double x) { fX = x; }
    void SetY(double y) { fY = y; }
    void SetZ(double z) { fZ = z; }
    void SetXYZ(double x, double y, double z);
    void SetPosition(const TVector3& pos);

  protected:
    int fTrackID;           ///< Track index
    double fPx, fPy, fPz;   ///< Momentum components [GeV]
    double fTime;           ///< Time since event start [ns]
    double fLength;         ///< Track length since creation [cm]
    double fELoss;          ///< Energy loss at this point [GeV]
    int fDetectorID;        ///< Detector unique identifier
    double fX, fY, fZ;      ///< Position of hit [cm]

  private:
    /** Copy constructor **/
    NewDetectorPoint(const NewDetectorPoint& point);
    NewDetectorPoint operator=(const NewDetectorPoint& point);

    ClassDef(NewDetectorPoint, 1);
};

inline void NewDetectorPoint::SetMomentum(const TVector3& mom)
{
    fPx = mom.Px();
    fPy = mom.Py();
    fPz = mom.Pz();
}

inline void NewDetectorPoint::SetXYZ(Double_t x, Double_t y, Double_t z)
{
    fX = x;
    fY = y;
    fZ = z;
}

inline void NewDetectorPoint::SetPosition(const TVector3& pos)
{
    fX = pos.X();
    fY = pos.Y();
    fZ = pos.Z();
}

#endif
