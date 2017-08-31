################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT GEANT3_ROOT)
  set(GEANT3_ROOT $ENV{GEANT3_ROOT})
endif()

# workaround for the fact, that Geant3Config.cmake sets this variable, patches submitted upstream (Sep 2017)
set(ORIGINAL_CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})

find_package(Geant3 QUIET CONFIG
  HINTS ${GEANT3_ROOT} ${SIMPATH}
)

# workaround for the fact, that Geant3Config.cmake sets this variable, patches submitted upstream (Sep 2017)
set(CMAKE_INSTALL_LIBDIR ${ORIGINAL_CMAKE_INSTALL_LIBDIR})

find_path(Geant3_SYSTEM_DIR NAMES data
  HINTS
  ${GEANT3_PATH}/share/geant3
  ${SIMPATH}/share/geant3
)

if(NOT Geant3_SYSTEM_DIR)
  set(Geant3_SYSTEM_DIR ${GEANT3_ROOT} CACHE PATH "Geant3 data files")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Geant3 CONFIG_MODE)

if(Geant3_FOUND AND NOT GEANT3_LIBRARY_DIR)
  get_target_property(Geant3_LIBRARY_PATH ${Geant3_LIBRARIES} IMPORT_LOCATION)
  get_filename_component(Geant3_LIBRARY_DIR ${Geant3_LIBRARY_PATH} DIRECTORY)
  set(GEANT3_LIBRARY_DIR ${GEANT3_LIBRARY_DIR} CACHE PATH "Geant3 library path")
endif()

if(TARGET geant321)
  set_target_properties(geant321 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${Geant3_INCLUDE_DIRS})
endif()

if(Geant3_FOUND)
  list(APPEND LD_LIBRARY_PATH ${Geant3_LIBRARY_DIR})
endif()
