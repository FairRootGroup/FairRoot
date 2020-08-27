/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairAsciiGenerator header file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**  FairAsciiGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *@author M.Al-Turany<M.Al-Turany@gsi.de>
 *
 The FairAsciiGenerator reads an Ascii input file. The file must contain
 for each event a header line of the format  NTRACKS  IEV  VX VY VZ,
 where NTRACKS is the number of tracks in the event, IEV the event number,
 and VX, VY, VZ the event vertex coordinates in cm. The header line is
 followed by NTRACKS lines of the format G3PID, PX, PY, PZ, where
 G3PID is the Geant3 particle code, and PX, PY, PZ the cartesian
 momentum coordinates in GeV.
 Derived from FairGenerator.
**/

#ifndef FAIR_ASCIIGENERATOR_H
#define FAIR_ASCIIGENERATOR_H

#include "FairGenerator.h"   // for FairGenerator

#include <Rtypes.h>   // for FairAsciiGenerator::Class, etc
#include <iosfwd>     // for ifstream

class FairPrimaryGenerator;

class FairAsciiGenerator : public FairGenerator
{
  public:
    /** Default constructor without arguments should not be used. **/
    FairAsciiGenerator();

    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairAsciiGenerator(const char* fileName);

    /** Destructor. **/
    virtual ~FairAsciiGenerator();

    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  private:
    std::ifstream* fInputFile;   //! Input file stream
    const Char_t* fFileName;     //! Input file Name

    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    FairAsciiGenerator(const FairAsciiGenerator&);
    FairAsciiGenerator& operator=(const FairAsciiGenerator&);

    /** PDG data base */

    // TDatabasePDG *fPDG; //!

    ClassDef(FairAsciiGenerator, 1);
};

#endif
