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

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})


# add the dictionary to the list of source files
#SET(FAIRTOOLS_SRCS ${FAIRTOOLS_SRCS} ${FAIRTOOLS_DICTIONARY})


############### build the library #####################
add_executable(_TestFairTools _TestFairTools.cxx)
target_link_libraries(_TestFairTools ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest)

#file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
#add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
#target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} pthread)

add_test(_TestFairTools ${FAIRROOT_BINARY_DIR}/bin/_TestFairTools)
