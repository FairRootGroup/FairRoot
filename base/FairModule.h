#ifndef FAIRMODULE_H
#define FAIRMODULE_H

#include "TString.h"
#include "TNamed.h"
#include "TRefArray.h"

class FairVolumeList;
class FairVolume;
class FairGeoNode;
class TGeoNode;
class TGeoMatrix;
class TGeoVolume;
class TList;
class TArrayI;
/**
 * Base class for constructing all detecors and passive volumes
 * @author M. Al-Turany, Denis Bertini
 * @version 1.0
 * @since 01.04.08 M.Al-Turany
 * Add methods to construct geometry via ROOT files
 * Add some documentation
 */
class FairModule:  public TNamed
{
public:
	/**default ctor*/
    FairModule();
    /**Standard ctor*/
    FairModule(const char * Name, const char *title, Bool_t Active=kFALSE);
    /**default dtor*/
    virtual  ~FairModule();
    /**Print method sould be implimented in detector or module*/
    virtual void        Print() const{;}
    /**Set the geometry file name o be used*/
    virtual void        SetGeometryFileName(TString fname, TString geoVer="0"); 
    /**Get the Geometry file name*/
    virtual TString     GetGeometryFileName(){return  fgeoName ;}
    /**Get the geometry file version if used*/
    virtual TString     GetGeometryFileVer(){return   fgeoVer ;}
    /**method called from the MC application to construct the geometry, has to be implimented by user*/
    virtual void        ConstructGeometry();
    /**method called from the MC application to set optical geometry properties*/
    virtual void        ConstructOpGeometry();
    /**construct geometry from root files (TGeo)*/
    virtual void        ConstructRootGeometry();
    /**construct geometry from standard ASSCII files (Hades Format)*/
    virtual void        ConstructASCIIGeometry(); 
    /**Set the sensitivity flag fro volumes, called from ConstructASCIIRootGeometry(), and has to be implimented for detectors 
     * which use ConstructASCIIRootGeometry() to build the geometry */
    virtual Bool_t      CheckIfSensitive(std::string name);
    /**called from ConstructRootGeometry()*/
    virtual void        ExpandNode(TGeoNode *Node);
    /**return the MC id of a volume named vname*/
    virtual Int_t       getVolId( const TString& vname ) const {return 0;}
    /**return the detector/Module id (which was set in the sim macro for the detector)*/
    Int_t               GetModId(){return fModId;}
    /**Set the verbose level in this detector*/
    void                SetVerboseLevel(Int_t level){fVerboseLevel=level;}
    /**return the detector status */
    Bool_t              IsActive(){return fActive;}
    /**set the detector/module id*/
    void                SetModId(Int_t id){fModId=id;}
    /** Set the name of the mother volume to which a new geometry is added. 
     ** This function is needed for geometries which are defined as ROOT geometry manager. 
     **/
    void                SetMotherVolume(TString volName){fMotherVolumeName=volName;}
    /**called from ConstuctASCIIGeometry*/
    void                ProcessNodes ( TList *aList );
    /**return the geo parameter of this detector/module*/
    TList * GetListOfGeoPar() { return flGeoPar;}
    /**list of volumes in a simulation session*/
    static              FairVolumeList   *vList; //!
    /**total number of volumes in a simulaion session*/
    static Int_t        fNbOfVolumes;  //!
    /**list of all sensitive volumes in  a simulaion session*/
    static TRefArray*   svList;   //!
    
    static TArrayI*     volNumber; //! 
    TString             fMotherVolumeName; //!
    FairVolume*		getFairVolume(FairGeoNode *fNode);
    void		AddSensitiveVolume(TGeoVolume *v);
   
private:
   FairModule(const FairModule &M);
   FairModule& operator= (const FairModule&) {return *this;}
   /** Re-implimented from ROOT:  TGeoMatrix::SetDefaultName()  */
   void SetDefaultMatrixName(TGeoMatrix* matrix);

protected:    
    TString             fgeoVer;
    TString             fgeoName;    
    Int_t               fModId;
    Bool_t	        fActive; 
    Int_t               fNbOfSensitiveVol; //!
    Int_t               fVerboseLevel;
    TList *flGeoPar; //!  list of Detector Geometry parameters
    Bool_t kGeoSaved; //! flag for initialisation


    ClassDef( FairModule,1)
};
    
#endif //FAIRMODULE_H
