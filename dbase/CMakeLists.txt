 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
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
dbValidation/DataType.cxx
dbValidation/ValCondition.cxx
dbValidation/ValInterval.cxx
dbValidation/ValTimeStamp.cxx
dbInterface/FairDb.cxx
dbInterface/FairDbConnection.cxx 
dbInterface/FairDbBufferFile.cxx
dbInterface/FairDbCache.cxx
dbInterface/FairDbConfig.cxx
dbInterface/FairDbConfigNotice.cxx
dbInterface/FairDbConfigurable.cxx
dbInterface/FairDbConfigData.cxx
dbInterface/FairDbFieldType.cxx
dbInterface/FairDbTableMetaData.cxx
dbInterface/FairDbConnectionPool.cxx
dbInterface/FairDbOutTableBuffer.cxx
dbInterface/FairDbProxy.cxx
dbInterface/FairDbResult.cxx
dbInterface/FairDbRollbackTimes.cxx
dbInterface/FairDbTableBuffer.cxx
dbInterface/FairDbStatement.cxx
dbInterface/FairDbString.cxx
dbInterface/FairDbTableInterface.cxx
dbInterface/FairDbTableInterfaceStore.cxx
dbInterface/FairDbObjTableMap.cxx
dbInterface/FairDbStopWatch.cxx 
dbInterface/FairDbStopWatchManager.cxx  
dbInterface/FairDbValRecord.cxx
dbInterface/FairDbValRecordFactory.cxx
dbInterface/FairRegistry.cxx
dbInterface/FairRegistryElement.cxx
dbInterface/FairRegistryElementGeneric.cxx
dbInterface/FairUtilStream.cxx
dbInterface/FairDbLogEntry.cxx
dbInterface/FairDbConfigBuffer.cxx
dbInterface/FairDbConnectionManager.cxx
dbInterface/FairDbExtSqlContent.cxx
dbInterface/FairDbSqlValidityData.cxx
dbInterface/FairDbException.cxx
dbInterface/FairDbExceptionLog.cxx
dbInterface/FairDbUtils.cxx
dbInterface/FairDbValRecordMap.cxx
dbInterface/FairDbDataTypeUnion.cxx
dbInterface/FairDbStreamer.cxx
dbUtils/FairTSQLObject.cxx
dbUtils/FairDbLog.cxx
dbUtils/FairDbLogFormat.cxx
dbUtils/FairDbLogOSStream.cxx
dbUtils/FairDbLogService.cxx
dbUtils/FairDbLogStat.cxx
dbUtils/FairDbLogStream.cxx
)


install(FILES "dbUtils/FairDbLogBFormat.h" DESTINATION include)
install(FILES "dbInterface/FairDbReader.tpl" DESTINATION include)
install(FILES "dbInterface/FairDbWriter.tpl" DESTINATION include)
install(FILES "dbInput/db_detector_def.h" DESTINATION include)
install(FILES "dbInput/prepare_db.sql" DESTINATION share/dbInput)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
SET( HEADERS ${HEADERS} ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbReader.h ${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbWriter.h)
Set(LINKDEF FairDBLinkDef.h)
Set(LIBRARY_NAME FairDB)
Set(DEPENDENCIES Net RIO Cint Core)

GENERATE_LIBRARY()




