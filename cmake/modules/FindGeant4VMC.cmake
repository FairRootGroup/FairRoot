################################################################################
#    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_package(${CMAKE_FIND_PACKAGE_NAME} CONFIG)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME} HANDLE_COMPONENTS CONFIG_MODE)

# Add missing include directory properties on Geant4vmc imported targets
if(Geant4VMC_FOUND AND Geant4VMC_INCLUDE_DIRS AND TARGET geant4vmc)
  get_target_property(_g4vmc_incdir geant4vmc INTERFACE_INCLUDE_DIRECTORIES)
  if(NOT _g4vmc_incdir)
    set_target_properties(geant4vmc PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Geant4VMC_INCLUDE_DIRS}")
  endif()
endif()

if(Geant4VMC_FOUND)
  set(Geant4VMC_LIBRARY_DIR "${Geant4VMC_DIR}/../../${Geant4VMC_CMAKE_INSTALL_LIBDIR}")
  get_filename_component(Geant4VMC_LIBRARY_DIR ${Geant4VMC_LIBRARY_DIR} ABSOLUTE)
  set(Geant4VMC_SHARE_DIR "${Geant4VMC_DIR}/share")
  find_path(Geant4VMC_MACRO_DIR NAMES g4libs.C PATHS
    ${Geant4VMC_SHARE_DIR}/Geant4VMC-${Geant4VMC_VERSION}/examples/macro
    NO_DEFAULT_PATH
  )
endif()
