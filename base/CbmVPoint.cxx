#include "CbmVPoint.h"

#include "TPad.h"
#include "TParticle.h"
#include "TView.h"
#include "TGeoTrack.h"

#include <iostream>

using std::cout;
using std::endl;

ClassImp(CbmVPoint)

//_______________________________________________________________________
CbmVPoint::CbmVPoint():
  fTrack(0),
  fParticle(0),
  fIndex(0)
{
  //
  // Default constructor
  //
}

//_______________________________________________________________________
CbmVPoint::CbmVPoint(const CbmVPoint &pts):
  TPolyMarker3D(pts),
  fTrack(0),
  fParticle(0),
  fIndex(0)
{
  //
  // Copy constructor
  //
  pts.Copy(*this);
}

//_______________________________________________________________________
CbmVPoint::CbmVPoint(Int_t nhits):
  TPolyMarker3D(nhits),
  fTrack(0),
  fParticle(0),
  fIndex(0)
  
{
  //
  // Standard constructor
  //
  ResetBit(kCanDelete);
}
         
//_______________________________________________________________________
CbmVPoint::~CbmVPoint()
{
  //
  // Default destructor
  //
}

//_______________________________________________________________________
void CbmVPoint::Copy(TObject &pts) const
{
  //
  // Copy *this onto pts
  //
  if((TObject*)this != &pts) {
    ((TPolyMarker3D*)this)->Copy(dynamic_cast<TPolyMarker3D&>(pts));
    (dynamic_cast<CbmVPoint&>(pts)).fGLList = fGLList;
    (dynamic_cast<CbmVPoint&>(pts)).fLastPoint = fLastPoint;
    (dynamic_cast<CbmVPoint&>(pts)).fParticle = fParticle;
  }
}

//_______________________________________________________________________
Int_t CbmVPoint::DistancetoPrimitive(Int_t px, Int_t py)
{
  //
  //*-*-*-*-*-*-*Compute distance from point px,py to a 3-D polymarker*-*-*-*-*
  //*-*          =====================================================
  //*-*
  //*-*  Compute the closest distance of approach from point
  //*-*  px,py to each segment
  //*-*  of the polyline.
  //*-*  Returns when the distance found is below DistanceMaximum.
  //*-*  The distance is computed in pixels units.
  //*-*
  //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

  //const Int_t inaxis = 7;
  //Int_t dist = 9999;
  return TPolyMarker3D::DistancetoPrimitive(px,py);
}

//_______________________________________________________________________
void CbmVPoint::DumpParticle() const
{
  //
  //   Dump particle corresponding to this point
  //
  
  if (fParticle) fParticle->Dump();
}

//_______________________________________________________________________
void CbmVPoint::ExecuteEvent(Int_t event, Int_t px, Int_t py)
{
  //
  //*-*-*-*-*-*-*-*-*-*Execute action corresponding to one event*-*-*-*-*-*-*-*
  //*-*                =========================================
  //*-*
  //*-*  This member function must be implemented to realize the action
  //*-*  corresponding to the mouse click on the object in the window
  //*-*
  //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

   gPad->SetCursor(kCross);
/*  
  if (gPad->GetView())
    gPad->GetView()->ExecuteRotateView(event, px, py);
  */
  // cout << "CbmVPoint::ExecuteEvent" << event <<" " <<px <<" " <<  py<< endl;
    if (fParticle)fParticle->ExecuteEvent(event, px, py);
 

}

//_______________________________________________________________________
const Text_t *CbmVPoint::GetName() const
{
  //
  // Return name of the Geant3 particle corresponding to this point
  //

  if (!fParticle) return "Particle";
  return fParticle->GetName();
}
 
//_______________________________________________________________________
Text_t *CbmVPoint::GetObjectInfo(Int_t px, Int_t py) const
{
  //
  //   Redefines TObject::GetObjectInfo.
  //   Displays the info (particle,etc
  //   corresponding to cursor position px,py
  //
 // static char info[64];
 // sprintf(info,"%s %d",GetName(),fIndex);
  return fParticle->GetObjectInfo(px,py);
}

//_______________________________________________________________________
TParticle *CbmVPoint::GetParticle() const
{
  //
  //   Returns pointer to particle index in AliRun::fParticles
  //

    return fParticle;
}

//_______________________________________________________________________
void CbmVPoint::InspectParticle() const
{
  //
  //   Inspect particle corresponding to this point
  //
//  TParticle *particle = GetParticle();
  if (fParticle) fParticle->Inspect();

}







