

#include <iostream>

#include "TSQLServer.h"
#include "TSQLStatement.h"

#include "FairDbException.h"

using namespace std;

ClassImp(FairDbException)


FairDbException::FairDbException(const char* msg /*= 0*/,
                                 Int_t code      /* = -1 */,
                                 Int_t dbType    /*= -1 */ ):
  fMessage(msg),
  fErrorCode(code),
  fDbType(dbType)
{


}


FairDbException::FairDbException(const TSQLServer& server,
                                 Int_t dbType    /*= -1 */ ):
  fMessage(server.GetErrorMsg()),
  fErrorCode(server.GetErrorCode()),
  fDbType(dbType)
{


}


FairDbException::FairDbException(const TSQLStatement& statement,
                                 Int_t dbType    /*= -1 */ ):
  fMessage(statement.GetErrorMsg()),
  fErrorCode(statement.GetErrorCode()),
  fDbType(dbType)
{


}



FairDbException::FairDbException(const FairDbException& that)
  : fMessage(that.fMessage),
    fErrorCode(that.fErrorCode),
    fDbType(that.fDbType)
{


  *this = that;

}



FairDbException::~FairDbException()
{


}


std::ostream& operator<<(std::ostream& os, const FairDbException& e)
{

  os << "Error " << e.GetErrorCode()
     << " (" << e.GetMessage() << ") from DB type " << e.GetDbType() << endl;
  return os;

}
