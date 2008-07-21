# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${GEANT4VMC_INCLUDE_DIR} 
${GEANT4_INCLUDE_DIR} 
${CLHEP_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/cbmg4
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(CBMG4_SRCS
CbmSpecialStackingAction.cxx
RichTbPhysicsList.cxx
)


# Add CbmRunConfiguration only for old virtual monte carlo
IF(GEANT4_MODULAR_PHYSICS_LIST)
  set (CBMG4_SRCS ${CBMG4_SRCS} CbmRunConfiguration.cxx)

  # fill list of header files from list of source files
  # by exchanging the file extension
  CHANGE_FILE_EXTENSION(*.cxx *.h CBMG4_HEADERS "${CBMG4_SRCS}")

  set(CBMG4_LINKDEF CbmG4LinkDef.h)
  set(CBMG4_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/CbmG4Dict.cxx) 

  ROOT_GENERATE_DICTIONARY("CbmRunConfiguration.h" "${CBMG4_LINKDEF}" "${CBMG4_DICTIONARY}" "${INCLUDE_DIRECTORIES}")
  set(CBMG4_SRCS ${CBMG4_SRCS} ${CBMG4_DICTIONARY})
ENDIF(GEANT4_MODULAR_PHYSICS_LIST)

#if(RULE_CHECKER_FOUND)
#  CHECK_RULES("${CBMG4_SRCS}" "${INCLUDE_DIRECTORIES}" CBMG4_RULES)
#endif(RULE_CHECKER_FOUND)

add_library(CbmG4 SHARED ${CBMG4_SRCS})
target_link_libraries(CbmG4 ${ROOT_LIBRARIES})
set_target_properties(CbmG4 PROPERTIES ${CBMROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS CbmG4 DESTINATION ${CMAKE_BINARY_DIR}/lib)
