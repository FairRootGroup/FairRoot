/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLogOSStream.h"
#include <cstdio>
extern "C" {
#include <unistd.h>
}
#include <cstdlib>
#include <cassert>
#include <cstring>

using namespace std;




ostream& operator<<(ostream& os, const FairDbLogCatStream& m)
{
  vector<string>::const_iterator vend(m.fFileList.end());
  os << m.fOutFile << ":";
  for (vector<string>::const_iterator itrFileName  = m.fFileList.begin();
       itrFileName != vend;
       ++itrFileName) {
    os << " " << *itrFileName;
  }
  os << "\n";
  return os;
}

FairDbLogCatStream::FairDbLogCatStream() : fOutFile("") { }

FairDbLogCatStream::FairDbLogCatStream(const char* fileName) : fOutFile(fileName) { }

FairDbLogCatStream::~FairDbLogCatStream() { }


void FairDbLogCatStream::AddFileToList(const char* filename)
{
  string aName(filename);
  fFileList.push_back(aName);
}


void FairDbLogCatStream::DoConcatenation()
{
  // Open the output file
  ofstream outFile(fOutFile.c_str());
  if (!outFile) {
    cerr << "-E- " << __FILE__ << ":" << __LINE__
         << " Can't open file " << fOutFile
         << " for write."
         << " Concatenation not performed\n";
    return;
  }

  // Append the contents of each file in the list to outFile and
  // delete the file
  vector<string>::iterator vend(fFileList.end());
  for (vector<string>::iterator itrFairDbLogName = fFileList.begin();
       itrFairDbLogName != vend;
       ++itrFairDbLogName) {
    ifstream* inFile;
    inFile = new ifstream(itrFairDbLogName->c_str());
    if ((*inFile)) {
      char ch;
      while (inFile->get(ch)) { outFile.put(ch); }
      delete inFile;
      if ( unlink(itrFairDbLogName->c_str()) != 0) {
        cerr << "-W- " << __FILE__ << ":" << __LINE__
             << "Failed to unlink file '"
             << (*itrFairDbLogName) << "'.\n";
      }
    } else {
      // Input stream didn't open correctly
      cerr << "-E- " << __FILE__ << ":" << __LINE__
           << " Can't open file " << (*itrFairDbLogName)
           << " for read."
           << " File skipped\n";
      continue;
    }
  }
}


void FairDbLogFileOStream::Close()
{
  if (SubtractReference()==0) {
    fOfstream->close();
  }
}

FairDbLogFileOStream::FairDbLogFileOStream(const char* name, openmode mode) :
  fFileName(name)
{
  // Open a file using this name
  fOfstream = new ofstream(fFileName.c_str(), mode);
}

FairDbLogFileOStream::~FairDbLogFileOStream()
{
  // Flush and close the file
  fOfstream->flush();
  fOfstream->close();
  delete fOfstream;
}

const char* FairDbLogFileOStream::GetName() const
{
  return fFileName.c_str();
}

ostream& FairDbLogFileOStream::Os() const
{
  return *fOfstream;
}



FairDbLogOStreamService* FairDbLogOStreamService::fInstance = 0;

FairDbLogOStreamService::~FairDbLogOStreamService()
{
  // Delete all the FairDbLogOStreams pointed to in the table
  map<std::string,FairDbLogOStream*>::iterator mend (fFairDbLogOStreamTable.end());
  for (map<std::string,FairDbLogOStream*>::iterator i = fFairDbLogOStreamTable.begin();
       i != mend;
       ++i) {
    delete i->second;
  }
}

FairDbLogOStream* FairDbLogOStreamService::GetStream(const char* streamName)
{
  // Look for the stream in the stream map
  std::string logStreamName(streamName);
  FairDbLogOStream* logOStream = fFairDbLogOStreamTable[logStreamName];


  if (logOStream == 0) {

    if (!fFairDbLogOStreamMakerList.empty()) {
      list<FairDbLogOStreamMaker_t>::iterator lend(fFairDbLogOStreamMakerList.end());
      for (list<FairDbLogOStreamMaker_t>::iterator itr=fFairDbLogOStreamMakerList.begin();
           itr != lend;
           ++itr) {
        logOStream = (*itr)(streamName);
        if (logOStream) { break; } // Done
      }
    }


    if (!logOStream) {
      if (strcmp(streamName, "cout")==0 ||
          strcmp(streamName, "cerr")==0 ||
          strcmp(streamName, "clog")==0) {
        logOStream = new FairDbLogStandardOStream(streamName);
      }
    }

    if (logOStream == 0) {
      logOStream = new FairDbLogFileOStream(streamName, ios::out);
    }

    assert(logOStream);

    fFairDbLogOStreamTable[logStreamName] = logOStream;
  }

  logOStream->AddReference();

  return logOStream;
}

FairDbLogOStreamService* FairDbLogOStreamService::Instance()
{
  if (fInstance == 0) { fInstance = new FairDbLogOStreamService(); }
  return fInstance;
}

void FairDbLogOStreamService::Register(FairDbLogOStreamMaker_t logOStreamMaker)
{
  fFairDbLogOStreamMakerList.push_front(logOStreamMaker);
}



FairDbLogStandardOStream::FairDbLogStandardOStream(const char* name)
{
  if (strcmp(name,"cout") == 0) { kStream = kCout; return; }
  if (strcmp(name,"cerr") == 0) { kStream = kCerr; return; }
  if (strcmp(name,"clog") == 0) { kStream = kClog; return; }
  abort();
}

const char* FairDbLogStandardOStream::GetName() const
{
  switch (kStream) {
  case kCout:
    return "cout";
  case kCerr:
    return "cerr";
  case kClog:
    return "clog";
  default:
    abort();
  }
  return "";
}

std::ostream& FairDbLogStandardOStream::Os() const
{
  switch (kStream) {
  case kCout:
    return std::cout;
  case kCerr:
    return std::cerr;
  case kClog:
    return std::clog;
  default:
    abort();
    break;
  }
  return std::cerr;
}
