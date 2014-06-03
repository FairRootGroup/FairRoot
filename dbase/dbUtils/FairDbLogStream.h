/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGSTREAM_H
#define FAIRDBLOGSTREAM_H

#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include "FairDbLog.h"
#include "FairDbLogOSStream.h"
#include "FairDbLogStat.h"


using namespace std;

class FairDbLogBFormat;
class FairDbLogOStream;

class FairDbLogStream
{
    friend ostream& operator<<(ostream& os, const FairDbLogStream& s);
  public:
    FairDbLogStream();
    FairDbLogStream(const char* name);

    bool            IsActive(FairDbLog::LogLevel_t lvl) const { return lvl>=fLogLevel; }
    FairDbLog::LogLevel_t GetLogLevel() const { return fLogLevel; };
    void            PrintStatistics(ostream& os);

    void AttachOStream(FairDbLog::LogLevel_t lvl, const char* name);
    void DetachOStream(FairDbLog::LogLevel_t lvl, const char* name);
    void ConnectOStream(FairDbLog::LogLevel_t lvl, const char* name) {AttachOStream(lvl,name);}
    void DisconnectOStream(FairDbLog::LogLevel_t lvl, const char* name) {DetachOStream(lvl,name);}

    void Close();
    void Flush();
    void AddFormat(FairDbLog::LogLevel_t lvl, int fmt);
    void RemoveFormat(FairDbLog::LogLevel_t lvl, int fmt) { fFormat[lvl]&=(~fmt); }
    void SetLogLevel(FairDbLog::LogLevel_t lvl);
    void SetFormat(FairDbLog::LogLevel_t lvl, int fmt)    { fFormat[lvl] = fmt;   }

    FairDbLogStream& operator()(FairDbLog::LogLevel_t priority, const char* file,
                                const char* svnid, int line);
    void LogPrint(FairDbLog::LogLevel_t priority, const char* file);


    template<class TP> FairDbLogStream& operator<<(const TP& t) {
      if (fCurrentLogLevel >= fLogLevel) {
        vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[fCurrentLogLevel].end());
        for (vector<FairDbLogOStream*>::iterator
             iter(fFairDbLogOStream[fCurrentLogLevel].begin());
             iter != vend;
             ++iter) {
          (*iter)->Os() << t;
        }
      }
      return (*this);
    }


    typedef std::ostream& (*__MSGomanip)(std::ostream&);
    FairDbLogStream& operator<<(__MSGomanip func) {
      if (fCurrentLogLevel >= fLogLevel) {
        vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[fCurrentLogLevel].end());
        for (vector<FairDbLogOStream*>::iterator
             iter(fFairDbLogOStream[fCurrentLogLevel].begin());
             iter != vend;
             ++iter) {
          (*iter)->Os() << func;
        }
      }
      return (*this);
    }

#if ( __GNUC__ >= 3)
    // << operator for ios_base...
    typedef ios_base& (*__MSGios_base)(ios_base&);
    FairDbLogStream& operator<<(__MSGios_base iosb) {
      if (fCurrentLogLevel >= fLogLevel) {
        vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[fCurrentLogLevel].end());
        for (vector<FairDbLogOStream*>::iterator
             iter = fFairDbLogOStream[fCurrentLogLevel].begin();
             iter != vend;
             ++iter) {
          (*iter)->Os() << iosb;
        }
      }
      return (*this);
    }
#else // (__GNUC__ < 3)
    // << operator for manips...
    typedef ios& (*__MSGmanip)(ios&);
    FairDbLogStream& operator<<(__MSGmanip func) {
      if (fCurrentLogLevel >= fLogLevel) {
        vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[fCurrentLogLevel].end());
        for (vector<FairDbLogOStream*>::iterator
             iter(fFairDbLogOStream[fCurrentLogLevel].begin());
             iter != vend;
             ++iter) {
          (*iter)->Os() << func;
        }
      }
      return (*this);
    }
#endif // __GNUC__

  private:
    void Init();
    void StatPrint(ostream& os, const char* label, int n) const;
    void SetCurrentDateString();
    void SetSVNVersion(const char* SVNId);

    enum { kMaxNameSize = 8 };
    char                fName[kMaxNameSize+1];        // Name of this FairDbLogStream
    FairDbLog::LogLevel_t     fLogLevel;                    // Threshold for print
    int                 fFormat[FairDbLog::kNLogLevel];     // Formatting flags
    vector<FairDbLogOStream*> fFairDbLogOStream[FairDbLog::kNLogLevel]; // Output streams
    map<string,FairDbLogStat> fFileStat;          // Print stats by file name

    FairDbLog::LogLevel_t fCurrentLogLevel; // The log level of messages being printed
    char fCurrentDate[32];            // Time stamp for current message
    char fSVNVersion[128];            // SVN version for current message
};

#endif // 

