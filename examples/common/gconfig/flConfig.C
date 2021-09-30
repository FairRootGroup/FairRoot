/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/// Configuration macro for Geant3 VirtualMC

void Config()
{

    new TFluka("C++ Interface to Fluka", 1 /*verbositylevel*/);

    cout << "GConfig: Fluka has been created." << endl;

    FairStack *st = new FairStack();
    st->SetMinPoints(0);
    TVirtual::GetMC()->SetStack(st);
    TVirtual::GetMC()->SetProcess("CKOV", 1);

    // set the common cuts
    TString configm = FairConfig::Instance().GetVMCWorkDir();
    TString cuts = configm + "/gconfig/SetCuts.C";
    cout << "Physics cuts with script \n " << cuts.Data() << endl;
    Int_t cut = gROOT->LoadMacro(cuts.Data());
    if (cut == 0)
        gInterpreter->ProcessLine("SetCuts()");
}
