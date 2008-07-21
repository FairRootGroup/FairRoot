#include "CbmVTrack.h"

#include "TPad.h"
#include "TParticle.h"
#include "TView.h"
#include "TGeoTrack.h"

#include <iostream>

using std::cout;
using std::endl;

ClassImp(CbmVTrack)

//_______________________________________________________________________
CbmVTrack::CbmVTrack():
  fTrack(0),
  fIndex(0),
  fParticle(0)
 
{
  //
  // Default constructor
  //
}

//_______________________________________________________________________
CbmVTrack::CbmVTrack(const CbmVTrack &pts):
  TPolyLine3D(pts),
  fTrack(0),
  fIndex(0),
  fParticle(0)                                     
{
  //
  // Copy constructor
  //
  pts.Copy(*this);
}

//_______________________________________________________________________
CbmVTrack::CbmVTrack(Int_t nhits):
    TPolyLine3D(nhits),
    fTrack(0),
	fIndex(0),
    fParticle(0)
   
{
  //
  // Standard constructor
  //
  ResetBit(kCanDelete);
}
         
//_______________________________________________________________________
CbmVTrack::~CbmVTrack()
{
  //
  // Default destructor
  //
}

//_______________________________________________________________________
void CbmVTrack::Copy(TObject &pts) const
{
  //
  // Copy *this onto pts
  //
  if((TObject*)this != &pts) {
    ((TPolyLine3D*)this)->Copy(dynamic_cast<TPolyLine3D&>(pts));
    (dynamic_cast<CbmVTrack&>(pts)).fGLList = fGLList;
    (dynamic_cast<CbmVTrack&>(pts)).fLastPoint = fLastPoint;
    (dynamic_cast<CbmVTrack&>(pts)).fIndex = fIndex;
    (dynamic_cast<CbmVTrack&>(pts)).fParticle = fParticle;
  }
}

//_______________________________________________________________________
Int_t CbmVTrack::DistancetoPrimitive(Int_t px, Int_t py)
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
  return TPolyLine3D::DistancetoPrimitive(px,py);
}
 
//_______________________________________________________________________
void CbmVTrack::DumpParticle() const
{
  //
  //   Dump particle corresponding to this point
  
   if (fParticle) fParticle->Dump();
   
}
 
//_______________________________________________________________________
void CbmVTrack::ExecuteEvent(Int_t event, Int_t px, Int_t py)
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
  // cout << "CbmVTrack::ExecuteEvent" << event <<" " <<px <<" " <<  py<< endl;
   fParticle->ExecuteEvent(event, px, py);
 

}

//_______________________________________________________________________
const Text_t *CbmVTrack::GetName() const
{
  //
  // Return name of the Geant3 particle corresponding to this point
  //

  if (!fParticle) return "Particle";
  return fParticle->GetName();
}
 
//_______________________________________________________________________
Text_t *CbmVTrack::GetObjectInfo(Int_t px, Int_t py) const
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
TParticle *CbmVTrack::GetParticle() const
{
  //
  //   Returns pointer to particle 
       return fParticle;
}

//_______________________________________________________________________
void CbmVTrack::InspectParticle() const
{
  //   Inspect particle corresponding to this track
  
  if (fParticle) fParticle->Inspect();

}
//_______________________________________________________________________

void CbmVTrack::SetParticle(TParticle *p)
 {
     fParticle = p;
     SetLineColor(Color(p->GetPdgCode()));    
 }
 //_______________________________________________________________________

 void CbmVTrack::SetTrack(TGeoTrack *Tr)
 {
     fTrack=Tr;
     SetLineColor(Color(Tr->GetPDG()));  
  }
//_______________________________________________________________________

Int_t CbmVTrack::Color(Int_t pdg) 
{
 switch(pdg) {

      case   22     : return  1;    // photon
      case   -2112  : return  2 ;   // anti-neutron
      case   -11    : return  3;    // e+
      case   -3122  : return  4;   // anti-Lambda
      case   11     : return  5;    // e-
      case   -3222  : return  6;   // Sigma-
      case   12     : return  7;    // e-neutrino (NB: flavour undefined by Geant)
      case   -3212  : return  8;   // Sigma0
      case   -13    : return  9;    // mu+
      case   -3112  : return  10;   // Sigma+ (PB)*/
      case   13     : return  11;    // mu-
      case   -3322  : return  12;   // Xi0
      case   111    : return  13;    // pi0
      case   -3312  : return  14;   // Xi+
      case   211    : return  15;    // pi+
      case   -3334  : return  16;   // Omega+ (PB)
      case   -211   : return  17;    // pi-
      case   -15    : return  18;   // tau+
      case   130    : return  19;   // K long
      case   15     : return  20;   // tau-
      case   321    : return  21;   // K+
      case   411    : return  22;   // D+
      case   -321   : return  23;   // K-
      case   -411   : return  24;   // D-
      case   2112   : return  25;   // n
      case   421    : return  26;   // D0
      case   2212   : return  27;   // p
      case   -421   : return  28;   // D0
      case   -2212  : return  29;   // anti-proton
      case   431    : return  30;   // Ds+
      case   310    : return  31;   // K short
      case   -431   : return  32;   // anti Ds-
      case   221    : return  33;   // eta
      case   4122   : return  34;   // Lamba_c+
      case   3122   : return  35;   // Lambda
      case   24     : return  36;   // W+
      case   3222   : return  37;   // Sigma+
      case   -24    : return  38;   // W-
      case   3212   : return  39;   // Sigma0
      case   23     : return  40;   // Z
      case   3112   : return  41;   // Sigma-
      case   3322   : return  42;   // Xi0
      case   3312   : return  43;   // Xi-
      case   3334   : return  44;   // Omega- (PB)
      case   50000050   : return  801;   // Cerenkov
      default  : return 0;

  }

}






                                                   




