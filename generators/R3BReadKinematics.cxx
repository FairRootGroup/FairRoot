/////////////////////////////////////////////////////////////////
//*-- AUTHOR : Oleg Kiselev		O.Kiselev@gsi.de
//*-- Date: 11/2005
//*-- Last Update: 20/07/05 Hector Alvarez
// --------------------------------------------------------------
// Description:
//   Event generator kinematics reader
//
// --------------------------------------------------------------
// Comments:
// 
// --------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////

#include "R3BReadKinematics.h"
#include "TSystem.h"
#include "TString.h"


ClassImp(R3BReadKinematics)

using namespace std;

R3BReadKinematics::R3BReadKinematics(){

  TString WorkDir = gSystem->Getenv("VMCWORKDIR");


  //
  // Constructor, all job here
  //

Double_t a,b,c,d,e,f,j, h,k,l,m,n;
Double_t Integral = 0.;
Int_t i, nbins;
const Int_t MAX = 140;
Char_t buffer[MAX];


//zero initial values
    for(i=0;i<1000;i++){
	  LabAngle[i]  = 0.;
		LabEnergy[i] = 0.;
		
		} 

 for(i=0;i<5000;i++){
 T_xsec[i] = 0.;
 CrossSection_t[i] = 0.;
 Icross_section[i] = 0.;
 }
 
//Read kinematical file
    TString kine1 = WorkDir+"/input/kine/KINR.OUT.12c_p_p_0MeV_400MeV_long.dat";
    ifstream infile(kine1.Data());

     if (!infile) exit(0);
     for(i=0;i<17;i++){
	  infile.getline(buffer, MAX);//readout header
//	  cout << "i=" << i << " buffer" << infile.rdbuf() <<  G4endl;
		} 
//	cout << "read file" << i << G4endl;
	i = -1;
	while( !infile.eof() )
	{
	i++;
	
	//readout of data - elastic case
	infile >> a >> b >> c >> d >> e >> f >> j >>
	LabAngle[i] >> LabEnergy[i] >> h >> k >> l >> m >> n;
//	cout << "read file a=" << a << G4endl;
	//readout of data - inelastic case
//	infile >> a >> b >> c >> d >> e >> f >> j >>
//	LabAngle[i] >> LabEnergy[i] >> h >> k >> l >> m;

	//readout of data - transfer case
//	infile >> LabAngle[i] >> LabEnergy[i] >> a >> b;
	

	}
	
//Read cross section file

       TString kine2 = WorkDir+"/input/kine/c12_400_long.dat";
       ifstream infile_xsec(kine2.Data());

	i = -1;
	while( !infile_xsec.eof() )
	{
	i++;
	infile_xsec >> T_xsec[i] >> CrossSection_t[i];	//readout of data	
	cout << i << " " << T_xsec[i] << " " << CrossSection_t[i] <<  endl;
	nbins = i;
	}	
//Int_Tegral of cross section
    for(i=0;i<nbins;i++){
	  Integral = Integral + CrossSection_t[i];
		} 
	cout << " Integral " << Integral << endl;

//Integrated cross section - probability
   Icross_section[0] = CrossSection_t[0]/Integral;
	 cout << "Cross_section[0] " << CrossSection_t[0]  << endl;
	 cout << "Icross_section[0] " <<  Icross_section[0] << endl;
		 
   for(i=1;i<nbins;i++){	 
	  Icross_section[i] = Icross_section[i-1] + CrossSection_t[i]/Integral;
		cout << "i" << i << "Icross_section[i]" <<  Icross_section[i]   << endl;
		} 
	 
}


R3BReadKinematics::~R3BReadKinematics(){
  //
  // Destructor
  //
}
