/**
* To draw the tracks in openGL
* @author M. Al-Turany
* @version 0.1
* @since 22.11.07
*/

#ifndef FAIRVTRACK_H
#define FAIRVTRACK_H
#include "TPolyLine3D.h"
#include "TGeoTrack.h"

class TParticle;
class TGeoTrack;
class FairVTrack : public TPolyLine3D
{
  public:
    FairVTrack();
    FairVTrack(const FairVTrack& pts);
    FairVTrack(Int_t nhits);
    virtual ~FairVTrack();
    void SetTrack(TGeoTrack* Tr);
    virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py);
    virtual void          ExecuteEvent(Int_t event, Int_t px, Int_t py);
    Int_t                   GetIndex() const {return fIndex;}
    virtual const Text_t* GetName() const;
    virtual void          InspectParticle() const; // *MENU*
    virtual void          DumpParticle() const; // *MENU*
    virtual Text_t*       GetObjectInfo(Int_t px, Int_t py) const;
    virtual void          SetParticle(TParticle* p);
    TParticle*              GetParticle() const;
    FairVTrack&            operator=(const FairVTrack& pts)
    {pts.Copy(*this); return (*this);}
  protected:
    void Copy(TObject& pts) const;
    Int_t Color(Int_t pdg);
    TGeoTrack*   fTrack;
    Int_t          fIndex;
    TParticle*     fParticle;
    ClassDef(FairVTrack,1) //Class to  Tracks (Also in OpenGL viewer of ROOT)
};
#endif





