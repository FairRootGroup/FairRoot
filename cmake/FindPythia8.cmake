################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_path(Pythia8_INCLUDE_DIR
  NAMES Pythia.h pythia.h
  PATH_SUFFIXES include/Pythia8 include/pythia8)

if(Pythia8_INCLUDE_DIR)
  get_filename_component(Pythia8_PREFIX ${Pythia8_INCLUDE_DIR}/../.. ABSOLUTE)
endif()

find_library(Pythia8_LIBRARY
  NAMES pythia8 Pythia8)

find_library(PYTHIA8_hepmcinterface_LIBRARY
  NAMES hepmcinterface pythia8tohepmc)

find_library(PYTHIA8_lhapdfdummy_LIBRARY
  NAMES lhapdfdummy)

find_path(Pythia8_DATA
  NAMES MainProgramSettings.xml
  HINTS
  ${Pythia8_PREFIX}/share/Pythia8/xmldoc
  ${Pythia8_PREFIX}/share/pythia8/xmldoc)

find_file(Pythia8_VERSION_FILE
  NAMES Pythia.h pythia.h
  HINTS ${Pythia8_INCLUDE_DIR})

if(Pythia8_VERSION_FILE)
  file(READ "${Pythia8_VERSION_FILE}" __version_raw)
  string(REGEX MATCH "#define PYTHIA_VERSION ([0-9\.]+)"
    __version_raw "${__version_raw}"
  )
  set(Pythia8_VERSION "${CMAKE_MATCH_1}")
  unset(__version_raw)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8
  REQUIRED_VARS Pythia8_INCLUDE_DIR Pythia8_LIBRARY Pythia8_DATA
  VERSION_VAR Pythia8_VERSION)

if(Pythia8_FOUND)
  if(NOT TARGET Pythia8)
    add_library(Pythia8 UNKNOWN IMPORTED)
    set_target_properties(Pythia8 PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${Pythia8_INCLUDE_DIR}
      IMPORTED_LOCATION ${Pythia8_LIBRARY})
  endif()
endif()
