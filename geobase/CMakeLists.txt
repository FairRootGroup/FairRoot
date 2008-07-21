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
CbmGeoCone.cxx	
CbmGeoCons.cxx 
CbmGeoEltu.cxx 
CbmGeoBuilder.cxx  
CbmGeoInterface.cxx  
CbmGeoIo.cxx  
CbmGeoLoader.cxx  
CbmGeoMatrix.cxx 
CbmGeoMedia.cxx	 
CbmGeoMedium.cxx 
CbmGeoNode.cxx 
CbmGeoOldAsciiIo.cxx 
CbmGeoPcon.cxx  
CbmGeoPgon.cxx 
CbmGeoRootBuilder.cxx  
CbmGeoRotation.cxx 
CbmGeoSet.cxx  
CbmGeoShapes.cxx 
CbmGeoSphe.cxx  
CbmGeoTransform.cxx 
CbmGeoTrap.cxx	
CbmGeoTrd1.cxx 
CbmGeoTube.cxx  
CbmGeoTubs.cxx  
CbmGeoTorus.cxx 
CbmGeoVector.cxx  
CbmGeoVolume.cxx 
CbmGeoCompositeVolume.cxx 
CbmGeoAsciiIo.cxx	
CbmGeoBrik.cxx 
CbmGeoBasicShape.cxx 
)

if(RULE_CHECKER_FOUND)
  CHECK_RULES("${GEOBASE_SRCS}" "${INCLUDE_DIRECTORIES}" GEOBASE_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h GEOBASE_HEADERS "${GEOBASE_SRCS}")


set(GEOBASE_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/CbmGeoDict.cxx) 
ROOT_GENERATE_DICTIONARY("${GEOBASE_HEADERS}" "${GEOBASE_LINKDEF}" "${GEOBASE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")


# add the dictionary to the list of source files
SET(GEOBASE_SRCS ${GEOBASE_SRCS} ${GEOBASE_DICTIONARY}) 


add_library(GeoBase SHARED ${GEOBASE_SRCS})
target_link_libraries(GeoBase ${ROOT_LIBRARIES})
set_target_properties(GeoBase PROPERTIES ${CBMROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS GeoBase DESTINATION ${CMAKE_BINARY_DIR}/lib)
