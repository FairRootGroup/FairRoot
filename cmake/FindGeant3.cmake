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
  get_target_property(geant3_include geant321 INTERFACE_INCLUDE_DIRECTORIES)
  string(REPLACE ":" ";" geant3_include ${geant3_include})
  list(GET geant3_include 0 geant3_include)
  get_filename_component(Geant3_PREFIX ${geant3_include}/../.. ABSOLUTE)
  unset(geant3_include)

  find_path(Geant3_SYSTEM_DIR NAMES data
    HINTS
    "${Geant3_PREFIX}/share/geant3"
    "${Geant3_PREFIX}/share/Geant3-${Geant3_VERSION}"
    NO_DEFAULT_PATH)
endif()
