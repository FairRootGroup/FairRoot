/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairGeoParSet_H
#define FairGeoParSet_H

/**
 * Parameter class for Geometry stuff
 * @author M. Al-Turany
 * @version 1
 * @since 12.10.04
 */
#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>        // for Double_t, etc
#include <TGeoManager.h>   // IWYU pragma: keep needed by cint

class FairParamList;
class TObjArray;

class FairGeoParSet : public FairParGenericSet
{
  public:
    /**
     * constructor
     * @param name :  Parameter set name
     * @param title:  Parameter set title
     * @param context:  Parameter set context
     */

    FairGeoParSet(const char* name = "FairGeoParSet",
                  const char* title = "Class for base parameter io",
                  const char* context = "BaseDefaultContext");
    /** dtor*/
    ~FairGeoParSet() override;
    /** clear*/
    void clear() override;
    /**
     * Fills all persistent data members into the list for write.
     * @param FairParamList : Parameter list to be filled
     */
    void putParams(FairParamList*) override;
    /**
     * Fills all persistent data members from the list after reading. The function
     * returns false, when a data member is not in the list.
     * @param FairParamList : Parameter list to be filled
     */

    Bool_t getParams(FairParamList*) override;
    /**
     * Set the Geometry node list used in the simulation
     * @param array: TObjArray of Geometry nodes
     */
    void SetGeoNodes(TObjArray* array) { fGeoNodes = array; }
    /**
     * Set the Geometry (TGeoManager) used in the simulation
     * @param Geom: TGeoManager of the full geometry
     */
    void SetGeometry(TGeoManager* Geom) { fGeom = Geom; }
    /**
     *  Get the Geometry Nodes list used in the simulation
     */
    TObjArray* GetGeoNodes() { return fGeoNodes; }
    /**
     *  Get the geometry (TGeoManager) used in the simulation
     */
    TGeoManager* GetGeometry() { return fGeom; }

  protected:
    /// List of FairGeoNodes for sensitive volumes
    TObjArray* fGeoNodes;   //!
    /// Full Geometry
    TGeoManager* fGeom;
    ClassDefOverride(FairGeoParSet, 1);

  private:
    FairGeoParSet(const FairGeoParSet& L);
    FairGeoParSet& operator=(const FairGeoParSet&) { return *this; }
};

#endif /* !FairGeoParSet_H */
