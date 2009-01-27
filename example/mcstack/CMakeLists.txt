# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/example/mcstack 
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${CMAKE_SOURCE_DIR}/base
${CMAKE_SOURCE_DIR}/example/mcstack

)
 
link_directories( ${LINK_DIRECTORIES})

set(MCSTACK_SRCS
FairStack.cxx 
FairMCTrack.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${MCSTACK_SRCS}" "${INCLUDE_DIRECTORIES}" MCSTACK_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h MCSTACK_HEADERS "${MCSTACK_SRCS}")
SET( MCSTACK_HEADERS ${MCSTACK_HEADERS} FairDetectorList.h )

set(MCSTACK_LINKDEF  MCStackLinkDef.h)
set(MCSTACK_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairMCStackDict.cxx) 

ROOT_GENERATE_DICTIONARY("${MCSTACK_HEADERS}" "${MCSTACK_LINKDEF}" "${MCSTACK_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

SET(MCSTACK_SRCS ${MCSTACK_SRCS} ${MCSTACK_DICTIONARY})

add_library(MCStack SHARED ${MCSTACK_SRCS})
target_link_libraries(MCStack ${ROOT_LIBRARIES})
set_target_properties(MCStack PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS MCStack DESTINATION ${CMAKE_BINARY_DIR}/lib)
