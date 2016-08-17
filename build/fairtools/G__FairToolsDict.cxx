// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIfairtoolsdIG__FairToolsDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FairLogger.h"
#include "FairMonitor.h"
#include "FairSystemInfo.h"

// Header files passed via #pragma extra_include

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairLogger*)
   {
      ::FairLogger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairLogger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairLogger", ::FairLogger::Class_Version(), "invalid", 90,
                  typeid(::FairLogger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairLogger::Dictionary, isa_proxy, 4,
                  sizeof(::FairLogger) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairLogger*)
   {
      return GenerateInitInstanceLocal((::FairLogger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairLogger*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMonitor*)
   {
      ::FairMonitor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMonitor >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMonitor", ::FairMonitor::Class_Version(), "invalid", 278,
                  typeid(::FairMonitor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMonitor::Dictionary, isa_proxy, 4,
                  sizeof(::FairMonitor) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMonitor*)
   {
      return GenerateInitInstanceLocal((::FairMonitor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMonitor*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairSystemInfo(void *p = 0);
   static void *newArray_FairSystemInfo(Long_t size, void *p);
   static void delete_FairSystemInfo(void *p);
   static void deleteArray_FairSystemInfo(void *p);
   static void destruct_FairSystemInfo(void *p);
   static void streamer_FairSystemInfo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairSystemInfo*)
   {
      ::FairSystemInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairSystemInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairSystemInfo", ::FairSystemInfo::Class_Version(), "invalid", 380,
                  typeid(::FairSystemInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairSystemInfo::Dictionary, isa_proxy, 16,
                  sizeof(::FairSystemInfo) );
      instance.SetNew(&new_FairSystemInfo);
      instance.SetNewArray(&newArray_FairSystemInfo);
      instance.SetDelete(&delete_FairSystemInfo);
      instance.SetDeleteArray(&deleteArray_FairSystemInfo);
      instance.SetDestructor(&destruct_FairSystemInfo);
      instance.SetStreamerFunc(&streamer_FairSystemInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairSystemInfo*)
   {
      return GenerateInitInstanceLocal((::FairSystemInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairLogger::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairLogger::Class_Name()
{
   return "FairLogger";
}

//______________________________________________________________________________
const char *FairLogger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairLogger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairLogger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairLogger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLogger*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMonitor::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMonitor::Class_Name()
{
   return "FairMonitor";
}

//______________________________________________________________________________
const char *FairMonitor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMonitor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMonitor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMonitor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMonitor*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairSystemInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairSystemInfo::Class_Name()
{
   return "FairSystemInfo";
}

//______________________________________________________________________________
const char *FairSystemInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairSystemInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairSystemInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairSystemInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSystemInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairLogger::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairLogger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairLogger::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairLogger::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::FairLogger

//______________________________________________________________________________
void FairMonitor::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMonitor.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMonitor::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMonitor::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::FairMonitor

//______________________________________________________________________________
void FairSystemInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairSystemInfo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b.CheckByteCount(R__s, R__c, FairSystemInfo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairSystemInfo::IsA(), kTRUE);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairSystemInfo(void *p) {
      return  p ? new(p) ::FairSystemInfo : new ::FairSystemInfo;
   }
   static void *newArray_FairSystemInfo(Long_t nElements, void *p) {
      return p ? new(p) ::FairSystemInfo[nElements] : new ::FairSystemInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairSystemInfo(void *p) {
      delete ((::FairSystemInfo*)p);
   }
   static void deleteArray_FairSystemInfo(void *p) {
      delete [] ((::FairSystemInfo*)p);
   }
   static void destruct_FairSystemInfo(void *p) {
      typedef ::FairSystemInfo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairSystemInfo(TBuffer &buf, void *obj) {
      ((::FairSystemInfo*)obj)->::FairSystemInfo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairSystemInfo

namespace ROOT {
   static TClass *vectorlEchargR_Dictionary();
   static void vectorlEchargR_TClassManip(TClass*);
   static void *new_vectorlEchargR(void *p = 0);
   static void *newArray_vectorlEchargR(Long_t size, void *p);
   static void delete_vectorlEchargR(void *p);
   static void deleteArray_vectorlEchargR(void *p);
   static void destruct_vectorlEchargR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<char>*)
   {
      vector<char> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<char>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<char>", -2, "vector", 457,
                  typeid(vector<char>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEchargR_Dictionary, isa_proxy, 0,
                  sizeof(vector<char>) );
      instance.SetNew(&new_vectorlEchargR);
      instance.SetNewArray(&newArray_vectorlEchargR);
      instance.SetDelete(&delete_vectorlEchargR);
      instance.SetDeleteArray(&deleteArray_vectorlEchargR);
      instance.SetDestructor(&destruct_vectorlEchargR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<char> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<char>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEchargR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<char>*)0x0)->GetClass();
      vectorlEchargR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEchargR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEchargR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char> : new vector<char>;
   }
   static void *newArray_vectorlEchargR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<char>[nElements] : new vector<char>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEchargR(void *p) {
      delete ((vector<char>*)p);
   }
   static void deleteArray_vectorlEchargR(void *p) {
      delete [] ((vector<char>*)p);
   }
   static void destruct_vectorlEchargR(void *p) {
      typedef vector<char> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<char>

namespace {
  void TriggerDictionaryInitialization_G__FairToolsDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/fairtools",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/fairtools/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairToolsDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairLogger;
class FairMonitor;
class FairSystemInfo;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairToolsDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairLogger.h
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#ifndef BASE_FAIRLOGGER_H_
#define BASE_FAIRLOGGER_H_

#include "Rtypes.h"                     // for Bool_t, FairLogger::Class, etc
#include "TMCtls.h"                     // for MT VMC

#include <stdarg.h>                     // for va_list
#include <fstream>                      // for ostream, operator<<, etc
#include <string>                       // for operator<<
#include <vector>                       // for vector

class FairLogger;

#define IMP_CONVERTTOSTRING(s)  # s
#define CONVERTTOSTRING(s)      IMP_CONVERTTOSTRING(s)
#define MESSAGE_ORIGIN          __FILE__, CONVERTTOSTRING(__LINE__), __FUNCTION__

#define LOG_LEVEL(level) \
  (!(FATAL == level) ? gLogger->GetOutputStream(level, MESSAGE_ORIGIN) : gLogger->GetFATALOutputStream(MESSAGE_ORIGIN))

#define LOG(level)        \
  !(gLogger->IsLogNeeded(level)) ? gLogger->GetNullStream(level) : LOG_LEVEL(level)

#define LOG_IF(level, condition) \
  !(condition) ? gLogger->GetNullStream(level) : LOG(level)

// Definiton of the different log levels
// TODO(F.U): Find bettter names for DEBUG1..4
enum FairLogLevel {FATAL, ERROR, WARNING, INFO,
                   DEBUG, DEBUG1, DEBUG2, DEBUG3, DEBUG4
                  };

static const char* const LogLevelString[] = { "FATAL", "ERROR", "WARNING",
    "INFO", "DEBUG", "DEBUG1",
    "DEBUG2", "DEBUG3", "DEBUG4"
                                            };
enum FairLogColor {
  /* Normal Text */
  Fair_Color_Normal = 0,

  /* Foreground Color */
  Fair_Color_ForegroundBlack   = 0x1,
  Fair_Color_ForegroundRed     = 0x2,
  Fair_Color_ForegroundGreen   = 0x3,
  Fair_Color_ForegroundYellow  = 0x4,
  Fair_Color_ForegroundBlue    = 0x5,
  Fair_Color_ForegroundMagenta = 0x6,
  Fair_Color_ForegroundCyan    = 0x7,
  Fair_Color_ForegroundWhite   = 0x8,
  Fair_Color_ForegroundMask    = 0xF,
};


static const char* const LogLevelColor[] = { "\33[01;31m", "\33[01;33m",
    "\33[00;33m", "\33[01;33m",
    "\33[01;32m", "\33[01;32m",
    "\33[01;32m", "\33[01;32m",
    "\33[01;32m"
                                           };

// Definition of the different verbosity levels of the output
// With the level HIGH the output contains a time stamp, the location from
// which the message commes (File, Function and Line) toegether with the
// log level and the mesage to be printed.
// The verbosity level MEDIUM has the above information without the time stamp
// The LOW verbosity level prints only the log level together with the message
enum FairLogVerbosityLevel {verbosityHIGH, verbosityMEDIUM, verbosityLOW};
static const char* const LogVerbosityString[] = { "HIGH", "MEDIUM", "LOW" };

class FairLogger : public std::ostream
{
  public:
    static FairLogger* GetLogger();

    void SetLogFileName(const char* name);

    void SetLogToScreen(Bool_t log1) {
      fLogToScreen = log1;
      if (!fLogToScreen) {
        SetLogScreenLevel("FATAL");
      }
    }

    void SetLogToFile(Bool_t log1) {
      fLogToFile = log1;
      if (!fLogToFile) {
        SetLogFileLevel("FATAL");
      }
    }

    void SetColoredLog(Bool_t log1) { fLogColored = log1; }

    void SetLogFileLevel(const char* level) {
      fLogFileLevel = ConvertToLogLevel(level);
      SetMinLogLevel();
    }

    void SetLogScreenLevel(const char* level) {
      fLogScreenLevel = ConvertToLogLevel(level);
      SetMinLogLevel();
    }

    void SetLogVerbosityLevel(const char* vlevel) {
      fLogVerbosityLevel = ConvertToLogVerbosityLevel(vlevel);
    }

    Bool_t IsLogNeeded(FairLogLevel logLevel);

    void Fatal(const char* file, const char* line, const char* func,
               const char* format, ...);


    void Error(const char* file, const char* line, const char* func,
               const char* format, ...);

    void Warning(const char* file, const char* line, const char* func,
                 const char* format, ...);

    void Info(const char* file, const char* line, const char* func,
              const char* format, ...);

    void Debug(const char* file, const char* line, const char* func,
               const char* format, ...);
    void Debug1(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug2(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug3(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug4(const char* file, const char* line, const char* func,
                const char* format, ...);

    FairLogger& GetOutputStream(FairLogLevel level, const char* file, const char* line, const char* func);
    FairLogger& GetFATALOutputStream(const char* file, const char* line, const char* func);

    std::ostream& GetNullStream(FairLogLevel level) {
      fLevel=level;
      return *fNullStream;
    }

    void SetScreenStreamToCerr(bool errorStream);

    /*! \brief Stream an object to the output stream
     */
    template <class T> FairLogger&   operator<<(const T& t) {
      if (fLogToScreen && fLevel <= fLogScreenLevel) {
        *(fScreenStream) << t;
      }
      if (fLogToFile && fLevel <= fLogFileLevel) {
        *(fFileStream) << t;
      }
      return *this;
    }

    /*! \brief Pass the ios_base manipulators
     */
#if (__GNUC__ >= 3)
    FairLogger&                      operator<<(std::ios_base & (*manip) (std::ios_base&));
#endif
    FairLogger&                      operator<<(std::ostream & (*manip) (std::ostream&));

    /*! \brief End of the line
     */
    static std::ostream&        endl(std::ostream&);

    /*! \brief Flush the streams
     */
    static std::ostream&        flush(std::ostream&);

  private:
#if !defined(__CINT__)
    static TMCThreadLocal FairLogger* instance;
#else
    static                FairLogger* instance;
#endif

    FairLogger();
    FairLogger(const FairLogger&);
    FairLogger operator=(const FairLogger&);
    ~FairLogger();


    void Log(FairLogLevel level, const char* file, const char* line,
             const char*, const char* format, va_list  arglist);

    void LogFatalMessage(std::ostream& strm);

    void OpenLogFile();
    void CloseLogFile();

    FairLogLevel ConvertToLogLevel(const char* level) const;
    FairLogVerbosityLevel ConvertToLogVerbosityLevel(const char* level) const;

    void GetTime();

    void SetMinLogLevel();

    const char* ConvertLogLevelToString(FairLogLevel level) const
    { return LogLevelString[level]; }

    const char* fLogFileName;
    Bool_t fLogToScreen;
    Bool_t fLogToFile;
    Bool_t fLogColored;
    FairLogLevel fLogFileLevel;
    FairLogLevel fLogScreenLevel;
    FairLogVerbosityLevel fLogVerbosityLevel;
    Int_t fBufferSize;
    Int_t fBufferSizeNeeded;
    std::vector<char> fDynamicBuffer;
    char* fBufferPointer;

    static const int fgkTimeBufferLength = 80;
    char fTimeBuffer[fgkTimeBufferLength];
    FairLogLevel fMinLogLevel;
    FairLogLevel fLevel;
    std::ostream* fScreenStream;
    std::ostream* fFileStream;
    std::ostream* fNullStream;
    Bool_t fLogFileOpen;
    Bool_t fIsNewLine;
    ClassDef(FairLogger, 3)
};

#define gLogger (FairLogger::GetLogger())

#endif  // BASE_FAIRLOGGER_H_
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairMonitor.h
 *
 *  Created on: Aug 01, 2015
 *      Author: r.karabowicz
 */

#ifndef BASE_FAIRMONITOR_H_
#define BASE_FAIRMONITOR_H_

#include <list>
#include <map>

#include "TNamed.h"
#include "TStopwatch.h"

class TCanvas;
class TFile;
class TList;
class TTask;

class FairMonitor : public TNamed
{
  public:
  static FairMonitor* GetMonitor();

  void EnableMonitor(Bool_t tempBool = kTRUE) { fRunMonitor = tempBool; }

  void StartMonitoring(const TTask* tTask, const char* identStr) {
    StartTimer        (tTask,identStr);
    StartMemoryMonitor(tTask,identStr);
  }
  void  StopMonitoring(const TTask* tTask, const char* identStr) {
    StopTimer        (tTask,identStr);
    StopMemoryMonitor(tTask,identStr);
  }

  void StartTimer(const TTask* tTask, const char* identStr);
  void  StopTimer(const TTask* tTask, const char* identStr);

  void StartMemoryMonitor(const TTask* tTask, const char* identStr);
  void  StopMemoryMonitor(const TTask* tTask, const char* identStr);

  void RecordInfo(const TTask* tTask, const char* identStr, Double_t value);

  void RecordRegister(const char* name, const char* folderName, Bool_t toFile);
  void RecordGetting(const char* name);

  void SetCurrentTask(TTask* tTask) { fCurrentTask = tTask; }

  virtual void Print(Option_t* option = "") const;
  virtual void Draw (Option_t* option = "");

  void PrintTask(TString specString) const;
  void PrintTask(TTask* tempTask, Int_t taskLevel=0) const;
  void DrawHist(TString specString);

  TList* GetHistList() { return fHistList; }

  void StoreHistograms(TFile* tfile);

  private:
    static FairMonitor* instance;
    FairMonitor();
    ~FairMonitor();
    FairMonitor(const FairMonitor&);
    FairMonitor& operator=(const FairMonitor&);

    Bool_t fRunMonitor;

    Double_t fRunTime; 
    Double_t fRunMem;

    std::map<TString, TStopwatch> fTimerMap;
    std::map<TString, Int_t> fMemoryMap;

    TList* fHistList;
    TCanvas* fCanvas;

    Int_t fNoTaskRequired;
    Int_t fNoTaskCreated;

    TTask* fCurrentTask;
    std::multimap<TString, TString> fTaskRequired;
    std::multimap<TString, TString> fTaskCreated;
    std::multimap<TString, TString> fTaskCreatedTemp;
    
    std::map<TString, Int_t> fObjectMap;
    std::map<TString, Int_t> fTaskMap;

    std::map<TString, std::pair<Double_t, Double_t> > fObjectPos;
    std::map<TString, std::pair<Double_t, Double_t> > fTaskPos;
 
    void GetTaskMap(TTask* tempTask);
    void AnalyzeObjectMap(TTask* tempTask);

    ClassDef(FairMonitor, 0)
};

extern FairMonitor* gMonitor;

#endif  // BASE_FAIRMONITOR_H_
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * FairSystemInfo.h
 *
 *  Created on: Mai 18, 2015
 *      Author: f.uhlig
 */

#ifndef BASE_FAIRSYSTEMINFO_H_
#define BASE_FAIRSYSTEMINFO_H_

#include "Rtypes.h"

class FairSystemInfo
{
 public:
  FairSystemInfo() {}
  virtual ~FairSystemInfo() {}

  Float_t GetMaxMemory();
  size_t GetCurrentMemory();  

  ClassDef(FairSystemInfo, 1)
};

#endif  // BASE_FAIRSYSTEMINFO_H_

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairLogger", payloadCode, "@",
"FairMonitor", payloadCode, "@",
"FairSystemInfo", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairToolsDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairToolsDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairToolsDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairToolsDict() {
  TriggerDictionaryInitialization_G__FairToolsDict_Impl();
}
