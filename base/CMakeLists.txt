# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

 
# Really lazy version to get the list of source files
# Take all source file in the given source dir
#FILE(GLOB BASE_SRCS ${CMAKE_CURRENT_SOURCE_DIR} *.cxx)

# List of source files
set(BASE_SRCS
FairBaseContFact.cxx 
FairBaseParSet.cxx 
FairDetector.cxx 
FairEventHeader.cxx 
FairGenerator.cxx 
FairHit.cxx 
FairIon.cxx 
FairMCApplication.cxx 
FairMCEventHeader.cxx 
FairMCPoint.cxx 
FairModule.cxx 
FairParticle.cxx 
FairPrimaryGenerator.cxx 
FairRootManager.cxx 
FairRun.cxx 
FairRunAna.cxx 
FairRunIdGenerator.cxx 
FairRunSim.cxx 
FairGenericStack.cxx 
FairTask.cxx 
FairTrackParam.cxx 
FairTrajFilter.cxx 
FairVolume.cxx 
FairVolumeList.cxx 
FairField.cxx
FairFieldFactory.cxx
FairVPoint.cxx
FairVTrack.cxx
FairRadLenPoint.cxx
FairRadLenManager.cxx
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${BASE_SRCS}" "${INCLUDE_DIRECTORIES}" BASE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h BASE_HEADERS "${BASE_SRCS}")

# set everything needed for the root dictonary and create the
# dictionary
set(BASE_LINKDEF FairLinkDef.h )
set(BASE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairDict.cxx) 
ROOT_GENERATE_DICTIONARY("${BASE_HEADERS}" "${BASE_LINKDEF}" "${BASE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

# add the dictionary to the list of source files
SET(BASE_SRCS ${BASE_SRCS} ${BASE_DICTIONARY}) 


############### build the library #####################
add_library(Base SHARED ${BASE_SRCS})
target_link_libraries(Base ${ROOT_LIBRARIES})
set_target_properties(Base PROPERTIES ${CBMROOT_LIBRARY_PROPERTIES})

############### install the library ###################
install(TARGETS Base DESTINATION ${CMAKE_BINARY_DIR}/lib)
