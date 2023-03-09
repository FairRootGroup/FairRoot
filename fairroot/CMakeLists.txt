################################################################################
# Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(alignment)
add_subdirectory(base)

if(Geant4_FOUND AND Geant4VMC_FOUND)
  add_subdirectory(fastsim)
endif()

add_subdirectory(geobase)
add_subdirectory(parbase)
add_subdirectory(generators)

if(BUILD_MBS)
  add_subdirectory(mbsapi)
endif()
if(BUILD_ONLINE)
  add_subdirectory(online)
endif()

if(Geant3_FOUND)
 add_subdirectory(geane)
 add_subdirectory(trackbase)
endIf()

if(ROOT_opengl_FOUND)
  add_subdirectory(eventdisplay)
else()
  message(STATUS "eventdisplay will not be built, because ROOT has no opengl support.")
endif()

if(Geant3_FOUND AND Geant4VMC_FOUND AND yaml-cpp_FOUND)
  add_subdirectory(mcconfigurator)
endif()

add_subdirectory(datamatch)

if(BUILD_BASEMQ)
  add_subdirectory(fairmq)
  add_subdirectory(basemq)
  add_subdirectory(parmq)
endif()
