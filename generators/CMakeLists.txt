# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

# Check for gcc version, since for gcc 4 one has to add friend-injection
# as option to compile FairPlutoGenerator
EXEC_PROGRAM( gcc ARGS "-dumpversion" OUTPUT_VARIABLE GCC_VERSION )
STRING(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]" "\\1" req_gcc_major_vers "${GCC_VERSION}")
STRING(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]" "\\1" req_gcc_minor_vers "${GCC_VERSION}")
IF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")
  SET_SOURCE_FILES_PROPERTIES(FairPlutoGenerator.cxx PROPERTIES COMPILE_FLAGS
  "-ffriend-injection")
ENDIF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")



set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR}
${PLUTO_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/field 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/generators 
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${PLUTO_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(GENERATORS_SRCS
FairAsciiGenerator.cxx    
FairBoxGenerator.cxx      
FairIonGenerator.cxx      
FairParticleGenerator.cxx 
FairShieldGenerator.cxx   
FairPlutoGenerator.cxx    
FairUrqmdGenerator.cxx    
FairEvtGenGenerator.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${GENERATORS_SRCS}" "${INCLUDE_DIRECTORIES}" GENERATORS_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h GENERATORS_HEADERS "${GENERATORS_SRCS}")

set(GENERATORS_LINKDEF GenLinkDef.h)
set(GENERATORS_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairGenDict.cxx) 

ROOT_GENERATE_DICTIONARY("${GENERATORS_HEADERS}" "${GENERATORS_LINKDEF}" "${GENERATORS_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


set(GENERATORS_SRCS ${GENERATORS_SRCS}  ${GENERATORS_DICTIONARY})


add_library(Gen SHARED ${GENERATORS_SRCS})
target_link_libraries(Gen ${ROOT_LIBRARIES} Pluto)
set_target_properties(Gen PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS Gen DESTINATION ${CMAKE_BINARY_DIR}/lib)
