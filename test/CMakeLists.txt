# Create a library called "libFairTest" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

set(INCLUDE_DIRECTORIES
 ${CMAKE_SOURCE_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
)

link_directories( ${LINK_DIRECTORIES})

############### build the library #####################
add_library(FairTest SHARED FairCaptureOutput.cxx FairTestOutputHandler.cxx)
#target_link_libraries(_TestFairTools ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools)

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
#target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} pthread)

#add_test(_TestFairTools ${FAIRROOT_BINARY_DIR}/bin/_TestFairTools)

Add_Subdirectory(fairtools)