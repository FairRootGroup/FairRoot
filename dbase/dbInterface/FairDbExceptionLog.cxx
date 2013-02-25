
#include <iostream>

#include "FairDbExceptionLog.h"

using namespace std;

ClassImp(FairDbExceptionLog)

FairDbExceptionLog FairDbExceptionLog::fgGELog;


FairDbExceptionLog::FairDbExceptionLog(const FairDbException* e)
  : fEntries()
{

  if ( e ) { this->AddEntry(*e); }

}


FairDbExceptionLog::~FairDbExceptionLog()
{



}


std::ostream& operator<<(std::ostream& os, const FairDbExceptionLog& el)
{

  if ( el.IsEmpty() ) {
    os << "The database exception log is empty" << endl;
  } else {
    os << "Database exception log:-" << endl;
    std::vector<FairDbException>::const_iterator itr(el.GetEntries().begin()),
        itrEnd(el.GetEntries().end());
    while ( itr != itrEnd ) {
      os << *itr << endl;
      ++itr;
    }
  }

  return os;

}


void FairDbExceptionLog::AddLog(const FairDbExceptionLog& el)
{

  const std::vector<FairDbException>& ve = el.GetEntries();
  std::vector<FairDbException>::const_iterator itr(ve.begin()), itrEnd(ve.end());
  while ( itr != itrEnd ) { this->AddEntry(*itr++); }

}


void FairDbExceptionLog::Copy(FairDbExceptionLog& that, UInt_t start) const
{

  UInt_t maxEntry = fEntries.size();
  while (start <= maxEntry ) { that.AddEntry(fEntries[start++]); }

}

void FairDbExceptionLog::Print () const
{
  return;
  std::cout << *this << std::endl;

}



