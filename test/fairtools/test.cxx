#include "FairLogger.h"
#include <iostream>

int main()
{
  //  std::ios_base::sync_with_stdio(false);
  FairLogger* fLogger = FairLogger::GetLogger();
  fLogger->SetColoredLog(true);
  fLogger->SetLogToFile(true);

  for (int i=0; i < 10; i++) {
    fLogger->Info(MESSAGE_ORIGIN, "Value: %i", i);
    std::cout<<"Das sollte schwarz sein."<<std::endl;
    fLogger->LOG(WarningLog) << "Value: "<< i <<" "<< FairLogger::endl;
    std::cout<<"Das sollte wieder schwarz sein."<<std::endl;
  }
}
