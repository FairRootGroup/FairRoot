 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTools" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
 ${GTEST_INCLUDE_DIRS} 
 ${CMAKE_SOURCE_DIR}/fairtools
 ${CMAKE_SOURCE_DIR}/test/testlib
)

# Boost is needed for the regular expression handling
# Need static boost libraries to link executable with path to library
Set(Boost_USE_STATIC_LIBS TRUE)
find_package(Boost COMPONENTS regex)

If(Boost_FOUND)
  Set(INCLUDE_DIRECTORIES
      ${INCLUDE_DIRECTORIES}
      ${Boost_INCLUDE_DIRS}
     )
EndIf(Boost_FOUND)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
 ${Boost_LIBRARY_DIRS}
)

link_directories( ${LINK_DIRECTORIES})
############### build the test #####################
If(Boost_FOUND)

  add_executable(_GTestFairTools _GTestFairTools.cxx)
  target_link_libraries(_GTestFairTools ${ROOT_LIBRARIES} ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest)
  add_test(_GTestFairTools ${CMAKE_BINARY_DIR}/bin/_GTestFairTools)

  add_executable(_GTestFairToolsNew _GTestFairToolsNew.cxx)
  target_link_libraries(_GTestFairToolsNew ${ROOT_LIBRARIES} ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest)
  add_test(_GTestFairToolsNew ${CMAKE_BINARY_DIR}/bin/_GTestFairToolsNew)

Else(Boost_FOUND)
  Message(STATUS "Could not build the test executable, because the Boost libraries are misssing.")
EndIf(Boost_FOUND)

add_executable(_test test.cxx)
target_link_libraries(_test ${ROOT_LIBRARIES} FairTools)
#target_link_libraries(_test FairTools)
add_test(_test ${CMAKE_BINARY_DIR}/bin/_test)

#If(Boost_FOUND)
#  add_executable(_BoostTestFairTools _BoostTestFairTools.cxx)
#  target_link_libraries(_BoostTestFairTools ${Boost_LIBRARIES} FairTools FairTest)
#  add_test(_BoostTestFairTools ${CMAKE_BINARY_DIR}/bin/_BoostTestFairTools)
#Else(Boost_FOUND)
#  Message(STATUS "Could not build the test executable, because the Boost libraries are misssing.")
#EndIf(Boost_FOUND)



