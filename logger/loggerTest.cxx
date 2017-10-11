/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// WARNING : pragma commands to hide boost warning
// TODO : remove these pragma commands when boost will fix this issue in future release

#include <Logger.h>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using namespace fair;

void printEverySeverity()
{
    static int i = 1;

    LOG(nolog) << "nolog message "   << i++;
    LOG(error) << "error message "   << i++;
    LOG(warn)  << "warning message " << i++;
    LOG(state) << "state message "   << i++;
    LOG(info)  << "info message "    << i++;
    LOG(debug) << "debug message "   << i++;
    LOG(debug1) << "debug1 message "   << i++;
    LOG(debug2) << "debug2 message "   << i++;
    LOG(debug3) << "debug3 message "   << i++;
    LOG(debug4) << "debug4 message "   << i++;
    LOG(trace) << "trace message "   << i++;
}

void printAllVerbositiesWithSeverity(Logger::Severity sev)
{
    Logger::SetConsoleSeverity(sev);

    cout << endl << ">>> testing severity '" << Logger::SeverityName(sev) << "' with 'low' verbosity..." << endl;
    Logger::SetVerbosity(Logger::Verbosity::low);
    printEverySeverity();
    cout << endl << ">>> testing severity '" << Logger::SeverityName(sev) << "' with 'medium' verbosity..." << endl;
    Logger::SetVerbosity(Logger::Verbosity::medium);
    printEverySeverity();
    cout << endl << ">>> testing severity '" << Logger::SeverityName(sev) << "' with 'high' verbosity..." << endl;
    Logger::SetVerbosity(Logger::Verbosity::high);
    printEverySeverity();
    cout << endl << ">>> testing severity '" << Logger::SeverityName(sev) << "' with 'veryhigh' verbosity..." << endl;
    Logger::SetVerbosity(Logger::Verbosity::veryhigh);
    printEverySeverity();
}

void silentlyPrintAllVerbositiesWithSeverity(Logger::Severity sev)
{
    Logger::SetConsoleSeverity(sev);

    Logger::SetVerbosity(Logger::Verbosity::low);
    printEverySeverity();
    Logger::SetVerbosity(Logger::Verbosity::medium);
    printEverySeverity();
    Logger::SetVerbosity(Logger::Verbosity::high);
    printEverySeverity();
    Logger::SetVerbosity(Logger::Verbosity::veryhigh);
    printEverySeverity();
}

int main()
{
    Logger::SetConsoleColor(true);

    cout << "testing severities..." << endl;

    printAllVerbositiesWithSeverity(Logger::Severity::trace);
    printAllVerbositiesWithSeverity(Logger::Severity::debug4);
    printAllVerbositiesWithSeverity(Logger::Severity::debug3);
    printAllVerbositiesWithSeverity(Logger::Severity::debug2);
    printAllVerbositiesWithSeverity(Logger::Severity::debug1);
    printAllVerbositiesWithSeverity(Logger::Severity::debug);
    printAllVerbositiesWithSeverity(Logger::Severity::info);
    printAllVerbositiesWithSeverity(Logger::Severity::state);
    printAllVerbositiesWithSeverity(Logger::Severity::warn);
    printAllVerbositiesWithSeverity(Logger::Severity::error);
    printAllVerbositiesWithSeverity(Logger::Severity::nolog);

    cout << endl;
    cout << "resetting severity to 'info' and verbosity to 'medium'" << endl;
    Logger::SetConsoleSeverity(Logger::Severity::info);
    Logger::SetVerbosity(Logger::Verbosity::medium);

    cout << "is logging trace: " << fair::Logger::Logging(Logger::Severity::trace) << endl;
    cout << "is logging debug4: " << fair::Logger::Logging(Logger::Severity::debug) << endl;
    cout << "is logging debug3: " << fair::Logger::Logging(Logger::Severity::debug) << endl;
    cout << "is logging debug2: " << fair::Logger::Logging(Logger::Severity::debug) << endl;
    cout << "is logging debug1: " << fair::Logger::Logging(Logger::Severity::debug) << endl;
    cout << "is logging debug: " << fair::Logger::Logging(Logger::Severity::debug) << endl;
    cout << "is logging info: " << fair::Logger::Logging(Logger::Severity::info) << endl;
    cout << "is logging state: " << fair::Logger::Logging(Logger::Severity::state) << endl;
    cout << "is logging warn: " << fair::Logger::Logging(Logger::Severity::warn) << endl;
    cout << "is logging error: " << fair::Logger::Logging(Logger::Severity::error) << endl;
    cout << "is logging fatal: " << fair::Logger::Logging(Logger::Severity::fatal) << endl;
    cout << "is logging nolog: " << fair::Logger::Logging(Logger::Severity::nolog) << endl;

    for (int i = 0; i < 1000000; ++i)
    {
        silentlyPrintAllVerbositiesWithSeverity(Logger::Severity::nolog);
    }
    cout << endl;
    cout << "resetting severity to 'trace' and verbosity to 'veryhigh'" << endl;
    Logger::SetConsoleSeverity(Logger::Severity::trace);
    Logger::SetVerbosity(Logger::Verbosity::veryhigh);

    cout << endl;
    cout << "testing conditional logging..." << endl;
    int x = 0;
    LOG(info) << "x = " << x << " (initial)";
    LOG_IF(info, (x == 0)) << "incrementing x to " << ++x;
    LOG(info) << "x = " << x << " (after increment)";
    LOG_IF(info, (x == 0)) << "this should not be printed and x not incremented: " << ++x;
    LOG(info) << "x = " << x << " (after conditional increment)";

    cout << endl;
    cout << "resetting severity to 'nolog'" << endl;
    Logger::SetConsoleSeverity(Logger::Severity::nolog);

    cout << "----------------------------" << endl;
    cout << "open log file with severity 'error'" << endl;
    Logger::InitFileSink(Logger::Severity::error, "test_log", true);
    printEverySeverity();

    return 0;
}
