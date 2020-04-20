void DecayConfigPythia8()
{
    // Create a new external decayer instance
    TPythia8Decayer* decayer = new TPythia8Decayer();

    // Create a new TPythia8 instance
    TPythia8* pythia8 = TPythia8::Instance();

    TVirtualMC::GetMC()->SetExternalDecayer(decayer);

    const Int_t npartnf = 9;
    Int_t pdgnf[npartnf] = {13, -13, 211, -211, 321, -321, 130, 3312, 443};
    for (Int_t ipartnf = 0; ipartnf < npartnf; ipartnf++) {
        Int_t ipdg = pdgnf[ipartnf];
        TVirtualMC::GetMC()->SetUserDecay(ipdg);   // Force the decay to be done w/external decayer
    }

    decayer->Init();
}

void DecayConfig() { DecayConfigPythia8(); }
