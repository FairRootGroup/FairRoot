/********************************************************************************
 *                  Copyright (C) 2026 Jagiellonian University                  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * @class FairShapeSetDraw FairShapeSetDraw.h
 * @author R. Lalik <Rafal.Lalik@uj.edu.pl>
 * @since 19.10.2026
 * @brief Base class to display 3D Shape in Eve corensponding to a point.
 * @details It provides interface for pure virtual methods GetShape(), which takes TObject (points to the objects being
 * visualised) and returns eight corners (represented as linearised 24 values array) of custom shape.
 *
 * If one wants to change the color of the points one has to overwrite the method GetValue().
 **/

#ifndef FAIRSHAPESETDRAW_H
#define FAIRSHAPESETDRAW_H

#include "FairDataSourceI.h"
#include "FairTSBufferFunctional.h"   // IWYU pragma: keep needed for cint
#include "FairTask.h"                 // for FairTask, InitStatus

class FairShapeSet;
class FairEventManager;
class FairRootManager;

class TShape;
class TClonesArray;
class TObject;
class TVector3;

class FairShapeSetDraw : public FairTask
{
  public:
    /** Default constructor **/
    FairShapeSetDraw();

    /** Standard constructor
     *@param name        Name of task
     *@param dataSource  Input source of the data to be displayed
     *@param color		 Color of points
     *@param mstyle		 Style of points
     *@param iVerbose    Verbosity level
     **/
    FairShapeSetDraw(const char* name, FairDataSourceI* dataSource, Color_t color, Style_t mstyle, Int_t iVerbose = 1);

    /** Legacy constructor
     *  Sets the input dataSource to nullptr which sets it to read in TClonesArray
     *@param name        Name of task
     *@param color		 Color of points
     *@param mstyle		 Style of points
     *@param iVerbose    Verbosity level
     **/
    FairShapeSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose = 1);

    FairShapeSetDraw(const FairShapeSetDraw&) = delete;
    FairShapeSetDraw(FairShapeSetDraw&&) = delete;
    FairShapeSetDraw& operator=(const FairShapeSetDraw&) = delete;
    FairShapeSetDraw& operator=(FairShapeSetDraw&&) = delete;

    /** Destructor **/
    virtual ~FairShapeSetDraw() = default;

    virtual Double_t GetTimeWindowPlus() { return fTimeWindowPlus; }
    virtual Double_t GetTimeWindowMinus() { return fTimeWindowMinus; }

    /** Set verbosity level. For this task and all of the subtasks. **/
    virtual void SetVerbose(Int_t iVerbose) { fVerbose = iVerbose; };

    virtual void SetTimeWindowMinus(Double_t val);
    virtual void SetTimeWindowPlus(Double_t val);

    /** Executed task **/
    virtual void Exec(Option_t* option);

    FairShapeSet* CreateShapeSet();

    void Reset();

  protected:
    virtual InitStatus Init();
    /** Action after each event**/
    virtual void Finish();

    /** Shape definition.
     * @brief Shape is defiend as a 8 points (corners) stored in continuous vector:
     * x0,y0,z0,x1,y1,z1,...,x7,y7,z7.
     * @param obj object for which the shape is drawn.
     * @return Shapre definition.
     */
    virtual std::array<Float_t, 8 * 3> GetShape(TObject* obj) = 0;   // eight corners * 3D

    /** Change the color of the shape.
     * @brief This method takes a TObject and an integer and translates this into an integer as input
     * for the EveShapeSet method DigitValue.
     * @param obj object for which the shape is drawn.
     * @param i value for which the color is calculated.
     * @return color.
     */
    virtual Int_t GetValue(TObject* obj, Int_t i);
    virtual void AddShapes(FairShapeSet* set, TObject* obj, Int_t i = 0);

    FairEventManager* fEventManager{nullptr};   //!
    FairShapeSet* fq{nullptr};                  //!
    Color_t fColor;                             //!
    Style_t fStyle;                             //!
    Int_t fVerbose{0};                          //!  Verbosity level

    Double_t fTimeWindowPlus{0.};
    Double_t fTimeWindowMinus{0.};
    FairDataSourceI* fDataSource{nullptr};

    ClassDef(FairShapeSetDraw, 1);
};

#endif
