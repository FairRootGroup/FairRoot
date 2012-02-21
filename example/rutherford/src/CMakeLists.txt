# Create a library called "libFairRutherford" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
#put here all directories where header files are located
${FAIRROOT_SOURCE_DIR}/fairtools
${FAIRROOT_SOURCE_DIR}/base
${FAIRROOT_SOURCE_DIR}/parbase
${FAIRROOT_SOURCE_DIR}/geobase
${FAIRROOT_SOURCE_DIR}/example/mcstack
${FAIRROOT_SOURCE_DIR}/example/rutherford/src
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(FAIRRUTHERFORD_SRCS
#Put here your sourcefiles
FairRutherford.cxx
FairRutherfordContFact.cxx
FairRutherfordGeo.cxx
FairRutherfordGeoPar.cxx
FairRutherfordPoint.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h FAIRRUTHERFORD_HEADERS "${FAIRRUTHERFORD_SRCS}")

set(FAIRRUTHERFORD_LINKDEF FairRutherfordLinkDef.h)
set(FAIRRUTHERFORD_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairRutherfordDict.cxx) 

ROOT_GENERATE_DICTIONARY("${FAIRRUTHERFORD_HEADERS}" "${FAIRRUTHERFORD_LINKDEF}" "${FAIRRUTHERFORD_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

set(FAIRRUTHERFORD_SRCS ${FAIRRUTHERFORD_SRCS} ${FAIRRUTHERFORD_DICTIONARY})

add_library(FairRutherford SHARED ${FAIRRUTHERFORD_SRCS})
target_link_libraries(FairRutherford ${ROOT_LIBRARIES})
set_target_properties(FairRutherford PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS FairRutherford DESTINATION ${CMAKE_BINARY_DIR}/lib)
