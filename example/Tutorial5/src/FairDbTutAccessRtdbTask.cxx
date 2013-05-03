#include "FairDbTutAccessRtdbTask.h"

#include "FairDbTutPar.h"               // for FairDbTutPar
#include "FairRunAna.h"                 // for FairRunAna
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "Riosfwd.h"                    // for ostream

#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;

ClassImp(FairDbTutAccessRtdbTask);

void FairDbTutAccessRtdbTask::SetParContainers()
{
  FairRunAna* ana = FairRunAna::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  fTutParDef = (FairDbTutPar*)(rtdb->getContainer("TUTParDefault"));
  fTutParAlt = (FairDbTutPar*)(rtdb->getContainer("TUTParAlternative"));
}

InitStatus FairDbTutAccessRtdbTask::Init()
{
  if (!fTutParDef) {
    std::cout<<"-E- FairDbTutAccessRtdbTask: fTutParDef Container does not exist!"<<std::endl;
    return kERROR;
  }
  if (!fTutParAlt) {
    std::cout<<"-E- FairDbTutAccessRtdbTask: fTutParAlt Container does not exist!"<<std::endl;
    return kERROR;
  }
  return kSUCCESS;

}

InitStatus FairDbTutAccessRtdbTask::ReInit()
{
  SetParContainers();
  return kSUCCESS;
}

void
FairDbTutAccessRtdbTask::Exec(Option_t* opt)
{
  return;
}

void
FairDbTutAccessRtdbTask::Finish()
{
  cout << " -I- FairDbTutAccessRtdbTask::Finish() ***** " << endl;

  fTutParDef->Print();
  fTutParAlt->Print();

  return;
}
