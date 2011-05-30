rootlogon()
{
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
  basiclibs();
  
  // Load this example libraries
        gSystem->Load("libFairTools");
  	gSystem->Load("libGeoBase");
	gSystem->Load("libParBase");
	gSystem->Load("libBase");
	gSystem->Load("libMCStack");
	gSystem->Load("libField");
	gSystem->Load("libPassive");
	gSystem->Load("libGen");
	gSystem->Load("libPGen");
	gSystem->Load("libGeane");
}
