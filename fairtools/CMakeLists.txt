# Create a library called "libFairTools" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR} 
 ${CMAKE_SOURCE_DIR}/fairtools
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

 
# Really lazy version to get the list of source files
# Take all source file in the given source dir
#FILE(GLOB FAIRTOOLS_SRCS ${CMAKE_CURRENT_SOURCE_DIR} *.cxx)

# List of source files
set(FAIRTOOLS_SRCS
   FairLogger.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${FAIRTOOLS_SRCS}" "${INCLUDE_DIRECTORIES}" FAIRTOOLS_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h FAIRTOOLS_HEADERS "${FAIRTOOLS_SRCS}")

# set everything needed for the root dictonary and create the
# dictionary
set(FAIRTOOLS_LINKDEF FairToolsLinkDef.h )
set(FAIRTOOLS_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairToolsDict.cxx) 
ROOT_GENERATE_DICTIONARY("${FAIRTOOLS_HEADERS}" "${FAIRTOOLS_LINKDEF}" "${FAIRTOOLS_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

# add the dictionary to the list of source files
SET(FAIRTOOLS_SRCS ${FAIRTOOLS_SRCS} ${FAIRTOOLS_DICTIONARY}) 


############### build the library #####################
add_library(FairTools SHARED ${FAIRTOOLS_SRCS})
target_link_libraries(FairTools ${ROOT_LIBRARIES})
set_target_properties(FairTools PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

############### install the library ###################
install(TARGETS FairTools DESTINATION ${CMAKE_BINARY_DIR}/lib)
