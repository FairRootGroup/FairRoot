################################################################################
#    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Forward all args of original call to config mode find_package
set(_quiet_arg)
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
  set(_quiet_arg QUIET)
endif()
set(_required_arg)
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
  set(_required_arg REQUIRED)
endif()
set(_exact_arg)
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_EXACT)
  set(_exact_arg REQUIRED)
endif()
set(_components_arg)
set(_optional_components_arg)
foreach(_comp IN LISTS ${CMAKE_FIND_PACKAGE_NAME}_FIND_COMPONENTS)
  if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED_${_comp})
    list(APPEND _components_arg ${_comp})
  else()
    list(APPEND _optional_components_arg ${_comp})
  endif()
endforeach()
set(_components_key)
set(_optional_components_key)
if(_components_arg)
  set(_components_key COMPONENTS)
endif()
if(_optional_components_arg)
  set(_optional_components_key OPTIONAL_COMPONENTS)
endif()

find_package(${CMAKE_FIND_PACKAGE_NAME}
  ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION}
  ${_exact_arg} ${_quiet_arg} ${_required_arg}
  CONFIG
  ${_components_key} ${_components_arg}
  ${_optional_components_key} ${_optional_components_arg}
)

# Add missing include directory properties on Geant4vmc imported targets
if(Geant4VMC_FOUND AND Geant4VMC_INCLUDE_DIRS AND TARGET geant4vmc)
  get_target_property(_g4vmc_incdir geant4vmc INTERFACE_INCLUDE_DIRECTORIES)
  if(NOT _g4vmc_incdir)
    set_target_properties(geant4vmc PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Geant4VMC_INCLUDE_DIRS}")
  endif()
endif()

if(Geant4VMC_FOUND)
  set(Geant4VMC_LIBRARY_DIR "${Geant4VMC_DIR}/${Geant4VMC_CMAKE_INSTALL_LIBDIR}")
  set(Geant4VMC_SHARE_DIR "${Geant4VMC_DIR}/share")
  find_path(Geant4VMC_MACRO_DIR NAMES g4libs.C PATHS
    ${Geant4VMC_SHARE_DIR}/Geant4VMC-${Geant4VMC_VERSION}/examples/macro
    NO_DEFAULT_PATH
  )
endif()
