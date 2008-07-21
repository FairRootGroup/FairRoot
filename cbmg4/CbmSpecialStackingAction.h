// $Id: CbmSpecialStackingAction.h,v 1.1.1.1 2005/06/23 07:14:09 dbertini Exp $
// Category: event
//
//
// Class TG4SpecialStackingAction
// ------------------------------
// Class that defines a special stacking mechanism,
// with which particles are popped from the stack in "families".
// The primary particles are first reclassified into
// the postpone stack, a new primary is transfered to the urgent 
// stack only after all secondaries of its precedent primary
// are tracked.
// The secondary particles are classified into the waiting stack,
// which is transfered to the urgent stack when the urgent stack
// is empty. 
// This ensures that all daughters of any particle are tracked
// subsequently and get successive track IDs:
// n, n+1, n+2, n+3, ..., n+m  

#ifndef Cbm_STACKING_ACTION_H
#define Cbm_STACKING_ACTION_H

#include "TG4Verbose.h"

#include "G4UserStackingAction.hh"
#include "globals.hh"

class TG4TrackingAction;
class G4Track;
class G4TrackStack;

class CbmSpecialStackingAction : public G4UserStackingAction,
                                 public TG4Verbose
{
  public:
    CbmSpecialStackingAction();
    // --> protected
    // CbmSpecialStackingAction(const CbmSpecialStackingAction& right);
    virtual ~CbmSpecialStackingAction();

    // methods
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* track);
    void NewStage();
    void PrepareNewEvent();

  protected:
    CbmSpecialStackingAction(const CbmSpecialStackingAction& right);

    // operators
    CbmSpecialStackingAction& operator=(const CbmSpecialStackingAction& right);

  private:
    // data members
    G4int               fStage;          //stage number
    TG4TrackingAction*  fTrackingAction; //the tracking action
};

#endif //Cbm_STACKING_ACTION_H

