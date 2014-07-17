/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/


#include <iostream>

#include "TSQLServer.h"
#include "TSQLStatement.h"
#include "FairDbException.h"
#include "FairDbLogService.h"

using namespace std;

ClassImp(FairDbException)


FairDbException::FairDbException(const char* msg,
                                 Int_t code,
                                 Int_t dbType):
  fMessage(msg),
  fErrorCode(code),
  fDbType(dbType)
{

}


FairDbException::FairDbException(const TSQLServer& server,
                                 Int_t dbType):
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
     << " (" << e.GetMessage() << ") from DB index# " << e.GetDbType() << endl;
  return os;

}
