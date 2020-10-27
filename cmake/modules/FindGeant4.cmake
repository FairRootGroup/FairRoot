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

# Add missing include directory properties on Geant4 imported targets
if(Geant4_FOUND AND Geant4_INCLUDE_DIRS AND Geant4_VERSION VERSION_LESS "10.6")
  set(_g4_targets G4analysis G4digits_hits G4error_propagation G4event G4clhep G4zlib G3toG4 G4geometry G4global G4graphics_reps G4intercoms G4interfaces G4materials G4parmodels G4particles G4persistency G4physicslists G4processes G4readout G4run G4track G4tracking G4FR G4vis HepRep G4RayTracer G4Tree G4VRML G4visXXX G4GMocren G4vis_management G4modeling)
  foreach(_g4_target IN LISTS _g4_targets)
    if(TARGET ${_g4_target})
      get_target_property(_g4_incdir ${_g4_target} INTERFACE_INCLUDE_DIRECTORIES)
      if(NOT _g4_incdir)
        set_target_properties(${_g4_target} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${Geant4_INCLUDE_DIRS}")
      endif()
    endif()
  endforeach()
  if(TARGET CLHEP::CLHEP AND TARGET G4global AND Geant4_system_clhep_FOUND)
    set_property(TARGET G4global APPEND PROPERTY
                 INTERFACE_LINK_LIBRARIES CLHEP::CLHEP)
  endif()
endif()
