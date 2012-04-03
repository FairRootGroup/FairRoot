#ifndef FAIRBASEPARSET_H
#define FAIRBASEPARSET_H

/**
 * Parameter class for run
 * @author M. Al-Turany
 * @version 1
 * @since 12.10.04
 */


#include "FairParGenericSet.h"
#include "TGeoManager.h"
#include "TObjString.h"
class FairPrimaryGenerator;
class TObjArray;

class FairBaseParSet : public FairParGenericSet
{
  public:
    /**
     * constructor
     * @param name :  Parameter set name
    * @param title:  Parameter set title
    * @param context:  Parameter set context
    */


    FairBaseParSet(const char* name="FairBaseParSet",
                   const char* title="Class for base parameter io",
                   const char* context="BaseDefaultContext");
    /** dtor*/
    ~FairBaseParSet(void);
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
     * Set the detector list used in the simulation
     * @param array: TObjArray of detector
     */
    void SetDetList(TObjArray* array) {fDetList=array;}
    /**
     * Set the Geometry node list used in the simulation
     * @param array: TObjArray of Geometry nodes
     */
    void SetGeoNodes(TObjArray* array) {fGeoNodes=array;}
    /**
     * Set the Generator used in the simulation
     * @param gen: Primary generator used in simulation
     */
    void SetGen(FairPrimaryGenerator* gen) {fPriGen=gen;}
    /**
     * Set the beam momentum (if any) used in the simulation
     * @param BMom: Beam Momentum in GeV/c
     */
    void SetBeamMom(Double_t  BMom) {fBeamMom = BMom;}
    /**
     * Set the Geometry (TGeoManager) used in the simulation
     * @param Geom: TGeoManager of the full geometry
     */
    void SetGeometry(TGeoManager* Geom) {fGeom=Geom;}
    /**
     * Set the list of parameter containers used in a run
     * @param array: TObjArray of containers
     */
    void SetContListStr(TObjArray* list) {fContNameList= list;}
    /**
     *  Get the detector list used in the simulation
     */
    TObjArray*             GetDetList() {return fDetList;}
    /**
    *  Get the Geometry Nodes list used in the simulation
    */
    TObjArray*             GetGeoNodes() {return fGeoNodes;}
    /**
     *  Get the Primery generator used in the simulation
     */
    FairPrimaryGenerator*   GetPriGen() {return fPriGen; }
    /**
     *  Get the Beam Momentum used in the simulation (GeV/c)
     */
    Double_t          GetBeamMom() {return fBeamMom; }
    /**
     *  Get the geometry (TGeoManager) used in the simulation
     */
    TGeoManager*           GetGeometry() {return fGeom;}
    /**
     *  Get the parameter container list used in this run
     */
    TObjArray*             GetContList() {return fContNameList;}

  protected:

    /// Detectors used in the simulation
    TObjArray*              fDetList;
    /// List of FairGeoNodes for sensitive volumes
    TObjArray*              fGeoNodes; //!
    ///Generator used for simulation
    FairPrimaryGenerator*   fPriGen;
    ///Beam momentum (GeV/c)
    Double_t              fBeamMom;
    /// Full Geometry
    TGeoManager*            fGeom;
    /// List of parameter container names in the RUN
    TObjArray*              fContNameList;

    ClassDef(FairBaseParSet,4)

  private:
    FairBaseParSet(const FairBaseParSet& L);
    FairBaseParSet& operator= (const FairBaseParSet&) {return *this;}



};

#endif /* !FAIRBASEPARSET_H */
