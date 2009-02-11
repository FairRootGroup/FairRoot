# Create a library called "libTutorial2" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
#put here all directories where header files are located
${FAIRROOT_SOURCE_DIR}/example/Tutorial2/src
${FAIRROOT_SOURCE_DIR}/base
${FAIRROOT_SOURCE_DIR}/example/mcstack
${FAIRROOT_SOURCE_DIR}/parbase
${FAIRROOT_SOURCE_DIR}/geobase
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(TUTORIAL2_SRCS
#Put here your sourcefiles
FairTutorialDet.cxx
FairTutorialDetContFact.cxx
FairTutorialDetGeo.cxx
FairTutorialDetGeoPar.cxx
FairTutorialDetPoint.cxx
FairTutorialDetDigiPar.cxx
FairTutorialDetDigitizer.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h TUTORIAL2_HEADERS "${TUTORIAL2_SRCS}")

set(TUTORIAL2_LINKDEF Tutorial2LinkDef.h)
set(TUTORIAL2_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairTutorial2Dict.cxx) 

ROOT_GENERATE_DICTIONARY("${TUTORIAL2_HEADERS}" "${TUTORIAL2_LINKDEF}" "${TUTORIAL2_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

set(TUTORIAL2_SRCS ${TUTORIAL2_SRCS} ${TUTORIAL2_DICTIONARY})

add_library(Tutorial2 SHARED ${TUTORIAL2_SRCS})
target_link_libraries(Tutorial2 ${ROOT_LIBRARIES})
set_target_properties(Tutorial2 PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS Tutorial2 DESTINATION ${CMAKE_BINARY_DIR}/lib)
