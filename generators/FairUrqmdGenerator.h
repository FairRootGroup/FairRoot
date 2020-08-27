/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairUrqmdGenerator header file                  -----
// -----          Created 11/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/** FairUrqmdGenerator.h
 *@ author V.Friese <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *
 The FairUrqmdGenerator reads the output file 14 (ftn14) from UrQMD. The UrQMD
 calculation has to be performed in the CM system of the collision; Lorentz
 transformation into the lab is performed by this class.
 Derived from FairGenerator.
**/

#ifndef FAIRURQMDGENERATOR_H
#define FAIRURQMDGENERATOR_H

#include "FairGenerator.h"   // for FairGenerator

#include <Rtypes.h>   // for Int_t, Bool_t, etc
#include <TString.h>
#include <map>       // for map
#include <stdio.h>   // for FILE

class FairPrimaryGenerator;

class FairUrqmdGenerator : public FairGenerator
{
  public:
    /** Default constructor without arguments should not be used. **/
    FairUrqmdGenerator();

    /** Standard constructor.
     * @param fileName The input file name
     **/
    FairUrqmdGenerator(const char* fileName);

    /** Standard constructor.
     * @param fileName The input file name
     * @param conversion_table name of conversion table file (from Urqmd->PDG) should use the full path to the file
     **/

    FairUrqmdGenerator(const char* fileName, const char* conversion_table);

    /** Destructor. **/
    ~FairUrqmdGenerator();

    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param pStack    pointer to the stack
     ** @param ver       not used
     **/
    Bool_t ReadEvent(FairPrimaryGenerator* primGen);

    /** Skip defined number of events in file **/
    Bool_t SkipEvents(Int_t count);

  private:
    FILE* fInputFile;   //!  Input file

    std::map<Int_t, Int_t> fParticleTable;   //!  Map from UrQMD PID to PDGPID

    const Char_t* fFileName;   //!  Input file name

    /** Private method ReadConversionTable. Reads the conversion table
        from UrQMD particle code to PDG particle code and fills the
        conversion map. Is called from the constructor. **/
    void ReadConversionTable(TString conversion_table = "");

    /** Check return value from fscanf call **/
    void CheckReturnValue(Int_t retval);

    FairUrqmdGenerator(const FairUrqmdGenerator&);
    FairUrqmdGenerator& operator=(const FairUrqmdGenerator&);

    ClassDef(FairUrqmdGenerator, 1);
};

#endif
