/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGOSTREAM_H
#define FAIRDBLOGOSTREAM_H

#include <iostream>
#include <iosfwd>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <map>

using namespace std;


class FairDbLogOStream
{
  public:
    FairDbLogOStream() : fNreference(0)       { }
    virtual ~FairDbLogOStream()               { }

    virtual std::ostream& Os()            const = 0;
    virtual const char*   GetName()       const = 0;
    int                   GetNreference() const { return fNreference; }

    virtual void Close()                { }
    void         Flush()                { Os().flush(); }

    int AddReference()                  { return ++fNreference; }
    int SubtractReference()             { return --fNreference; }
  private:
    int fNreference;

};

class FairDbLogCatStream
{
    friend ostream& operator<<(ostream& os, const FairDbLogCatStream& m);
  public:
    FairDbLogCatStream();
    FairDbLogCatStream(const char* fileName);
    ~FairDbLogCatStream();

    const char* GetOutputFileName() const { return fOutFile.c_str(); }

    void SetOutputFile(const char* filename) {fOutFile = filename; }
    void AddFileToList(const char* filename);
    void DoConcatenation();

  private:
    string         fOutFile;
    vector<string> fFileList;

};


class FairDbLogFileOStream : public FairDbLogOStream
{
  public:
#if __GNUC__ == 3 && __GNUC_MINOR__ >= 4
    typedef ios_base::openmode openmode;
#elif __GNUC__ == 4
    typedef ios_base::openmode openmode;
#else
#ifdef _CPP_BITS_IOSBASE_H
    typedef ios_base::openmode openmode;
#else
    typedef int openmode;
#endif
#endif

    FairDbLogFileOStream() : FairDbLogOStream(), fFileName(""), fOfstream(NULL) { }
    FairDbLogFileOStream(const char* name, openmode mode);
    ~FairDbLogFileOStream();
    const char* GetName() const;
    ostream& Os() const;

    void Close();
  private:
    string    fFileName;
    ofstream* fOfstream;

    FairDbLogFileOStream(const FairDbLogFileOStream&);
    FairDbLogFileOStream operator=(const FairDbLogFileOStream&);
};


class FairDbLogOStreamService
{
  public:
    typedef FairDbLogOStream* (*FairDbLogOStreamMaker_t)(const char*);

    ~FairDbLogOStreamService();

    FairDbLogOStream* GetStream(const char* streamName);
    static FairDbLogOStreamService* Instance();
    void Register(FairDbLogOStreamMaker_t logOStreamMaker);

  private:
    FairDbLogOStreamService() : fFairDbLogOStreamTable(), fFairDbLogOStreamMakerList() { }
    static FairDbLogOStreamService* fInstance;

  private:
    map<string,FairDbLogOStream*> fFairDbLogOStreamTable;
    list<FairDbLogOStreamMaker_t> fFairDbLogOStreamMakerList;
};



class FairDbLogStandardOStream : public FairDbLogOStream
{
  public:
    FairDbLogStandardOStream() : FairDbLogOStream(), kStream(){ }
    FairDbLogStandardOStream(const char* name);
    ~FairDbLogStandardOStream() { }

    const char* GetName() const;
    std::ostream& Os() const;

    void Close() { }
  private:
    typedef enum EStdOStream {
      kUnknownOStream = 0,
      kCout           = 1,
      kCerr           = 2,
      kClog           = 3
    } StdOStream_t;

    StdOStream_t kStream; //
};


#endif // !FAIRDBLOGOSSTREAM
