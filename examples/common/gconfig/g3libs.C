/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <iostream>

void g3libs()
{
  cout << "Loading Geant3 libraries ..." << endl;

  gSystem->Load("libPythia6");
  gSystem->Load("libEGPythia6");
  gSystem->Load("libgeant321");

  cout << "Loading Geant3 libraries ... finished" << endl;
}
