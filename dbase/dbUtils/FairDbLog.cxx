/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLog.h"
#include <cstring>

FairDbLog::LogLevel_t FairDbLog::GetLevelCode(const char* level)
{
  if      (strcasecmp(level,"Verbose")  == 0) { return FairDbLog::kVerbose; }
  else if (strcasecmp(level,"Debug")    == 0) { return FairDbLog::kDebug; }
  else if (strcasecmp(level,"Info")     == 0) { return FairDbLog::kInfo; }
  else if (strcasecmp(level,"Synopsis") == 0) { return FairDbLog::kSynopsis; }
  else if (strcasecmp(level,"Warning")  == 0) { return FairDbLog::kWarning; }
  else if (strcasecmp(level,"Error")    == 0) { return FairDbLog::kError; }
  else if (strcasecmp(level,"Fatal")    == 0) { return FairDbLog::kFatal; }
  return -1;
}

const char* FairDbLog::LevelAsString(int level)
{
  if (level == FairDbLog::kVerbose) { return "Verbose"; }
  if (level == FairDbLog::kDebug) { return "Debug"; }
  if (level == FairDbLog::kInfo) { return "Info"; }
  if (level == FairDbLog::kSynopsis) { return "Synopsis"; }
  if (level == FairDbLog::kWarning) { return "Warning"; }
  if (level == FairDbLog::kError) { return "Error"; }
  if (level == FairDbLog::kFatal) { return "Fatal"; }
  return "Unknown?!";
}

int FairDbLog::GetFormatCode(const char* fmt)
{
  if (strcasecmp(fmt,"Priority")==0) { return FairDbLog::kPriority; }
  if (strcasecmp(fmt,"Name")==0) { return FairDbLog::kName; }
  if (strcasecmp(fmt,"Time")==0) { return FairDbLog::kTime; }
  if (strcasecmp(fmt,"File")==0) { return FairDbLog::kFile; }
  if (strcasecmp(fmt,"SVNId")==0) { return FairDbLog::kSVNId; }
  if (strcasecmp(fmt,"Line")==0) { return FairDbLog::kLine; }
  if (strcasecmp(fmt,"Host")==0) { return FairDbLog::kHost; }
  if (strcasecmp(fmt,"PID")==0) { return FairDbLog::kPID; }
  if (strcasecmp(fmt,"Runid")==0) { return FairDbLog::kRunId; }
  if (strcasecmp(fmt,"StackTrace")==0) { return FairDbLog::kStackTrace; }

  if (strcasecmp(fmt,"ColorAll")==0) { return FairDbLog::kColorAll; }
  if (strcasecmp(fmt,"Bold")==0) { return FairDbLog::kBold; }
  if (strcasecmp(fmt,"Dim")==0) { return FairDbLog::kDim; }
  if (strcasecmp(fmt,"Underline")==0) { return FairDbLog::kUnderline; }
  if (strcasecmp(fmt,"Blink")==0) { return FairDbLog::kBlink; }
  if (strcasecmp(fmt,"Reverse")==0) { return FairDbLog::kReverse; }
  if (strcasecmp(fmt,"Black")==0) { return FairDbLog::kBlack; }
  if (strcasecmp(fmt,"Red")==0) { return FairDbLog::kRed; }
  if (strcasecmp(fmt,"Green")==0) { return FairDbLog::kGreen; }
  if (strcasecmp(fmt,"Yellow")==0) { return FairDbLog::kYellow; }
  if (strcasecmp(fmt,"Blue")==0) { return FairDbLog::kBlue; }
  if (strcasecmp(fmt,"Magenta")==0) { return FairDbLog::kMagenta; }
  if (strcasecmp(fmt,"Cyan")==0) { return FairDbLog::kCyan; }
  if (strcasecmp(fmt,"White")==0) { return FairDbLog::kWhite; }
  if (strcasecmp(fmt,"BgBlack")==0) { return FairDbLog::kBgBlack; }
  if (strcasecmp(fmt,"BgRed")==0) { return FairDbLog::kBgRed; }
  if (strcasecmp(fmt,"BgGreen")==0) { return FairDbLog::kBgGreen; }
  if (strcasecmp(fmt,"BgYellow")==0) { return FairDbLog::kBgYellow; }
  if (strcasecmp(fmt,"BgBlue")==0) { return FairDbLog::kBgBlue; }
  if (strcasecmp(fmt,"BgMagenta")==0) { return FairDbLog::kBgMagenta; }
  if (strcasecmp(fmt,"BgCyan")==0) { return FairDbLog::kBgCyan; }
  if (strcasecmp(fmt,"BgWhite")==0) { return FairDbLog::kBgWhite; }
  return -1;
}

