// -------------------------------------------------------------------------
// -----                  FairPrimaryGenerator header file              -----
// -----                 Created 23/06/04  by  V. Friese               -----
// -------------------------------------------------------------------------


/** FairPrimaryGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *
The FairPrimaryGenerator is responsible for the handling of the MC input.
Several input generators can be registered to it; these have to be
derived from the FairGenerator class. The FairPrimaryGenerator defines
position and (optionally) smearing of the primary vertex.
This class should be instantised only once.

Modified 05.06.07:  add a method DoTracking(Bool_t) to be able to switch on/off
the tracking from the macro (M. Al-Turany)

**/
 

#ifndef CBMPRIMARYGENERATOR_H
#define CBMPRIMARYGENERATOR_H

#include "FairGenerator.h"

#include "TNamed.h"
#include "TObjArray.h"
#include "TVector3.h"

#include <iostream>

class TRandom;
class TF1;
class FairGenericStack;
class FairMCEventHeader;
//class FairGenerator;

class FairPrimaryGenerator : public TNamed 
{

 public:

  /** Default constructor. **/
  FairPrimaryGenerator();


  /** Constructor with name and title **/
  FairPrimaryGenerator(const char* name, const char *title="CBM Generator");


  /** Destructor. **/
  virtual ~FairPrimaryGenerator();


  /** Register a generator derived from FairGenerator.  **/
  void AddGenerator(FairGenerator* generator) {
    if ( ! fGenList ) {
      std::cout << "Empty fGenList pointer ! " << std::endl;
      return;
    }
    fGenList->Add(generator);
  }
      

  /** Public method GenerateEvent
      To be called at the beginning of each event from FairMCApplication.
      Generates an event vertex and calls the ReadEvent methods from the 
      registered generators.
      *@param pStack The particle stack
      *@return kTRUE if successful, kFALSE if not
  **/
  Bool_t GenerateEvent(FairGenericStack* pStack);


  /** Public method AddTrack
      Adding a track to the MC stack. To be called within the ReadEvent
      methods of the registered generators.
      *@param pdgid Particle ID (PDG code)
      *@param px,py,pz Momentum coordinates [GeV]
      *@param vx,vy,vz Track origin relative to event vertex
  **/
  void AddTrack(Int_t pdgid, Double_t px, Double_t py, Double_t pz,
		Double_t vx, Double_t vy, Double_t vz);


  /** Set beam position and widths. 
   *@param beamX0      mean x position of beam at target
   *@param beamY0      mean y position of beam at target
   *@param beamSigmaX  Gaussian beam width in x 
   *@param beamSigmaY  Gaussian beam width in y 
   **/
  void SetBeam(Double_t beamX0, Double_t beamY0, 
	       Double_t beamSigmaX, Double_t beamSigmaY);


  /** Set target position and thickness.
   *@param targetZ   z position of target center
   *@param targetDz  full target thickness
   **/
  void SetTarget(Double_t targetZ, Double_t targetDz);

  /** Set target position for multiple tagets. The thickness 
   * is the same for all targets.
   *@param nroftargets   number of targets
   *@param *targetZ      z positions of target center
   *@param targetDz      full target thickness
   **/
  void SetMultTarget(Int_t nroftargets, Double_t* targetZ, Double_t targetDz);


  /** Enable vertex smearing in z and/or xy direction **/
  void SmearVertexZ(Bool_t flag)  { fSmearVertexZ  = flag; };
  void SmearVertexXY(Bool_t flag) { fSmearVertexXY = flag; };

  TObjArray* GetListOfGenerators() { return fGenList;}


  /** Set the pointer to the MCEvent **/
  void SetEvent(FairMCEventHeader* event) { fEvent = event; };


  /** Accessor to the MCEvent **/
  FairMCEventHeader* GetEvent() { return fEvent; };

 /** Swich on/off the tracking of a particle*/

  void DoTracking(Bool_t doTracking= kTRUE){fdoTracking=doTracking ;}


  /** Set the min and max limit for event time in ns */
  void SetEventTimeInterval(Double_t min, Double_t max);
  
  /** Set the mean time for the event in ns */
  void SetEventMeanTime(Double_t mean);
  

 private:

  Double_t    fBeamX0;        //  Nominal beam position at target in x [cm]
  Double_t    fBeamY0;        //  Nominal beam position at target in y [cm]
  Double_t    fBeamSigmaX;    //  Beam width (Gaussian) in x [cm]
  Double_t    fBeamSigmaY;    //  Beam width (Gaussian) in y [cm]
  Double_t*   fTargetZ;       //!  Nominal z position of center of targets [cm]
  Int_t       fNrTargets;     //  Number of targets;
  Double_t    fTargetDz;      //  Full target thickness [cm]
  TVector3    fVertex;        //  Vertex position of current event [cm]
  Int_t       fNTracks;       //  Number of primary tracks in current event
  Bool_t      fSmearVertexZ;  //  Flag for vertex smearing in z
  Bool_t      fSmearVertexXY; //  Flag for vertex smearing in xy
  TRandom*    fRandGen;       //  Pointer to random generator
  FairGenericStack*   fStack;  //!  Pointer to MC stack
  TObjArray*  fGenList;       //  List of registered generators
  TIterator*  fListIter;      //!  Iterator over generator list
  FairMCEventHeader* fEvent;   //!  Pointer to MCEventHeader
  Bool_t      fdoTracking;    //! go to tracking  
  Double_t    fEventTimeMin;  //! min time for one event (ns)
  Double_t    fEventTimeMax;  //! max time for one Event (ns)
  Double_t    fEventTime;     //! Time of event since th start (ns)
  Double_t    fEventMeanTime; //! EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime)
  TF1*        fTimeProb;      //! used to generate random numbers for event time;

  /** Private method MakeVertex. If vertex smearing in xy is switched on, 
      the event vertex is smeared Gaussianlike in x and y direction 
      according to the mean beam positions and widths set by the 
      SetBeam method. If vertex smearing in z is switched on, the z 
      coordinate of the event vertex is flatly distributed over the 
      extension of the target. 
      To be called at the beginning of the event from the 
      GenerateEvent method.
  **/
  void MakeVertex();
  
  FairPrimaryGenerator(const FairPrimaryGenerator &P);
  FairPrimaryGenerator& operator= (const  FairPrimaryGenerator&) {return *this;}

  ClassDef(FairPrimaryGenerator,3);

};

#endif


