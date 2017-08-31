################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(NOT GEANT4_ROOT)
  set(GEANT4_ROOT $ENV{GEANT4_ROOT})
endif()

find_package(Geant4 QUIET CONFIG
  HINTS ${GEANT4_ROOT} ${SIMPATH}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Geant4 CONFIG_MODE)

foreach(set ${Geant4_DATASETS})
  if(NOT ${Geant4_DATASET_${set}_ENVVAR})
    message("-- Found Geant4 ${set} data: ${Geant4_DATASET_${set}_PATH} (envvar ${Geant4_DATASET_${set}_ENVVAR})")
  endif()
  set(${Geant4_DATASET_${set}_ENVVAR} ${Geant4_DATASET_${set}_PATH}
    CACHE PATH "Geant4 ${set} data"
  )
endforeach()

if(Geant4_FOUND AND NOT Geant4_LIBRARY_DIR)
  list(GET Geant4_LIBRARIES 0 geant4_library)
  get_target_property(geant4_library_path ${geant4_library} IMPORT_LOCATION)
  get_filename_component(Geant4_LIBRARY_DIR ${geant4_library_path} DIRECTORY)
  set(Geant4_LIBRARY_DIR ${Geant4_LIBRARY_DIR} CACHE PATH "Geant4 library path")
endif()

if(Geant4_FOUND)
  list(APPEND LD_LIBRARY_PATH ${Geant4_LIBRARY_DIR})
endif()
