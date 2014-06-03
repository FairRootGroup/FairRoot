/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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
