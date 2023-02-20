/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairShieldGenerator header file                 -----
// -----                Created 15/09/06 by V. Friese                  -----
// -------------------------------------------------------------------------

/** FairShieldGenerator
 *@author V.Friese  <v.friese@gsi.de>
 *@since 15.09.06
 *@version 1.0
 *
 ** The FairShieldGenerator is similar to the FairAsciiGenerator. It uses the
 ** ASCII output of the SHIELD code as input for simulation.
 ** The format of the event header is:
 ** event nr.; number of particles; beam momentum; impact parameter
 ** followed by a line for each particle of the format
 ** PID; A; Z; px; py; pz
 ** The PID must be given as for Geant3. For ions, it is 1000. The total
 ** momentum is required, not momentum per nucleon.
 **/

#ifndef FAIRSHIELDGENERATOR_H
#define FAIRSHIELDGENERATOR_H 1

#include "FairGenerator.h"   // for FairGenerator

#include <Rtypes.h>    // for FairShieldGenerator::Class, etc
#include <TString.h>   // for TString
#include <iosfwd>      // for ifstream
#include <map>         // for map

class TDatabasePDG;
class FairPrimaryGenerator;
class FairIon;

class FairShieldGenerator : public FairGenerator
{
  public:
    /** Default constructor without arguments should not be used. **/
    FairShieldGenerator();

    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairShieldGenerator(const char* fileName);

    /** Destructor. **/
    virtual ~FairShieldGenerator();

    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  private:
    std::ifstream* fInputFile;   //! Input file stream
    const Char_t* fFileName;     //! Input file Name
    TDatabasePDG* fPDG;          //!  PDG database

    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    /** Private method RegisterIons. Goes through the input file and registers
     ** any ion needed. **/
    Int_t RegisterIons();

    /** STL map from ion name to FairIon **/
    std::map<TString, FairIon*> fIonMap;   //!

    FairShieldGenerator(const FairShieldGenerator&);
    FairShieldGenerator& operator=(const FairShieldGenerator&);

    ClassDef(FairShieldGenerator, 1);
};

#endif
