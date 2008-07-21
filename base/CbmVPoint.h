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
class CbmVPoint : public TPolyMarker3D {
public:
  CbmVPoint();
  CbmVPoint(const CbmVPoint& pts);
  CbmVPoint(Int_t nhits);
  virtual ~CbmVPoint();
  void SetTrack(TGeoTrack *Tr){fTrack=Tr;}
  virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py);
  virtual void          ExecuteEvent(Int_t event, Int_t px, Int_t py); 
  TParticle             *GetParticle() const;
  virtual const         Text_t *GetName() const;
  virtual void          InspectParticle() const; // *MENU*
  virtual void          DumpParticle() const; // *MENU*
  virtual Text_t       *GetObjectInfo(Int_t px, Int_t py) const;
  CbmVPoint &           operator=(const CbmVPoint &pts)
    {pts.Copy(*this); return (*this);}
  virtual void          SetParticle(TParticle *p) {fParticle = p;}
  
protected:
  void Copy(TObject &pts) const;
  TGeoTrack	    *fTrack;
  TParticle 	*fParticle;
  Int_t         fIndex;      

  ClassDef(CbmVPoint,1) //Class to draw detector hits (is PolyMarker3D)
};
#endif


