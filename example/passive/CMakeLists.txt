# Create a library called "libPassive" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/example/passive
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(PASSIVE_SRCS
PndCave.cxx            
PndGeoCave.cxx        
PndGeoMagnet.cxx      
PndGeoPassivePar.cxx  
PndGeoPipe.cxx        
PndGeoTarget.cxx      
PndMagnet.cxx         
PndPassiveContFact.cxx
PndPipe.cxx           
PndTarget.cxx 
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${PASSIVE_SRCS}" "${INCLUDE_DIRECTORIES}" PASSIVE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h PASSIVE_HEADERS "${PASSIVE_SRCS}")

set(PASSIVE_LINKDEF  PassiveLinkDef.h)
set(PASSIVE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/PndPassiveDict.cxx) 

ROOT_GENERATE_DICTIONARY("${PASSIVE_HEADERS}" "${PASSIVE_LINKDEF}" "${PASSIVE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

SET(PASSIVE_SRCS ${PASSIVE_SRCS} ${PASSIVE_DICTIONARY})

add_library(Passive SHARED ${PASSIVE_SRCS})
target_link_libraries(Passive ${ROOT_LIBRARIES})
set_target_properties(Passive PROPERTIES ${CBMROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS Passive DESTINATION ${CMAKE_BINARY_DIR}/lib)
