# Create a library called "FairDbTut" 

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${FAIRROOT_SOURCE_DIR}/example/Tutorial5/src
${FAIRROOT_SOURCE_DIR}/example/mcstack
)

#set(INCLUDE_DIRECTORIES
#${ROOT_INCLUDE_DIR} 
#${CMAKE_SOURCE_DIR}/fairtools
#${CMAKE_SOURCE_DIR}/geobase 
#${CMAKE_SOURCE_DIR}/parbase 
#${CMAKE_SOURCE_DIR}/base 
#${CMAKE_SOURCE_DIR}/rtdb
#${CMAKE_SOURCE_DIR}/dbase 
#${CMAKE_SOURCE_DIR}/dbase/dbInterface
#${CMAKE_SOURCE_DIR}/dbase/dbValidation
#${CMAKE_SOURCE_DIR}/input/db
#${CMAKE_SOURCE_DIR}/dbase/dbInput
#${CMAKE_SOURCE_DIR}/example/Tutorial5/src
#)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(FairDbTut_SRCS
FairDbTutPar.cxx
FairDbTutContFact.cxx
FairDbTutAccessRtdbTask.cxx
)

set(FairDbTut_HEADERS
FairDbTutPar.h
FairDbTutContFact.h
FairDbTutAccessRtdbTask.h
${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbResPtr.h
${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbWriter.h
)



set(FairDbTut_LINKDEF FairDbTutLinkDef.h)
set(FairDbTut_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairDbTutDict.cxx) 

ROOT_GENERATE_DICTIONARY("${FairDbTut_HEADERS}" "${FairDbTut_LINKDEF}" "${FairDbTut_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


set(FairDbTut_SRCS ${FairDbTut_SRCS} ${FairDbTut_DICTIONARY})

add_library(Tutorial5 SHARED ${FairDbTut_SRCS})
target_link_libraries(Tutorial5 ${ROOT_LIBRARIES})
set_target_properties(Tutorial5 PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS Tutorial5 DESTINATION ${CMAKE_BINARY_DIR}/lib)
