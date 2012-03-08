# Create a library called "libFAIRDB" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/parbase
${CMAKE_SOURCE_DIR}/dbase
${CMAKE_SOURCE_DIR}/dbase/dbValidation
${CMAKE_SOURCE_DIR}/dbase/dbInterface
${CMAKE_SOURCE_DIR}/dbase/dbIO
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(FAIRDB_SRCS
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

dbIO/FairDetParTSQLIo.cxx
dbIO/FairDetParTSQLIo.h
dbIO/FairGenericParTSQLIo.cxx
dbIO/FairGenericParTSQLIo.h
dbIO/FairParTSQLIo.cxx
dbIO/FairParTSQLIo.h
)


if(RULE_CHECKER_FOUND)
CHECK_RULES("${FAIRDB_SRCS}" "${INCLUDE_DIRECTORIES}" FAIRDB_RULES)
endif(RULE_CHECKER_FOUND)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h FAIRDB_HEADERS "${FAIRDB_SRCS}")
SET( FAIRDB_HEADERS ${FAIRDB_HEADERS} ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbResPtr.h ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbWriter.h)

set(FAIRDB_LINKDEF  FairDBLinkDef.h)
set(FAIRDB_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/FAIRDBDict.cxx)

ROOT_GENERATE_DICTIONARY("${FAIRDB_HEADERS}" "${FAIRDB_LINKDEF}" "${FAIRDB_DICTIONARY}" "${INCLUDE_DIRECTORIES}")

SET(FAIRDB_SRCS ${FAIRDB_SRCS} ${FAIRDB_DICTIONARY})

add_library(FairDB SHARED ${FAIRDB_SRCS})
target_link_libraries(FairDB ${ROOT_LIBRARIES})
set_target_properties(FairDB PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})
################ install ###################
install(TARGETS FairDB DESTINATION ${CMAKE_BINARY_DIR}/lib)
