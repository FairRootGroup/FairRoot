/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MILLE_H
#define MILLE_H

#include <fstream>

/**
 * \class Mille
 *
 *  Class to write a C binary (cf. below) file of a given name and to fill it
 *  with information used as input to pede.
 *  Use its member functions mille(...), special(...), kill() and end() as you would
 *  use the fortran MILLE and its entry points MILLSP, KILLE and ENDLE.
 *
 *  For debugging purposes constructor flags enable switching to text output and/or
 *  to write also derivatives and lables which are ==0.
 *  But note that pede will not be able to read text output and has not been tested with
 *  derivatives/labels ==0.
 *
 *  \author    : Gero Flucke
 *  date       : October 2006
 *  $Revision: 1.3 $
 *  $Date: 2007/04/16 17:47:38 $
 *  (last update by $Author: flucke $)
 */

#include <fstream>
#include <iostream>

class Mille
{
  public:
    Mille(const char* outFileName, bool asBinary = true, bool writeZero = false);
    ~Mille();

    void mille(int NLC, const float* derLc, int NGL, const float* derGl, const int* label, float rMeas, float sigma);
    void special(int nSpecial, const float* floatings, const int* integers);
    void kill();
    void end();

  private:
    void newSet();
    bool checkBufferSize(int nLocal, int nGlobal);

    std::ofstream myOutFile;   // C-binary for output
    bool myAsBinary;           // if false output as text
    bool myWriteZero;          // if true also write out derivatives/lables ==0

    enum
    {
        myBufferSize = 10000
    };
    int myBufferInt[myBufferSize];       // to collect labels etc.
    float myBufferFloat[myBufferSize];   // to collect derivatives etc.
    int myBufferPos;
    bool myHasSpecial;   // if true, special(..) already called for this record

    enum
    {
        myMaxLabel = (0xFFFFFFFF - (1 << 31))
    };   // largest label allowed: 2^31 - 1
};
#endif
