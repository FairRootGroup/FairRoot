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

if(Geant4_FOUND AND Geant4_INCLUDE_DIRS)
  # Add missing include directory properties on Geant4 imported targets
  set(_g4_targets G4analysis G4digits_hits G4error_propagation G4event G4clhep G4zlib G3toG4 G4geometry G4global G4graphics_reps G4intercoms G4interfaces G4materials G4parmodels G4particles G4persistency G4physicslists G4processes G4readout G4run G4track G4tracking G4FR G4vis HepRep G4RayTracer G4Tree G4VRML G4visXXX G4GMocren G4vis_management G4modeling)
  foreach(_g4_target IN LISTS _g4_targets)
    if(TARGET ${_g4_target})
      get_target_property(_g4_incdir ${_g4_target} INTERFACE_INCLUDE_DIRECTORIES)
      if(NOT _g4_incdir)
        set_target_properties(${_g4_target} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Geant4_INCLUDE_DIRS}")
      endif()
    endif()
  endforeach()

  list(GET Geant4_INCLUDE_DIRS 0 geant4_include)
  get_filename_component(Geant4_PREFIX ${geant4_include}/../.. ABSOLUTE)
  unset(geant4_include)

  if(NOT Geant4_BINARY_DIR)
    set(Geant4_BINARY_DIR "${Geant4_PREFIX}/bin")
  endif()

  function(geant4_generate_data_config)
    cmake_parse_arguments(PARSE_ARGV 1 A "" "OUTVAR" "")

    if(NOT A_OUTVAR)
      set(A_OUTVAR "Geant4_DATA_CONFIG_SH")
    endif()

    foreach(DATASET ${Geant4_DATASETS})
      string(CONCAT ${A_OUTVAR} ${${A_OUTVAR}}
        "export ${Geant4_DATASET_${DATASET}_ENVVAR}=\"${Geant4_DATASET_${DATASET}_PATH}\"\n")
    endforeach()

    set(${A_OUTVAR} ${${A_OUTVAR}} PARENT_SCOPE)
  endfunction()
endif()
