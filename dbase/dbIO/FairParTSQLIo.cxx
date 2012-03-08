/***************************************
 * Author: M.Babai (M.Babai@rug.nl)    *
 * License:                            *
 * Version:                            *
 ***************************************/
#include "FairParTSQLIo.h"

ClassImp(FairParTSQLIo)

/**
 * Default constructor.
 */
FairParTSQLIo::FairParTSQLIo()
  : fDefaultDb (-1),
    fConnections( new FairDbMultConnector() )
{
  std::cout << "\t<DEBUG_INFO>FairParTSQLIo::FairParTSQLIo()\n";
}

/**
 *@param cons FairDbMultConnector which holds a number of
 * initialized db connections.
 *@param dbNum The number of the db which is selected to act as the
 * master for the current operations.
 */
FairParTSQLIo::FairParTSQLIo(FairDbMultConnector const& cons, int const dbNum)
  : fDefaultDb (dbNum),
    fConnections(new FairDbMultConnector(cons))
{
  std::cout << "\t<DEBUG_INFO>FairParTSQLIo::FairParTSQLIo()12\n";
}

/**
 * Destructor
 */
FairParTSQLIo::~FairParTSQLIo()
{
  disconnect();
}

/**
 *@return True if the connection is alive.
 */
bool FairParTSQLIo::check()
{
  //FairDbMultConnector::Status s;
  int stat = -100;
  // Check if at least one DB is connected.
  if(fDefaultDb != -1) { // Has been specified.
    stat = fConnections->GetStatus(fDefaultDb);
    if(stat == FairDbMultConnector::kFailed ||
        stat == FairDbMultConnector::kClosed)
      std::cerr << "<Error> The connection to specified default Database"
                << " is not alive.\n";
  } else { // No selection
    for(size_t db = 0; db < fConnections->GetNumDb(); ++db) {
      stat = fConnections->GetStatus(db);
    }
  }
  return kTRUE;
  //return ( stat == FairDbMultConnector::kOpen);
}

/**
 * creates the specified I/O.
 *@param ioName The name of IO to be created/added in the IO list.
 */
void FairParTSQLIo::setDetParIo(Text_t* ioName)
{
  if (fConnections) {
    TObject* io = detParIoList->FindObject(ioName);
    // If does not exist
    if(!io) {
      if (strcmp(ioName, "FairGenericParIo") == 0) {
        io = new FairGenericParTSQLIo();
      }
      if (io) {
        detParIoList->Add(io);
      }
    }
  }
}

/**
 * Destroy the connection.
 */
void FairParTSQLIo::disconnect()
{
  if(fConnections) {
    delete fConnections;
    fConnections = 0;
  }
}

bool FairParTSQLIo::activateDetIo()
{
  if(!fConnections) { // FIXME FIXME
    return false;
  }
  FairDetParIo* io=new FairGenericParTSQLIo();
  detParIoList->Add(io);
  return true;
}

/**
 * Print some info. This function maybe removed in future.
 */
void FairParTSQLIo::print()
{
  if (fConnections) {
    std::cout << "<INFO> Number of available DBs = " << fConnections->GetNumDb()
              << std::endl;

    TIter next(detParIoList);
    FairDetParIo* io;
    std::cout << " Number of detector I/Os = " << detParIoList->GetSize()
              << "\nDetector IO list:\n";

    while ((io=(FairDetParIo*)next())) {
      std::cout<<" "<<io->GetName();
    }//while
    std::cout << std::endl;
  }//if
}//print
