# Create a library called "libFairTools" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
 ${GTEST_INCLUDE_DIRS} 
 ${CMAKE_SOURCE_DIR}/fairtools
 ${CMAKE_SOURCE_DIR}/test
)

# Boost is needed for the regular expression handling
find_package(Boost)

If(Boost_FOUND)
  Set(INCLUDE_DIRECTORIES
      ${INCLUDE_DIRECTORIES}
      ${Boost_INCLUDE_DIRS}
     )
EndIf(Boost_FOUND)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})
############### build the library #####################
If(Boost_FOUND)
  add_executable(_TestFairTools _TestFairTools.cxx)
  target_link_libraries(_TestFairTools ${ROOT_LIBRARIES} ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest)
  add_test(_TestFairTools ${FAIRROOT_BINARY_DIR}/bin/_TestFairTools)
Else(Boost_FOUND)
  Message(STATUS "Could not build the test executable, because the Boost libraries are misssing.")
EndIf(Boost_FOUND)

add_test(_TestFairTools ${FAIRROOT_BINARY_DIR}/bin/_TestFairTools)
