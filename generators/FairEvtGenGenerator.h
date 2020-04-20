/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairEvtGenGenerator header file                 -----
// -----          Created 09/10/06  by S. Spataro                      -----
// -------------------------------------------------------------------------

/**  FairEvtGenGenerator.h
 *@author S.Spataro  <stefano.spataro@exp2.physik.uni-giessen.de>
 *
 The FairEvtGenGenerator reads an EvtGen input file. The file must contain
 for each event a header line of the format:

 [start]
1       11
  N      Id Ist   M1   M2   DF   DL      px      py      pz       E       t       x       y       z
  0   70553   2   -1   -1    1    2  0.0000  0.0000  0.0000 10.5704  0.0000  0.0000  0.0000  0.0000
  1     521   2    0    0    3    4 -0.1756  0.1064 -0.1494  5.2852  0.0000  0.0000  0.0000  0.0000
  2    -521   2    0    0    7    8  0.1756 -0.1064  0.1494  5.2852  0.0000  0.0000  0.0000  0.0000
  3     333   2    1    1    5    6 -1.4042 -2.0079 -0.7628  2.7603  0.0492 -0.0016  0.0010 -0.0014
  4     211   1    1    1   -1   -1  1.2286  2.1142  0.6134  2.5249  0.0492 -0.0016  0.0010 -0.0014
  5     321   1    3    3   -1   -1 -0.9021 -1.1453 -0.4297  1.5981  0.0492 -0.0016  0.0010 -0.0014
  6    -321   1    3    3   -1   -1 -0.5021 -0.8625 -0.3330  1.1622  0.0492 -0.0016  0.0010 -0.0014
  7     333   2    2    2    9   10 -1.2388  0.1390 -2.0780  2.6316  0.6223  0.0207 -0.0125  0.0176
  8    -211   1    2    2   -1   -1  1.4144 -0.2454  2.2274  2.6536  0.6223  0.0207 -0.0125  0.0176
  9     321   1    7    7   -1   -1 -0.4624  0.1538 -0.9382  1.1668  0.6223  0.0207 -0.0125  0.0176
 10    -321   1    7    7   -1   -1 -0.7764 -0.0148 -1.1398  1.4649  0.6223  0.0207 -0.0125  0.0176


2       11
  N      Id Ist   M1   M2   DF   DL      px      py      pz       E       t       x       y       z
  0   70553   2   -1   -1    1    2  0.0000  0.0000  0.0000 10.5699  0.0000  0.0000  0.0000  0.0000
  1     521   2    0    0    3    4 -0.2228 -0.0227 -0.1080  5.2850  0.0000  0.0000  0.0000  0.0000
  2    -521   2    0    0    7    8  0.2228  0.0227  0.1080  5.2850  0.0000  0.0000  0.0000  0.0000
  3     333   2    1    1    5    6  2.2879  0.7442 -0.3869  2.6413  0.0413 -0.0017 -0.0002 -0.0008
  4     211   1    1    1   -1   -1 -2.5107 -0.7669  0.2789  2.6437  0.0413 -0.0017 -0.0002 -0.0008
  5     321   1    3    3   -1   -1  0.9174  0.3217 -0.2480  1.1182  0.0413 -0.0017 -0.0002 -0.0008
  6    -321   1    3    3   -1   -1  1.3705  0.4225 -0.1389  1.5231  0.0413 -0.0017 -0.0002 -0.0008
  7     333   2    2    2    9   10  2.2762 -1.0938 -0.6929  2.8103  0.0116  0.0005  0.0000  0.0002
  8    -211   1    2    2   -1   -1 -2.0534  1.1165  0.8009  2.4747  0.0116  0.0005  0.0000  0.0002
  9     321   1    7    7   -1   -1  1.4371 -0.7057 -0.4321  1.7302  0.0116  0.0005  0.0000  0.0002
 10    -321   1    7    7   -1   -1  0.8392 -0.3881 -0.2608  1.0801  0.0116  0.0005  0.0000  0.0002


...
 [stop]

 where the first row has the number of event and the number of particles, and below "N" is the line
 number of the event, "Id" is the PDG id number, "Ist" is the number of daughter particles, "M1" and
 "M2" are the two "N" numbers of the mother particle, "DF" and "DL" the "N" of the daughter particles,
 "px" "py" "pz" "E" are the 4-momentum components [in GeV/c], "x" "y" "z" "t" are vertex positions
 [in mm] and decay time.

 In order to produce the output file one shoulkd write, in the EvtGen macro:

 [CUT]
  ...
  ofstream out;
  out.open("evtgen_out.evt");

  EvtStdHep stdhep;
  myGenerator.generateEvent(root_part,t_init);
  stdhep.init();
  root_part->makeStdHep(stdhep);

  out << count << "\t" << stdhep.getNPart();
  out <<stdhep<<endl;

  root_part->deleteTree();
...
[CUT]

 Derived from FairGenerator.
**/

#ifndef FAIR_EVTGENGENERATOR_H
#define FAIR_EVTGENGENERATOR_H

#include "FairGenerator.h"   // for FairGenerator

#include <Rtypes.h>   // for FairEvtGenGenerator::Class, etc
#include <stdio.h>    // for FILE

class FairPrimaryGenerator;
class TF1;

class FairEvtGenGenerator : public FairGenerator
{
  public:
    /** Default constructor without arguments should not be used. **/
    FairEvtGenGenerator();

    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairEvtGenGenerator(const char* fileName);

    /** @param fileName: The input file name, DensityFunction: axial gas density
     **/
    FairEvtGenGenerator(const char* fileName, Double_t Rsigma, TF1* DensityFunction);

    /** Destructor. **/
    virtual ~FairEvtGenGenerator();

    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  private:
    // ifstream* fInputFile;             //! Input file stream
    const Char_t* fFileName;   //! Input file Name
    FILE* fInputFile;          //! Input file pointer

    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    int fGasmode;
    double fRsigma;

    /** PDG data base */

    // TDatabasePDG *fPDG; //!
    TF1* fDensityFunction;

    FairEvtGenGenerator(const FairEvtGenGenerator&);
    FairEvtGenGenerator& operator=(const FairEvtGenGenerator&);

    ClassDef(FairEvtGenGenerator, 1);
};

#endif
