/********************************************************************************
 *    Copyright (C) 2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Configuration macro for Geant4 VirtualMC PostInit
void ConfigPostInit()
{
    cout << "Loading Geant4 PostInit Config." << endl;
    TString configm(gSystem->Getenv("VMCWORKDIR"));
    TString configm1 = configm + "/common/gconfig/g4configPostInit.in";
    cout << " -I g4ConfigPostInit using g4configPostInit macro: " << configm1 << endl;

    // set geant4 specific stuff
    TGeant4 *geant4 = (TGeant4*)(TVirtualMC::GetMC());
    geant4->ProcessGeantMacro(configm1.Data());
}
