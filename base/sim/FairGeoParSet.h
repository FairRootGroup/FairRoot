/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairGeoParSet_H
#define FairGeoParSet_H

#include <Rtypes.h>        // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>    // for Bool_t
#include <TGeoManager.h>   // for TGeoManager (ptr only)

/**
 * Parameter class for Geometry stuff
 * @author M. Al-Turany
 * @version 1
 * @since 12.10.04
 */
#include "FairParGenericSet.h"   // for FairParGenericSet

class FairParamList;
class TObjArray;
class TBuffer;
class TClass;
class TMemberInspector;

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
    ~FairGeoParSet(void);
    /** clear*/
    void clear(void);
    /**
     * Fills all persistent data members into the list for write.
     * @param FairParamList : Parameter list to be filled
     */
    void putParams(FairParamList*);
    /**
     * Fills all persistent data members from the list after reading. The function
     * returns false, when a data member is not in the list.
     * @param FairParamList : Parameter list to be filled
     */

    Bool_t getParams(FairParamList*);
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
    ClassDef(FairGeoParSet, 1);

  private:
    FairGeoParSet(const FairGeoParSet& L);
    FairGeoParSet& operator=(const FairGeoParSet&) { return *this; }
};

#endif /* !FairGeoParSet_H */
