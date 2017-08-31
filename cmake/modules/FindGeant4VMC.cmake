################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT GEANT4_VMC_ROOT)
  set(GEANT4_VMC_ROOT $ENV{GEANT4_VMC_ROOT})
endif()

# workaround for the fact, that Geant4VMCConfig.cmake sets this variable, patches submitted upstream (Sep 2017)
set(ORIGINAL_CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})

find_package(Geant4VMC QUIET CONFIG
  HINTS ${GEANT4_VMC_ROOT} ${SIMPATH}
)

# workaround for the fact, that Geant4VMCConfig.cmake sets this variable, patches submitted upstream (Sep 2017)
set(CMAKE_INSTALL_LIBDIR ${ORIGINAL_CMAKE_INSTALL_LIBDIR})

find_path(Geant4VMC_MACRO_DIR NAMES g4libs.C
  HINTS
  ${GEANT4_VMC_ROOT}/share/geant4_vmc/macro
  ${SIMPATH}/share/geant4_vmc/macro/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Geant4VMC CONFIG_MODE)

if(Geant4VMC_FOUND AND NOT Geant4VMC_INCLUDE_DIR)
  list(GET Geant4VMC_INCLUDE_DIRS 0 Geant4VMC_INCLUDE_DIR)
  set(Geant4VMC_INCLUDE_DIR ${Geant4VMC_INCLUDE_DIR} CACHE PATH "Geant4VMC include path")
endif()

if(Geant4VMC_FOUND AND NOT Geant4VMC_LIBRARY_DIR)
    list(GET Geant4VMC_LIBRARIES 0 geant4vmc_library)
  get_target_property(geant4vmc_library_path ${geant4vmc_library} IMPORT_LOCATION)
  get_filename_component(Geant4VMC_LIBRARY_DIR ${geant4vmc_library_path} DIRECTORY)
  set(Geant4VMC_LIBRARY_DIR ${Geant4VMC_LIBRARY_DIR} CACHE PATH "Geant4VMC library path")
endif()
