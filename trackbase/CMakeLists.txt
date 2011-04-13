# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${INCLUDE_DIRECTORIES} 
${CLHEP_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/field 
${CMAKE_SOURCE_DIR}/passive
${CMAKE_SOURCE_DIR}/genfit
${CMAKE_SOURCE_DIR}/trackbase
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(TRKBASE_SRCS
FairTrackPar.cxx
FairTrackParP.cxx
FairTrackParH.cxx 
FairGeaneUtil.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${TRKBASE_SRCS}" "${INCLUDE_DIRECTORIES}" TRKBASE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h TRKBASE_HEADERS "${TRKBASE_SRCS}")

set(TRKBASE_LINKDEF TrackBaseLinkDef.h)
set(TRKBASE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/TrackBaseDict.cxx) 

ROOT_GENERATE_DICTIONARY("${TRKBASE_HEADERS}" "${TRKBASE_LINKDEF}" "${TRKBASE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

SET(TRKBASE_SRCS ${TRKBASE_SRCS} ${TRKBASE_DICTIONARY})

add_library(TrkBase SHARED ${TRKBASE_SRCS})
target_link_libraries(TrkBase ${ROOT_LIBRARIES})
set_target_properties(TrkBase PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS TrkBase DESTINATION ${CMAKE_BINARY_DIR}/lib)
