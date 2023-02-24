// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See https://alice-o2.web.cern.ch/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

//****************************************************************************
//* This file is free software: you can redistribute it and/or modify        *
//* it under the terms of the GNU General Public License as published by     *
//* the Free Software Foundation, either version 3 of the License, or        *
//* (at your option) any later version.                                      *
//*                                                                          *
//* Primary Authors: Sandro Wenzel <sandro.wenzel@cern.ch>                   *
//*                                                                          *
//* The authors make no claims about the suitability of this software for    *
//* any purpose. It is provided "as is" without express or implied warranty. *
//****************************************************************************

//  @file   MCStepInterceptor.cxx
//  @author Sandro Wenzel
//  @since  2017-06-29
//  @brief  A LD_PRELOAD logger hooking into Stepping of FairMCApplication's
//  @author Radoslaw Karabowicz
//  @since  2018-10-22
//  @brief  Modified for FairRoot

// NOLINTBEGIN(bugprone-macro-parentheses) false positive
// (re)declare symbols to be able to hook into them
#define DECLARE_INTERCEPT_SYMBOLS(APP)                                                                                 \
    class APP                                                                                                          \
    {                                                                                                                  \
      public:                                                                                                          \
        void Stepping();                                                                                               \
        void FinishEvent();                                                                                            \
        void FinishRun();                                                                                              \
    };
// NOLINTEND(bugprone-macro-parentheses)

DECLARE_INTERCEPT_SYMBOLS(FairMCApplication)

extern "C" void performLogging(FairMCApplication *);
extern "C" void dispatchStepping(FairMCApplication *, char const *libname, char const *);
extern "C" void dispatchFinishEvent(FairMCApplication *, char const *libname, char const *);
extern "C" void dispatchFinishRun(FairMCApplication *, char const *libname, char const *);
extern "C" void flushLog();
extern "C" void flushFinalLog();

#define INTERCEPT_STEPPING(APP, LIB, SYMBOL)                                                                           \
    void APP::Stepping()                                                                                               \
    {                                                                                                                  \
        auto baseptr = reinterpret_cast<FairMCApplication *>(this);                                                    \
        performLogging(baseptr);                                                                                       \
        dispatchStepping(baseptr, LIB, SYMBOL);                                                                        \
    }

#define INTERCEPT_FINISHEVENT(APP, LIB, SYMBOL)                                                                        \
    void APP::FinishEvent()                                                                                            \
    {                                                                                                                  \
        auto baseptr = reinterpret_cast<FairMCApplication *>(this);                                                    \
        flushLog();                                                                                                    \
        dispatchFinishEvent(baseptr, LIB, SYMBOL);                                                                     \
    }

#define INTERCEPT_FINISHRUN(APP, LIB, SYMBOL)                                                                          \
    void APP::FinishRun()                                                                                              \
    {                                                                                                                  \
        auto baseptr = reinterpret_cast<FairMCApplication *>(this);                                                    \
        flushFinalLog();                                                                                               \
        dispatchFinishRun(baseptr, LIB, SYMBOL);                                                                       \
    }

// the runtime will now dispatch to these functions due to LD_PRELOAD
INTERCEPT_STEPPING(FairMCApplication, "libBase", "_ZN17FairMCApplication8SteppingEv")
INTERCEPT_FINISHEVENT(FairMCApplication, "libBase", "_ZN17FairMCApplication11FinishEventEv")
INTERCEPT_FINISHRUN(FairMCApplication, "libBase", "_ZN17FairMCApplication9FinishRunEv")
