# Create a library called "libR3BDB" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/db  
${CMAKE_SOURCE_DIR}/db/dbValidation
${CMAKE_SOURCE_DIR}/db/dbInterface
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${CMAKE_SOURCE_DIR}/base
)
 
link_directories( ${LINK_DIRECTORIES})

set(R3BDB_SRCS
dbValidation/Experiment.cxx
dbValidation/Detector.cxx
dbValidation/SimFlag.cxx
dbValidation/ValContext.cxx
dbValidation/ValRange.cxx
dbValidation/ValTimeStamp.cxx
dbValidation/ValValidate.cxx
dbInterface/FairDb.cxx
dbInterface/FairDbConnection.cxx 
dbInterface/FairDbBinaryFile.cxx
dbInterface/FairDbCache.cxx
dbInterface/FairDbConf.cxx
dbInterface/FairDbConfDialog.cxx
dbInterface/FairDbConfigurable.cxx
dbInterface/FairDbConfigSet.cxx
dbInterface/FairDbFieldType.cxx
dbInterface/FairDbTableMetaData.cxx
dbInterface/FairDbMultConnector.cxx
dbInterface/FairDbOutRowStream.cxx
dbInterface/FairDbProxy.cxx
dbInterface/FairDbResult.cxx
dbInterface/FairDbRollbackDates.cxx
dbInterface/FairDbRowStream.cxx
dbInterface/FairDbStatement.cxx
dbInterface/FairDbString.cxx
dbInterface/FairDbTableProxy.cxx
dbInterface/FairDbTableProxyRegistry.cxx
dbInterface/FairDbTableRow.cxx
dbInterface/FairDbTimer.cxx 
dbInterface/FairDbTimerManager.cxx  
dbInterface/FairDbValidityRec.cxx
dbInterface/FairDbValidityRecBuilder.cxx
dbInterface/FairRegistry.cxx
dbInterface/FairRegistryItem.cxx
dbInterface/FairRegistryItemXxx.cxx
dbInterface/FairUtilStream.cxx
dbInterface/FairDbLogEntry.cxx
dbInterface/FairDbConfigStream.cxx
dbInterface/FairDbConnectionMaintainer.cxx
dbInterface/FairDbSqlContext.cxx
dbInterface/FairDbSqlValPacket.cxx
dbInterface/FairDbException.cxx
dbInterface/FairDbExceptionLog.cxx
dbInterface/FairDbServices.cxx
dbInterface/FairDbValRecSet.cxx
dbInterface/FairDbSimFlagAssociation.cxx 
)


if(RULE_CHECKER_FOUND)
CHECK_RULES("${R3BDB_SRCS}" "${INCLUDE_DIRECTORIES}" R3BDB_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h R3BDB_HEADERS "${R3BDB_SRCS}")
SET( R3BDB_HEADERS ${R3BDB_HEADERS} ${CMAKE_SOURCE_DIR}/db/dbInterface/FairDbResPtr.h ${CMAKE_SOURCE_DIR}/db/dbInterface/FairDbWriter.h)

set(R3BDB_LINKDEF  R3BDBLinkDef.h)
set(R3BDB_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/R3BDBDict.cxx)

ROOT_GENERATE_DICTIONARY("${R3BDB_HEADERS}" "${R3BDB_LINKDEF}" "${R3BDB_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

SET(R3BDB_SRCS ${R3BDB_SRCS} ${R3BDB_DICTIONARY})

add_library(R3BDB SHARED ${R3BDB_SRCS})
target_link_libraries(R3BDB ${ROOT_LIBRARIES})
set_target_properties(R3BDB PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS R3BDB DESTINATION ${CMAKE_BINARY_DIR}/lib)
