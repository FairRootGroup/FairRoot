generators
========

The input to the `FairRunSim` is provided by the particle generator. 
There are several particle generators implemented in FairRoot, however it is possible to develop additional generators - 
they need to derive from FairGenerator and contain the ReadEvent() function that pushes generated tracks onto the stack. 
One may add several particle generators to FairRunSim. 

The following generators are part of FairRoot:

* FairParticleGenerator generates a single particle type with given momentum components, vertex and multiplicity per event.
* FairBoxGenerator generates particles within given range over pt, phi, eta, y or theta a fixed multiplicity per event.
* FairIonGenerator for the generation of ions with pre-defined FairIon
* FairAsciiGenerator reads an Ascii input file. The file must contain for each event a header line of the format  NTRACKS  IEV  VX VY VZ, where NTRACKS is the number of tracks in the event, IEV the event number, and VX, VY, VZ the event vertex coordinates in cm. The header line is followed by NTRACKS lines of the format G3PID, PX, PY, PZ, where G3PID is the Geant3 particle code, and PX, PY, PZ the cartesian momentum coordinates in GeV.
* FairUrqmdGenerator reads the output file 14 (ftn14) from UrQMD. The UrQMD calculation has to be performed in the CM system of the collision; Lorentz transformation into the lab is performed by this class.
* FairPlutoGenerator reads the PLUTO output file (ROOT format) and inserts the tracks into the FairStack via the FairPrimaryGenerator.
* FairPlutoReactionGenerator inserts an inline PReaction and thus connects Pluto with the FairPrimaryGenerator.
* FairShieldGenerator is similar to the FairAsciiGenerator. It uses the ASCII output of the SHIELD code as input for simulation. The format of the event header is: event nr., number of particles, beam momentum, impact parameter; followed by a line for each particle of the format: PID; A; Z; px; py; pz. The PID must be given as for Geant3. For ions, it is 1000. The total momentum is required, not momentum per nucleon.


