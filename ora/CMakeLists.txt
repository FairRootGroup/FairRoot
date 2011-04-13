# Create a library called "libOra" which includes the source files given in
# the array. The pc files are preproccessed by oracle to generate the needed
# cxx files


set(INCLUDE_DIRECTORIES
${INCLUDE_DIRECTORIES} 
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/ora
${CMAKE_SOURCE_DIR}/parbase
${CMAKE_SOURCE_DIR}/base
${ORACLE_HOME}/precomp/public
${ORACLE_HOME}/rdbms/public
${ORACLE_HOME}/rdbms/demo
${ORACLE_HOME}/plsql/public
${ORACLE_HOME}/network/public
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(Ora_input_files
FairDetParOraIo.pc  
FairGenericParOraIo.pc  
FairOraConn.pc  
FairOraInfo.pc
)

PREPROCESS_ORACLE_FILES("${Ora_input_files}" "${INCLUDE_DIRECTORIES}")

CHANGE_FILE_EXTENSION(*.pc *.cxx ORA_SRCS "${Ora_input_files}")
CHANGE_FILE_EXTENSION(*.pc *.h ORA_HEADERS "${Ora_input_files}")

set(ORA_HEADERS ${ORA_HEADERS} FairOraRunInfo.h FairParOraIo.h)


set(ORA_LINKDEF OraLinkDef.h)
set(ORA_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/CbmOraDict.cxx)
 
ROOT_GENERATE_DICTIONARY("${ORA_HEADERS}" "${ORA_LINKDEF}" "${ORA_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

set(ORA_SRCS ${ORA_SRCS} ${ORA_DICTIONARY})

add_library(Ora SHARED ${ORA_SRCS})
target_link_libraries(Ora ${ROOT_LIBRARIES})
#set_target_properties(Ora PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS Ora  DESTINATION ${CMAKE_BINARY_DIR}/lib)
