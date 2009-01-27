/**
 * To draw hits (points) in openGL
 * @author M. Al-Turany
 * @version 0.1
 * @since 22.11.07
 */
#ifndef CBMVPOINT_H
#define CBMVPOINT_H
#include "TPolyMarker3D.h"
class TParticle;
class TGeoTrack;
class FairVPoint : public TPolyMarker3D {
public:
  FairVPoint();
  FairVPoint(const FairVPoint& pts);
  FairVPoint(Int_t nhits);
  virtual ~FairVPoint();
  void SetTrack(TGeoTrack *Tr){fTrack=Tr;}
  virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py);
  virtual void          ExecuteEvent(Int_t event, Int_t px, Int_t py); 
  TParticle             *GetParticle() const;
  virtual const         Text_t *GetName() const;
  virtual void          InspectParticle() const; // *MENU*
  virtual void          DumpParticle() const; // *MENU*
  virtual Text_t       *GetObjectInfo(Int_t px, Int_t py) const;
  FairVPoint &           operator=(const FairVPoint &pts)
    {pts.Copy(*this); return (*this);}
  virtual void          SetParticle(TParticle *p) {fParticle = p;}
  
protected:
  void Copy(TObject &pts) const;
  TGeoTrack	    *fTrack;
  TParticle 	*fParticle;
  Int_t         fIndex;      

  ClassDef(FairVPoint,1) //Class to draw detector hits (is PolyMarker3D)
};
#endif


