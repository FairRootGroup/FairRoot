 ################################################################################
 #    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/examples/advanced/propagator/src
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/trackbase
  ${FairLogger_INCDIR}
)

set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${Geant3_INCLUDE_DIRS}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

link_directories(${LINK_DIRECTORIES})

set(SRCS
  FairTutPropContFact.cxx
  FairTutPropDet.cxx
  FairTutPropGeo.cxx
  FairTutPropGeoPar.cxx
  FairTutPropPoint.cxx
  FairTutPropTr.cxx
)

set(HEADERS
  FairTutPropContFact.h
  FairTutPropDet.h
  FairTutPropGeo.h
  FairTutPropGeoPar.h
  FairTutPropPoint.h
  FairTutPropTr.h
)

set(LINKDEF TutPropLinkDef.h)
set(LIBRARY_NAME PropagatorExample)
set(DEPENDENCIES
    Base
    GeoBase
    ParBase
    MCStack
    Gen
    TrkBase
)

GENERATE_LIBRARY()
