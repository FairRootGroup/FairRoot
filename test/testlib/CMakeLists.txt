 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTest" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

# Boost is needed for the regular expression handling
# Need static boost libraries to link executable with path to library
Set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost COMPONENTS unit_test_framework)

set(INCLUDE_DIRECTORIES
 ${CMAKE_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})

############### build the library #####################
add_library(FairTest SHARED FairTestOutputHandler.cxx FairCaptureOutputNew.cxx )
target_link_libraries(FairTest Boost::unit_test_framework)

