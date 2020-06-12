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

# Add missing include directory properties on Geant3 imported targets
if(Geant3_FOUND AND Geant3_INCLUDE_DIRS AND TARGET geant321)
  get_target_property(_g3_incdir geant321 INTERFACE_INCLUDE_DIRECTORIES)
  if(NOT _g3_incdir)
    set_target_properties(geant321 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Geant3_INCLUDE_DIRS}")
  endif()
endif()

if(Geant3_FOUND)
  set(Geant3_LIBRARY_DIR ${Geant3_DIR}/../../${Geant3_CMAKE_INSTALL_LIBDIR})
  get_filename_component(Geant3_LIBRARY_DIR ${Geant3_LIBRARY_DIR} ABSOLUTE)
  find_path(Geant3_SYSTEM_DIR NAMES data PATHS
           ${Geant3_DIR}/../../share/geant3
           NO_DEFAULT_PATH)
endif()
