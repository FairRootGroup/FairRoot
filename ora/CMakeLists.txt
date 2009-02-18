# Create a library called "libOra" which includes the source files given in
# the array. The pc files are preproccessed by oracle to generate the needed
# cxx files


set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
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
${ORACLE_LIBRARY_DIR}
) 

link_directories( ${LINK_DIRECTORIES})

set(Ora_input_files
FairDetParOraIo.pc  
FairGenericParOraIo.pc  
FairOraConn.pc  
FairOraInfo.pc
)

CHANGE_FILE_EXTENSION(*.pc *.cxx ORA_SRCS "${Ora_input_files}")
FOREACH(_actual_file ${ORA_SRCS})
  SET(Full_path ${Full_path} ${CMAKE_CURRENT_BINARY_DIR}/${_actual_file})
ENDFOREACH(_actual_file ${ORA_SRCS})
SET(ORA_SRCS ${Full_path} FairParOraIo.cxx FairOraRunInfo.cxx)

CHANGE_FILE_EXTENSION(*.pc *.h ORA_HEADERS "${Ora_input_files}")
set(ORA_HEADERS ${ORA_HEADERS} FairParOraIo.h FairOraRunInfo.h)

PREPROCESS_ORACLE_FILES("${Ora_input_files}" "${INCLUDE_DIRECTORIES}")

set(ORA_LINKDEF OraLinkDef.h)
set(ORA_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/CbmOraDict.cxx)
 
ROOT_GENERATE_DICTIONARY("${ORA_HEADERS}" "${ORA_LINKDEF}" "${ORA_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

set(ORA_SRCS ${ORA_SRCS} ${ORA_DICTIONARY})

add_library(Ora SHARED ${ORA_SRCS})
target_link_libraries(Ora ${ROOT_LIBRARIES} ${ORACLE_LIBRARIES})
set_target_properties(Ora PROPERTIES  ${FAIRROOT_LIBRARY_PROPERTIES})

################ install ###################
install(TARGETS Ora  DESTINATION ${CMAKE_BINARY_DIR}/lib)
