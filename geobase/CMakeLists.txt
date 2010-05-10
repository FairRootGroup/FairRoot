# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR} 
)
 
link_directories( ${LINK_DIRECTORIES})


set(GEOBASE_SRCS

FairGeoAssembly.cxx
FairGeoCone.cxx	
FairGeoCons.cxx 
FairGeoEltu.cxx 
FairGeoBuilder.cxx  
FairGeoInterface.cxx  
FairGeoIo.cxx  
FairGeoLoader.cxx  
FairGeoMatrix.cxx 
FairGeoMedia.cxx	 
FairGeoMedium.cxx 
FairGeoNode.cxx 
FairGeoOldAsciiIo.cxx 
FairGeoPcon.cxx  
FairGeoPgon.cxx 
FairGeoRootBuilder.cxx  
FairGeoRotation.cxx 
FairGeoSet.cxx  
FairGeoShapes.cxx 
FairGeoSphe.cxx  
FairGeoTransform.cxx 
FairGeoTrap.cxx	
FairGeoTrd1.cxx 
FairGeoTube.cxx  
FairGeoTubs.cxx  
FairGeoTorus.cxx 
FairGeoVector.cxx  
FairGeoVolume.cxx 
FairGeoCompositeVolume.cxx 
FairGeoAsciiIo.cxx	
FairGeoBrik.cxx 
FairGeoBasicShape.cxx 
 
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${GEOBASE_SRCS}" "${INCLUDE_DIRECTORIES}" GEOBASE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h GEOBASE_HEADERS "${GEOBASE_SRCS}")


set(GEOBASE_LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/GeoBaseLinkDef.h) 
set(GEOBASE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FairGeoDict.cxx) 
ROOT_GENERATE_DICTIONARY("${GEOBASE_HEADERS}" "${GEOBASE_LINKDEF}" "${GEOBASE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


# add the dictionary to the list of source files
SET(GEOBASE_SRCS ${GEOBASE_SRCS} ${GEOBASE_DICTIONARY}) 


add_library(GeoBase SHARED ${GEOBASE_SRCS})
target_link_libraries(GeoBase ${ROOT_LIBRARIES})
set_target_properties(GeoBase PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS GeoBase DESTINATION ${CMAKE_BINARY_DIR}/lib)
