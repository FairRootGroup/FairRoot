 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairFastSim" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/logger
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/source
  ${CMAKE_SOURCE_DIR}/base/sink
  ${CMAKE_SOURCE_DIR}/geobase
  ${CMAKE_SOURCE_DIR}/parbase
  ${CMAKE_SOURCE_DIR}/alignment
  ${CMAKE_SOURCE_DIR}/base/sim/fastsim
  ${FairLogger_INCDIR}
)


Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${Geant4_INCLUDE_DIRS}
  ${Geant4VMC_INCLUDE_DIRS}
)

Include_Directories(${INCLUDE_DIRECTORIES})

Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Geant4_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

# List of source files
set(SRCS
        FairFastSimulation.cxx
        FairFastSimModel.cxx
	      FairFastSimRunConfiguration.cxx
        FairFastSimDetector.cxx
)

Set(DEPENDENCIES
      ParBase GeoBase FairTools
      Proof GeomPainter Geom VMC EG MathCore Physics
      Matrix Tree Hist RIO RHTTP Core geant4vmc G4processes
)

Set(LINKDEF FastSimLinkDef.h)
Set(LIBRARY_NAME FairFastSim)

GENERATE_LIBRARY()
