# Create a library called "libParbase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(PARBASE_SRCS
FairContFact.cxx       
FairDetParAsciiFileIo.cxx    
FairDetParIo.cxx         
FairDetParRootFileIo.cxx     
FairGenericParAsciiFileIo.cxx     
FairGenericParRootFileIo.cxx     
FairParAsciiFileIo.cxx   
FairParGenericSet.cxx   
FairParIo.cxx  
FairParRootFileIo.cxx 
FairParSet.cxx 
FairParamList.cxx  
FairRtdbRun.cxx  
FairRuntimeDb.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${PARBASE_SRCS}" "${INCLUDE_DIRECTORIES}" PARBASE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h PARBASE_HEADERS "${PARBASE_SRCS}")


set(PARBASE_LINKDEF   ParBaseLinkDef.h)
set(PARBASE_DICTIONARY  ${CMAKE_CURRENT_BINARY_DIR}/ParBaseDict.cxx) 
ROOT_GENERATE_DICTIONARY("${PARBASE_HEADERS}" "${PARBASE_LINKDEF}" "${PARBASE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


# add the dictionary to the list of source files
SET(PARBASE_SRCS ${PARBASE_SRCS} ${PARBASE_DICTIONARY}) 


add_library(ParBase SHARED ${PARBASE_SRCS})
target_link_libraries(ParBase ${ROOT_LIBRARIES})
set_target_properties(ParBase PROPERTIES ${CBMROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS ParBase DESTINATION ${CMAKE_BINARY_DIR}/lib)
