 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find PYTHIA8 instalation
# Once done this will define
# PYTHIA8_INCLUDE_DIR     where to locate Pythia.h file
# PYTHIA8_LIBRARY         where to find the libpythia8 library
# PYTHIA8_<lib>_LIBRARY   Addicional libraries
# PYTHIA8_LIBRARIES       (not cached) the libraries to link against to use Pythia8
# PYTHIA8_FOUND           if false, you cannot build anything that requires Pythia8
# PYTHIA8_VERSION         version of Pythia8 if found
################################################################################

set(_pythia8dirs
    ${PYTHIA8}
    $ENV{PYTHIA8}
    ${PYTHIA8_DIR}
    $ENV{PYTHIA8_DIR}
    $ENV{PYTHIA_ROOT}
    ${AlFa_DIR}
    ${SIMPATH}
    ${SIMPATH}/generators
    /usr
    /opt/pythia8)

find_path(PYTHIA8_INCLUDE_DIR
          NAMES Pythia8/Pythia.h pythia8/Pythia.h  pythia8/pythia.h Pythia8/pythia.h
          HINTS ${_pythia8dirs}
          PATH_SUFFIXES include include/Pythia8 include/pythia8
          DOC "Specify the directory containing Pythia.h.")

if(PYTHIA8_INCLUDE_DIR MATCHES "include$")
  get_filename_component(PYTHIA8_PREFIX ${PYTHIA8_INCLUDE_DIR}/.. ABSOLUTE)
elseif()
  get_filename_component(PYTHIA8_PREFIX ${PYTHIA8_INCLUDE_DIR}/../.. ABSOLUTE)
endif()

find_library(PYTHIA8_LIBRARY
             NAMES pythia8 Pythia8
             HINTS ${_pythia8dirs}
             PATH_SUFFIXES lib
             DOC "Specify the Pythia8 library here.")

find_path(PYTHIA8_LIB_DIR  NAMES libpythia8.so libpythia8.dylib PATHS
               $ENV{PYTHIA_ROOT}/lib
               ${PYTHIA8_DIR}/lib
               ${AlFa_DIR}/lib
               ${SIMPATH}/lib
               ${SIMPATH}/generators/lib
               NO_DEFAULT_PATH
             )

find_library(PYTHIA8_hepmcinterface_LIBRARY
             NAMES hepmcinterface pythia8tohepmc
             HINTS ${_pythia8dirs}
             PATH_SUFFIXES lib)

find_library(PYTHIA8_lhapdfdummy_LIBRARY
             NAMES lhapdfdummy
             HINTS ${_pythia8dirs}
             PATH_SUFFIXES lib)


find_path(PYTHIA8DATA
  NAMES MainProgramSettings.xml
  HINTS
  ${PYTHIA8_PREFIX}/share/Pythia8/xmldoc
  ${PYTHIA8_PREFIX}/share/pythia8/xmldoc)

foreach(_lib PYTHIA8_LIBRARY PYTHIA8_hepmcinterface_LIBRARY PYTHIA8_lhapdfdummy_LIBRARY)
  if(${_lib})
    set(PYTHIA8_LIBRARIES ${PYTHIA8_LIBRARIES} ${${_lib}})
  endif()
endforeach()
set(PYTHIA8_INCLUDE_DIRS ${PYTHIA8_INCLUDE_DIR} ${PYTHIA8_INCLUDE_DIR}/Pythia8 )

# handle the QUIETLY and REQUIRED arguments and set PYTHIA8_FOUND to TRUE if
# all listed variables are TRUE

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia8 DEFAULT_MSG PYTHIA8_INCLUDE_DIR PYTHIA8_LIBRARY PYTHIA8DATA)
mark_as_advanced(PYTHIA8_INCLUDE_DIR PYTHIA8_LIBRARY PYTHIA8_hepmcinterface_LIBRARY PYTHIA8_lhapdfdummy_LIBRARY)
