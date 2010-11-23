#include "Riostream.h"
void Read_Memory_File(TString inputFile, Int_t Interval) {
//  Read data from the memeory_consumption_<pid>.txt file
// and create a root file with an ntuple.
//Author: Florian Uhlig
      

// This file has one colum with the time and 10 colums with the data
// The time is the real time which has to be converted into the time
// difference between the actual and the first measurement.
// To make things simple for the begining the time interval is given
// as parameter and all new measurements have time=#measurement*Interval 

   ifstream in;
   in.open(inputFile.Data());

   Int_t  vmPeak,vmSize,vmLck,vmHWM,vmRSS,vmData,vmStk,vmExe,vmLib,vmPTE;
   Int_t time;
   TString dummy[11];
   Int_t nlines = 0;

   TString outputFile(inputFile);
   outputFile.ReplaceAll(".txt",".root");
   TFile *f = new TFile(outputFile,"RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file",
         "time:vmPeak:vmSize:vmLck:vmHWM:vmRSS:vmData:vmStk:vmExe:vmLib:vmPTE");

   // Read and skip the first colum which contains only the header
      in >> dummy[0] >> dummy[1] >> dummy[2] >> dummy[3] >> dummy[4] >> dummy[5] >> dummy[6] >> dummy[7] 
         >> dummy[8] >> dummy[9] >> dummy[10];

   while (1) {
      in >> dummy[0] >> vmPeak >> dummy[1] >> vmSize >> dummy[2] >> vmLck >> dummy[3] >> vmHWM >> dummy[4] >> vmRSS >> 
            dummy[5] >> vmData >> dummy[6] >> vmStk >> dummy[7] >> vmExe >> dummy[8] >> vmLib >>    dummy[9] >> vmPTE >> 
            dummy[10];
      time=nlines*Interval;
      if (!in.good()) break;
      ntuple->Fill(time,vmPeak,vmSize,vmLck,vmHWM,vmRSS,vmData,vmStk,vmExe,vmLib,vmPTE);
      nlines++;
   }
   printf(" found %d measurements\n",nlines);

   in.close();

   f->Write();
}