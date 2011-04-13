# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${GEANT3_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/trackbase 
${CMAKE_SOURCE_DIR}/geane
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})


set(GEANE_SRCS
FairGeane.cxx       
FairGeanePro.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${GEANE_SRCS}" "${INCLUDE_DIRECTORIES}" GEANE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h GEANE_HEADERS "${GEANE_SRCS}")

set(GEANE_LINKDEF GeaneLinkDef.h)
set(GEANE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/GeaneDict.cxx) 

ROOT_GENERATE_DICTIONARY("${GEANE_HEADERS}" "${GEANE_LINKDEF}" "${GEANE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


set(GEANE_SRCS ${GEANE_SRCS} ${GEANE_DICTIONARY})

add_library(Geane SHARED ${GEANE_SRCS})
target_link_libraries(Geane ${ROOT_LIBRARIES})
set_target_properties(Geane PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS Geane DESTINATION ${CMAKE_BINARY_DIR}/lib)
