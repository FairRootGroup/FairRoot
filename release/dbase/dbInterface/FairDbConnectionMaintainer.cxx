

#include "FairDbMultConnector.h"
#include "FairDbConnectionMaintainer.h"

ClassImp(FairDbConnectionMaintainer)

FairDbConnectionMaintainer::FairDbConnectionMaintainer(FairDbMultConnector* cascader) : fCascader(cascader)
{


  //  fCascader = cascader;
  if ( fCascader ) { fCascader->HoldConnections(); }

}


FairDbConnectionMaintainer::~FairDbConnectionMaintainer()
{

  if ( fCascader ) { fCascader->ReleaseConnections(); }


}

