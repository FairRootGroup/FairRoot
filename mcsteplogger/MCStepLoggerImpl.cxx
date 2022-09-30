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

//  @file   MCStepLoggerImpl.cxx
//  @author Sandro Wenzel
//  @since  2017-06-29
//  @brief  A logging service for MCSteps (hooking into Stepping of FairMCApplication's)
//  @author Radoslaw Karabowicz
//  @since  2018-10-22
//  @brief  Modified for FairRoot

#include <FairMCApplication.h>
#include <TAxis.h>   // for TAxis
#include <TFile.h>   // for TAxis
#include <TH1.h>     // for TH1F
#include <TTree.h>
#include <TVirtualMC.h>
#include <TVirtualMCStack.h>   // for TVirtualMCStack
#include <cassert>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <utility>   // for pair
#ifdef NDEBUG
#undef NDEBUG
#endif

class StepLogger
{
    int stepcounter = 0;

    std::set<int> trackset;
    std::set<int> pdgset;
    std::map<int, int> volumetosteps;
    std::map<int, int> volumetostepsGlobal;
    std::map<int, char const*> idtovolname;

    // TODO: consider writing to a TTree/TFile
  public:
    void addStep(TVirtualMC* mc)
    {
        assert(mc);
        stepcounter++;
        auto stack = mc->GetStack();
        assert(stack);
        trackset.insert(stack->GetCurrentTrackNumber());
        pdgset.insert(mc->TrackPid());
        int copyNo;
        auto id = mc->CurrentVolID(copyNo);
        if (volumetosteps.find(id) == volumetosteps.end()) {
            volumetosteps.insert(std::pair<int, int>(id, 0));
        } else {
            volumetosteps[id]++;
        }
        if (volumetostepsGlobal.find(id) == volumetostepsGlobal.end()) {
            volumetostepsGlobal.insert(std::pair<int, int>(id, 0));
        } else {
            volumetostepsGlobal[id]++;
        }
        if (idtovolname.find(id) == idtovolname.end()) {
            idtovolname.insert(std::pair<int, char const*>(id, mc->CurrentVolName()));
        }
    }

    void clear()
    {
        stepcounter = 0;
        trackset.clear();
        pdgset.clear();
        volumetosteps.clear();
    }

    void flush()
    {
        std::cerr << "did " << stepcounter << " steps \n";
        std::cerr << "transported " << trackset.size() << " different tracks \n";
        std::cerr << "transported " << pdgset.size() << " different types \n";
        // summarize steps per volume
        for (auto& p : volumetosteps) {
            std::cout << " VolName " << idtovolname[p.first] << " COUNT " << p.second << "\n";
        }
        clear();
    }

    void flushFinal()
    {
        // summarize steps per volume
        TFile* stepLoggerFile = TFile::Open("stepLogger.root", "recreate");
        TH1F* stepLoggerHistogram = new TH1F("stepLoggerHistogram",
                                             "Step logger results;volume number;number of steps",
                                             volumetostepsGlobal.size(),
                                             0.5,
                                             volumetostepsGlobal.size() + 0.5);
        uint binNumber = 0;
        for (auto& p : volumetostepsGlobal) {
            std::cout << " VolName " << idtovolname[p.first] << " COUNT " << p.second << "\n";
            stepLoggerHistogram->SetBinContent(++binNumber, p.second);
            stepLoggerHistogram->GetXaxis()->SetBinLabel(binNumber, idtovolname[p.first]);
        }
        stepLoggerHistogram->DrawClone();
        stepLoggerFile->Write();
        stepLoggerFile->Close();
    }
};

StepLogger logger;

