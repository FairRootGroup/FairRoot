# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
#put here all directories where header files are located
${FAIRROOT_SOURCE_DIR}/fairtools
${FAIRROOT_SOURCE_DIR}/base
#${FAIRROOT_SOURCE_DIR}/<directory which contains the stack>
${FAIRROOT_SOURCE_DIR}/parbase
${FAIRROOT_SOURCE_DIR}/geobase
${FAIRROOT_SOURCE_DIR}/tutorial/NewDetector
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(NEWDETECTOR_SRCS
#Put here your sourcefiles
NewDetector.cxx
NewDetectorContFact.cxx
NewDetectorGeo.cxx
NewDetectorGeoPar.cxx
NewDetectorPoint.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h NEWDETECTOR_HEADERS "${NEWDETECTOR_SRCS}")

set(NEWDETECTOR_LINKDEF NewDetectorLinkDef.h)
set(NEWDETECTOR_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/NewDetectorDict.cxx) 

ROOT_GENERATE_DICTIONARY("${NEWDETECTOR_HEADERS}" "${NEWDETECTOR_LINKDEF}" "${NEWDETECTOR_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

set(NEWDETECTOR_SRCS ${NEWDETECTOR_SRCS} ${NEWDETECTOR_DICTIONARY})

add_library(NewDetector SHARED ${NEWDETECTOR_SRCS})
target_link_libraries(NewDetector ${ROOT_LIBRARIES})
set_target_properties(NewDetector PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS NewDetector DESTINATION ${CMAKE_BINARY_DIR}/lib)
