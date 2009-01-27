// $Id$

//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file fllibs.C
/// \brief Macro for loading FLUKA libraries

#include <iostream>

void fllibs()
{
/// Macro function for loading FLUKA libraries

  cout << "Loading Fluka libraries ..." << endl;

  gSystem->Load("libfluka.so");
  
  cout << "Loading Fluka libraries ... finished" << endl;
}

