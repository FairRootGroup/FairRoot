 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Check if SSE instructions are available on the machine where 
# the project is compiled.

If(CMAKE_SYSTEM_NAME MATCHES Linux)
  Exec_Program(cat ARGS "/proc/cpuinfo" OUTPUT_VARIABLE CPUINFO)
  String(REGEX REPLACE "^.*(sse).*$" "\\1" SSE_THERE ${CPUINFO})
  String(COMPARE EQUAL "sse" "${SSE_THERE}" SSE_TRUE)
ElseIf(CMAKE_SYSTEM_NAME MATCHES Darwin)
  Exec_Program("/usr/sbin/sysctl -n machdep.cpu.features" OUTPUT_VARIABLE CPUINFO)
  String(REGEX REPLACE "^.*(SSE).*$" "\\1" SSE_THERE ${CPUINFO})
  String(COMPARE EQUAL "SSE" "${SSE_THERE}" SSE_TRUE)
EndIf(CMAKE_SYSTEM_NAME MATCHES Linux)

If(SSE_TRUE)
  Set(SSE_FOUND true) 
  MESSAGE(STATUS "SSE extensions available")
Else(SSE_TRUE)
  Set(SSE_FOUND false)
  MESSAGE(STATUS "NO SSE extensions available.")
EndIf(SSE_TRUE)
