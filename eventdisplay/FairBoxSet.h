// -------------------------------------------------------------------------
// -----              FairBoxSet header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSet
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FAIRBOXSET_H
#define FAIRBOXSET_H


#include "TEveBoxSet.h"
#include "FairBoxSetDraw.h"


class FairBoxSet : public TEveBoxSet
{

  public:

    /** Standard constructor
       **/
    FairBoxSet(FairBoxSetDraw* drawer, const char* name = "FairBoxSet", const char* t = "");

    void SetTimeWindow(double time) {fDraw->SetTimeWindow(time);}
    double GetTimeWindow() {return fDraw->GetTimeWindow();}


    /** Destructor **/
    virtual ~FairBoxSet() {};



  protected:

  private:
    FairBoxSetDraw* fDraw;

    ClassDef(FairBoxSet,1);

};


#endif
