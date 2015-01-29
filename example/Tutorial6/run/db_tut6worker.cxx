/** 
 *  db_tut6worker.cxx 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 


#include "FairDbMQTutWorker.h"


int main (int argc, char *argv[])
{
  FairDbMQTutWorker  worker;


  TString file_input =  "/tutorial5/macros/ascii-example.par";
  worker.SetIoInput(file_input.Data());

  // SQL Input
  //worker.SetIoInput("sqlio"); 

  TString file_output=  "/tutorial6/data/zmq_test_par.root";
  worker.SetIoOuput(file_output.Data());
  
  // Register the required parameter 
  worker.Register("TUTParDefault"); 


  worker.Run();
	
}
