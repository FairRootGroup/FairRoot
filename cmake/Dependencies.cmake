################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# backwards compatibility to FairSoft
if(NOT SIMPATH)
  set(SIMPATH $ENV{SIMPATH})
endif()

find_package(ROOT 6.10.04 REQUIRED)
find_package(FairLogger 1.1.0 REQUIRED)
find_package(Pythia6)
find_package(Pythia8)
find_package(Pythia8Data)
find_package(Geant3)
find_package(Geant4)
find_package(Geant4VMC)
find_package(VGM)
find_package(IWYU)
find_package(FairMQ 1.2.1)
find_package(Protobuf)
find_package(Msgpack)
find_package(FlatBuffers)
find_package(DDS)
if(NOT DISABLE_GO)
  find_package(Go 1.7)
endif()
if(NOT GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()
find_package(GTest)
if(WITH_DBASE)
  find_package(MYSQL)
  find_package(PGSQL)
  find_package(SQLITE)
endif(WITH_DBASE)

if(Boost_SYSTEM_LIBRARY_RELEASE) # checks for cached boost variable which indicates if Boost is already found
  set(SILENCE_BOOST QUIET)
endif()
find_package(Boost 1.64 ${SILENCE_BOOST}
  COMPONENTS 
  atomic chrono date_time exception filesystem log log_setup program_options
  random regex serialization system thread timer
)
