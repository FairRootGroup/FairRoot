################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Order matters! (e.g. base depends on fairtools, so fairtools has to be added first)

add_subdirectory (fairtools)
add_subdirectory (parbase)
add_subdirectory (MbsAPI)
add_subdirectory (geobase)
add_subdirectory (base)
add_subdirectory (generators)
add_subdirectory (eventdisplay)
if(GEANT3_FOUND)
  add_subdirectory (geane)
  add_subdirectory (trackbase)
endif()
add_subdirectory (datamatch)
if(Boost_FOUND AND ZeroMQ_FOUND)
  add_subdirectory (fairmq)
  add_subdirectory (base/MQ)
  add_subdirectory (parmq)
endif()
if(BUILD_DOXYGEN)
  add_subdirectory(doxygen)
endif()
if(BUILD_EXAMPLES)
  add_subdirectory (examples)
endif()
if(BUILD_UNITTESTS AND GTEST_FOUND)
    add_subdirectory(test)
EndIf()
# backwards compatibility to FairSoft
if(NOT SIMPATH)
  set(SIMPATH $ENV{SIMPATH})
endif()
