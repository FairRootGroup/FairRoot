################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

option(WITH_DBASE "Switch off the building of FairDB." OFF)
option(USE_PATH_INFO "Information from PATH and LD_LIBRARY_PATH are used." OFF)
option(BUILD_DOXYGEN "Build Doxygen" OFF)
option(BUILD_EXAMPLES "Build Examples" ON)

option(BUILD_UNITTESTS "Build all unittests and add them as new tests" OFF)
if(${CMAKE_BUILD_TYPE} MATCHES PROFILE)
  set(BUILD_UNITTESTS ON)
endif()
