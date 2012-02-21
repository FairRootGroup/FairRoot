#include <iostream>

Bool_t isLibrary(const char* libName)
{
  if (TString(gSystem->DynamicPathName(libName, kTRUE)) != TString(""))
    return kTRUE;
  else  
    return kFALSE;
}    

void g3libs()
{
  cout << "Loading Geant3 libraries ..." << endl;

  if (isLibrary("libdummies.so"))
     gSystem->Load("libdummies.so");
                   // libdummies.so needed from geant3_+vmc version 0.5

  gSystem->Load("libgeant321.so");

  cout << "Loading Geant3 libraries ... finished" << endl;
}
