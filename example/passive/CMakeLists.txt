# Create a library called "libPassive" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${FAIRROOT_SOURCE_DIR}/fairtools
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

set(SRCS
FairCave.cxx            
FairGeoCave.cxx        
FairGeoMagnet.cxx      
FairGeoPassivePar.cxx  
FairGeoPipe.cxx        
FairGeoTarget.cxx      
FairMagnet.cxx         
FairPassiveContFact.cxx
FairPipe.cxx           
FairTarget.cxx 
)

Set(HEADERS )
Set(LINKDEF PassiveLinkDef.h)
Set(LIBRARY_NAME Passive)
Set(DEPENDENCIES Base GeoBase ParBase Geom Cint Core)

GENERATE_LIBRARY()
