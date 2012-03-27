# Create a library called "libEventDisplay" 
# 06.12.07  M. Al-Turany

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${GEANT3_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/trackbase 
${CMAKE_SOURCE_DIR}/geane
${CMAKE_SOURCE_DIR}/eventdisplay
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(EVEDISP_SRCS
FairEventManager.cxx  
FairMCTracks.cxx
FairEventManagerEditor.cxx
FairMCTracksEditor.cxx
FairBoxSet.cxx
FairBoxSetDraw.cxx
FairBoxSetEditor.cxx
FairPointSetDraw.cxx
FairMCPointDraw.cxx
FairHitDraw.cxx
FairHitPointSetDraw.cxx
FairTimeStampPointDraw.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${EVEDISP_SRCS}" "${INCLUDE_DIRECTORIES}" EVEDISP_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h EVEDISP_HEADERS "${EVEDISP_SRCS}")

set(EVEDISP_LINKDEF EventDisplayLinkDef.h)
set(EVEDISP_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/EventDisplayDict.cxx) 

ROOT_GENERATE_DICTIONARY("${EVEDISP_HEADERS}" "${EVEDISP_LINKDEF}" "${EVEDISP_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


set(EVEDISP_SRCS ${EVEDISP_SRCS} ${EVEDISP_DICTIONARY})

add_library(EventDisplay SHARED ${EVEDISP_SRCS})
target_link_libraries(EventDisplay ${ROOT_LIBRARIES})
set_target_properties(EventDisplay PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS EventDisplay DESTINATION ${CMAKE_BINARY_DIR}/lib)
