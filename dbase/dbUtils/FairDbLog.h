/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOG_H
#define FAIRDBLOG_H


class FairDbLog
{
  public:
    //
    // Define the various print levels for messages
    //

    typedef int LogLevel_t;
    static const LogLevel_t kMinLogLevel = 0;
    static const LogLevel_t kVerbose     = 0;
    static const LogLevel_t kDebug       = 1;
    static const LogLevel_t kSynopsis    = 2;
    static const LogLevel_t kInfo        = 3;
    static const LogLevel_t kWarning     = 5;
    static const LogLevel_t kError       = 6;
    static const LogLevel_t kFatal       = 7;
    static const LogLevel_t kNLogLevel   = 8;

    //
    // Define format flags for messages
    //

    static const int kPriority = 0x01; // The message's priority (=I=, =E= etc..)
    static const int kName     = 0x02; // The stream's name
    static const int kTime     = 0x04; // A time stamp for the message
    static const int kFile     = 0x08; // The file the message came from
    static const int kSVNId    = 0x10; // SVN revision information for the file
    static const int kLine     = 0x20; // Line number from the file
    static const int kHost     = 0x40; // Hostname
    static const int kPID      = 0x80; // Process ID
    static const int kRunId    = 0x100; // Run and snarl number
    static const int kStackTrace=0x200; // Add a stack trace on every message.


    //
    // Define some Colors!
    //

    static const int kColorAll  =0x1000;
    static const int kBlack     =0x100000;
    static const int kRed       =0x200000;
    static const int kGreen     =0x300000;
    static const int kYellow    =0x400000;
    static const int kBlue      =0x500000;
    static const int kMagenta   =0x600000;
    static const int kCyan      =0x700000;
    static const int kWhite     =0x800000;
    static const int kBgBlack   =0x1000000;
    static const int kBgRed     =0x2000000;
    static const int kBgGreen   =0x3000000;
    static const int kBgYellow  =0x4000000;
    static const int kBgBlue    =0x5000000;
    static const int kBgMagenta =0x6000000;
    static const int kBgCyan    =0x7000000;
    static const int kBgWhite   =0x8000000;
    static const int kBold      =0x2000;
    static const int kDim       =0x4000;
    static const int kUnderline =0x8000;
    static const int kBlink     =0x10000;
    static const int kReverse   =0x20000;
    static const int kFgColorMask =0xF00000;
    static const int kBgColorMask =0xF000000;
    // Mask out all color bits.
    static const int kFontMask = 0xFFF0000;

    static LogLevel_t GetLevelCode(const char* level);
    static const char* LevelAsString(int level);
    static int        GetFormatCode(const char* fmt);
  private:
    FairDbLog(); // No instances allowed
};

#endif // FAIRDBLOG_H
