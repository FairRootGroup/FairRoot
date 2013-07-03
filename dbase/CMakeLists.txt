# Create a library called "libFAIRDB" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/base
${CMAKE_SOURCE_DIR}/base/steer
${CMAKE_SOURCE_DIR}/base/event
${CMAKE_SOURCE_DIR}/base/field
${CMAKE_SOURCE_DIR}/base/sim
${CMAKE_SOURCE_DIR}/parbase
${CMAKE_SOURCE_DIR}/dbase
${CMAKE_SOURCE_DIR}/dbase/dbInterface
${CMAKE_SOURCE_DIR}/dbase/dbValidation
${CMAKE_SOURCE_DIR}/dbase/dbUtils
${CMAKE_SOURCE_DIR}/input/db
${CMAKE_SOURCE_DIR}/dbase/dbInput
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
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
dbInterface/FairDbStreamer.cxx
dbUtils/FairTSQLObject.cxx
dbUtils/FairDbLog.cxx
dbUtils/FairDbLogFormat.cxx
dbUtils/FairDbLogOSStream.cxx
dbUtils/FairDbLogService.cxx
dbUtils/FairDbLogStat.cxx
dbUtils/FairDbLogStream.cxx
)


CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
SET( HEADERS ${HEADERS} ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbResPtr.h ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbWriter.h)
Set(LINKDEF FairDBLinkDef.h)
Set(LIBRARY_NAME FairDB)
Set(DEPENDENCIES Net RIO Cint Core)

GENERATE_LIBRARY()




