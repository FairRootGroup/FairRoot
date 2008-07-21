// -------------------------------------------------------------------------
// -----                      CbmRadLenManager source file             -----
// -----                  Created 14/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef CBMRADLENMANAGER_H
#define CBMRADLENMANAGER_H 1


#include "Rtypes.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"



/**
 * @class CbmRadLenManager
 */


class CbmRadLenManager {

 public:
  /**
   * Default constructor.
   * Creates the singleton object of CbmRadLenManager class.
   * The pointer to this object can be reached via CbmRadLenManager::Instance().
   */
  CbmRadLenManager();

  /**
   * Destructor.
   */
  virtual ~CbmRadLenManager();

  /**
   * Class definition.
   */
  ClassDef(CbmRadLenManager,1);


 private:
 
  CbmRadLenManager(const CbmRadLenManager &L);
  CbmRadLenManager& operator= (const CbmRadLenManager&) {return *this;}
 
  static CbmRadLenManager *fgInstance;
 
 /**
  * collection of point
  */
  TClonesArray*  fPointCollection; 
  /**track index */
  Int_t          fTrackID;           //!  
  /**volume id */
  Int_t          fVolumeID;          //!  
  /**  entry position in global frame*/
  TLorentzVector fPosIn;             //! 
  /**  exit position in global frame*/
  TLorentzVector fPosOut;            //! 
  /**  momentum in*/
  TLorentzVector fMomIn;             //! 
  /**  momentum out*/
  TLorentzVector fMomOut;            //! 
  /**track time */
  Double_t       fTime;                //!  
  /**track length */
  Double_t       fLength;              //!  
  /** energy loss */
  Double_t       fELoss;               //! 
  /** mass umber*/
  Float_t        fA;                      
  /** atomic number*/
  Float_t        fZmat;                
  /**  density */
  Float_t        fDensity;              
  /**radition length */
  Float_t        fRadl;                  
  /**absorption length */
  Float_t 	     fAbsl;                  
 
public:
   /**Add point to collection*/	
   void  AddPoint();
   /**initialize the manager*/
   void  Init();
   /**reset*/
   void  Reset();
  /**
   * This function is used to access the methods of the class.
   * @return Pointer to the singleton CbmRadLenManager object, created
   * with CbmRadLenManager::CbmRadLenManager().
   */
  static CbmRadLenManager* Instance();
};

#endif
