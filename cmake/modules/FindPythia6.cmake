################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_library(Pythia6_LIBRARY
  NAMES Pythia6 pythia6
  HINTS "${PYTHIA6_ROOT}" "${Pythia6_LIBRARY_DIR}"
  PATH_SUFFIXES lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Pythia6
  REQUIRED_VARS Pythia6_LIBRARY
)

if(Pythia6_FOUND)
  get_filename_component(Pythia6_LIBRARY_DIR ${Pythia6_LIBRARY} DIRECTORY)
  set(PYTHIA6_LIBRARY_DIR ${Pythia6_LIBRARY_DIR}) # legacy

  if(NOT TARGET Pythia6)
    add_library(Pythia6 UNKNOWN IMPORTED)
    set_target_properties(Pythia6 PROPERTIES
      IMPORTED_LOCATION ${Pythia6_LIBRARY}
    )
  endif()
endif()