// a generic function that can dispatch to the original method of a FairMCApplication
// (for functions of type void FairMCApplication::Method(void); )
// RK: did two versions, because on the first call while Stepping the origMethod was set to avoid calling it over and
// over again RK: but this setting also prevented the FinishEvent ever be calling - instead Stepping was also called
extern "C" void dispatchStepping(FairMCApplication* app, char const* libname, char const* origFunctionName)
{
    typedef void (FairMCApplication::*StepMethodType)();
    static StepMethodType origMethod = nullptr;
    if (origMethod == nullptr) {
        auto libHandle = dlopen(libname, RTLD_NOW);
        // try to make the library loading a bit more portable:
        if (!libHandle) {
            // try appending *.so
            std::stringstream stream;
            stream << libname << ".so";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        if (!libHandle) {
            // try appending *.dylib
            std::stringstream stream;
            stream << libname << ".dylib";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        assert(libHandle);
        void* symbolAddress = dlsym(libHandle, origFunctionName);
        assert(symbolAddress);
        // hack since C++ does not allow casting to C++ member function pointers
        // thanks to gist.github.com/mooware/1174572
        memcpy(&origMethod, &symbolAddress, sizeof(symbolAddress));
    }
    (app->*origMethod)();
}

// a generic function that can dispatch to the original method of a FairMCApplication
// (for functions of type void FairMCApplication::Method(void); )
// RK: did two versions, because on the first call while Stepping the origMethod was set to avoid calling it over and
// over again RK: but this setting also prevented the FinishEvent ever be calling - instead Stepping was also called
extern "C" void dispatchFinishEvent(FairMCApplication* app, char const* libname, char const* origFunctionName)
{
    typedef void (FairMCApplication::*StepMethodType)();
    static StepMethodType origMethod = nullptr;
    if (origMethod == nullptr) {
        auto libHandle = dlopen(libname, RTLD_NOW);
        // try to make the library loading a bit more portable:
        if (!libHandle) {
            // try appending *.so
            std::stringstream stream;
            stream << libname << ".so";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        if (!libHandle) {
            // try appending *.dylib
            std::stringstream stream;
            stream << libname << ".dylib";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        assert(libHandle);
        void* symbolAddress = dlsym(libHandle, origFunctionName);
        assert(symbolAddress);
        // hack since C++ does not allow casting to C++ member function pointers
        // thanks to gist.github.com/mooware/1174572
        memcpy(&origMethod, &symbolAddress, sizeof(symbolAddress));
    }
    (app->*origMethod)();
}

// a generic function that can dispatch to the original method of a FairMCApplication
// (for functions of type void FairMCApplication::Method(void); )
// RK: did two versions, because on the first call while Stepping the origMethod was set to avoid calling it over and
// over again RK: but this setting also prevented the FinishEvent ever be calling - instead Stepping was also called
extern "C" void dispatchFinishRun(FairMCApplication* app, char const* libname, char const* origFunctionName)
{
    typedef void (FairMCApplication::*StepMethodType)();
    static StepMethodType origMethod = nullptr;
    if (origMethod == nullptr) {
        auto libHandle = dlopen(libname, RTLD_NOW);
        // try to make the library loading a bit more portable:
        if (!libHandle) {
            // try appending *.so
            std::stringstream stream;
            stream << libname << ".so";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        if (!libHandle) {
            // try appending *.dylib
            std::stringstream stream;
            stream << libname << ".dylib";
            libHandle = dlopen(stream.str().c_str(), RTLD_NOW);
        }
        assert(libHandle);
        void* symbolAddress = dlsym(libHandle, origFunctionName);
        assert(symbolAddress);
        // hack since C++ does not allow casting to C++ member function pointers
        // thanks to gist.github.com/mooware/1174572
        memcpy(&origMethod, &symbolAddress, sizeof(symbolAddress));
    }
    (app->*origMethod)();
}

extern "C" void performLogging(FairMCApplication* app)
{
    static TVirtualMC* mc = TVirtualMC::GetMC();
    logger.addStep(mc);
}

extern "C" void flushLog() { logger.flush(); }

extern "C" void flushFinalLog() { logger.flushFinal(); }
