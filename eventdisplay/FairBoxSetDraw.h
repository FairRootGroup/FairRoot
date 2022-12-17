/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----              FairBoxSetDraw header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------

/** FairBoxSetDraw
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an
 *input to place the points. If one wants to change the color of the points one has to overwrite the method GetValue.
 *This method takes a TObject and an integer and translates this into an integer as input for the EveBoxSet method
 *DigitValue
 **
 **/

#ifndef FAIRBOXSETDRAW_H
#define FAIRBOXSETDRAW_H

#include "FairDataSourceI.h"
#include "FairTSBufferFunctional.h"   // IWYU pragma: keep needed for cint
#include "FairTask.h"                 // for FairTask, InitStatus

#include <Rtypes.h>   // for Double_t, Int_t, Bool_t, etc

class FairBoxSet;
class FairEventManager;
class FairRootManager;
class TObject;
class TVector3;
class TClonesArray;

class FairBoxSetDraw : public FairTask
{
  public:
    /** Default constructor **/
    FairBoxSetDraw();

    /** Standard constructor
     *@param name        Name of task
     *@param dataSource  Input source of the data to be displayed
     *@param iVerbose    Verbosity level
     **/
    FairBoxSetDraw(const char* name, FairDataSourceI* dataSource, Int_t iVerbose = 1);

    /** Legacy constructor
     *  Sets the input dataSource to nullptr which sets it to read in TClonesArray
     *@param name        Name of task
     *@param iVerbose    Verbosity level
     **/
    FairBoxSetDraw(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FairBoxSetDraw();

    virtual Double_t GetTimeWindowPlus() { return fTimeWindowPlus; }
    virtual Double_t GetTimeWindowMinus() { return fTimeWindowMinus; }

    /** Set verbosity level. For this task and all of the subtasks. **/
    virtual void SetVerbose(Int_t iVerbose) { fVerbose = iVerbose; };
    virtual void SetBoxDimensions(Double_t x, Double_t y, Double_t z)
    {
        fX = x;
        fY = y;
        fZ = z;
    }

    virtual void SetTimeWindowMinus(Double_t val);
    virtual void SetTimeWindowPlus(Double_t val);
    //    virtual void SetStartTime(Double_t val) { fStartTime = val; }
    //    virtual void UseEventTimeAsStartTime(Bool_t val = kTRUE) { fUseEventTime = val; }

    /** Executed task **/
    virtual void Exec(Option_t* option);

    FairBoxSet* CreateBoxSet();

    void Reset();

  protected:
    Int_t fVerbose;   //  Verbosity level
    virtual InitStatus Init();
    /** Action after each event**/
    virtual void Finish();

    virtual TVector3 GetVector(TObject* obj) = 0;
    virtual Int_t GetValue(TObject* obj, Int_t i);
    virtual void AddBoxes(FairBoxSet* set, TObject* obj, Int_t i = 0);

    FairEventManager* fEventManager = nullptr;   //!
    FairBoxSet* fq = nullptr;                    //!
    Double_t fX{0.3};
    Double_t fY{0.3};
    Double_t fZ{0.3};

    Double_t fTimeWindowPlus{0.};
    Double_t fTimeWindowMinus{0.};
    FairDataSourceI* fDataSource = nullptr;

  private:
    FairBoxSetDraw(const FairBoxSetDraw&);
    FairBoxSetDraw& operator=(const FairBoxSetDraw&);

    ClassDef(FairBoxSetDraw, 1);
};

#endif
