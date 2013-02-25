/** FairMCEventHeader.h
 *@author V.Friese <v.friese@gsi.de>
 ** Data class (level MC) containing information about the input event.
 ** 15.05.2008 change the event time to ns (M. Al-Turany)
 **/


#ifndef FAIRMCEVENTHEADER_H
#define FAIRMCEVENTHEADER_H 1


#include "TNamed.h"
#include "TVector3.h"


class FairMCEventHeader : public TNamed
{

  public:

    /** Default constructor **/
    FairMCEventHeader();


    /** Constructor with all members
     **
     *@param iEvent   event identifier
     *@param x,y,z    vertex oordinates [cm]
     *@param t        event time [ns]
     *@param b        impact parameter [fm] (if relevant)
     *@param nPrim    number of input tracks
     **/
    FairMCEventHeader(Int_t iEvent, Double_t x, Double_t y, Double_t z,
                      Double_t t, Double_t b, Int_t nPrim);


    /** Standard constructor with run identifier **/
    FairMCEventHeader(UInt_t runId);


    /** Destructor **/
    virtual ~FairMCEventHeader();


    /** Accessors **/
    UInt_t GetRunID()   const { return fRunId; }     /// run identifier
    UInt_t GetEventID() const { return fEventId; }   /// event identifier
    Double_t GetX()     const { return fX; }         /// vertex x [cm]
    Double_t GetY()     const { return fY; }         /// vertex y [cm]
    Double_t GetZ()     const { return fZ; }         /// vertex z [cm]
    Double_t GetT()     const { return fT; }         /// event time [ns]
    Double_t GetB()     const { return fB; }         /// impact parameter [fm]
    Int_t GetNPrim()    const { return fNPrim; }     /// number of input tracks
    Bool_t IsSet()      const { return fIsSet; }     /// Flag

    void GetVertex(TVector3& vertex) { vertex.SetXYZ(fX, fY, fZ); }


    /** Modifiers **/
    void SetEventID(UInt_t eventId) { fEventId = eventId; }
    void SetRunID(UInt_t runId) { fRunId = runId; }
    void SetTime(Double_t t)       { fT = t; }
    void SetB(Double_t b)          { fB = b; }
    void SetNPrim(Int_t nPrim)     { fNPrim = nPrim; }
    void MarkSet(Bool_t isSet)     { fIsSet = isSet; }
    void SetVertex(Double_t x, Double_t y, Double_t z);
    void SetVertex(const TVector3& vertex);


    /** Reset all members **/
    void Reset();

    /** Register the class as data branch to the output */
    virtual void Register();

  protected:


    UInt_t     fRunId;       ///  Run identifier
    UInt_t     fEventId;     ///  Event identifier
    Double32_t fX;           ///  Primary vertex x [cm]
    Double32_t fY;           ///  Primary vertex y [cm]
    Double32_t fZ;           ///  Primary vertex z [cm]
    Double32_t fT;           ///  Event time [s]
    Double32_t fB;           ///  Impact parameter [fm] (if relevant)
    Int_t      fNPrim;       ///  Number of input tracks
    Bool_t     fIsSet;       ///  Flag whether variables are filled


    ClassDef(FairMCEventHeader,1);

};


inline void FairMCEventHeader::SetVertex(Double_t x, Double_t y,
    Double_t z)
{
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairMCEventHeader::SetVertex(const TVector3& vertex)
{
  fX = vertex.X();
  fY = vertex.Y();
  fZ = vertex.Z();
}


#endif
