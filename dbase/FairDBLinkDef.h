/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

// Generic
#pragma link C++ namespace     Experiment;
#pragma link C++ enum          Experiment::EExperiment;
#pragma link C++ nestedtypedef Experiment::Experiment_t;

#pragma link C++ namespace     FairDbDetector;
#pragma link C++ enum          FairDbDetector::EDetector;
#pragma link C++ nestedtypedef FaiDbDetector::Detector_t;

#pragma link C++ namespace     DataType;
#pragma link C++ enum          DataType::EDataType;
#pragma link C++ nestedtypedef DataType::DataType_t;

// dbValidation
#pragma link C++ class ValTimeStamp+;
#pragma link C++ function operator<<(ostream&, const ValTimeStamp&);
#pragma link C++ function operator==(const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator!=(const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator< (const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator<=(const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator> (const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator>=(const ValTimeStamp&, const ValTimeStamp&);
#pragma link C++ function operator- (const ValTimeStamp&, const ValTimeStamp&);

#pragma link C++ class ValCondition+;
#pragma link C++ function operator==(const ValCondition&, const ValCondition&);
#pragma link C++ function operator!=(const ValCondition&, const ValCondition&);
#pragma link C++ function operator< (const ValCondition&, const ValCondition&);
#pragma link C++ function operator<<(ostream&, const ValCondition&);

#pragma link C++ class ValInterval+;
#pragma link C++ function operator<<(ostream&, const ValInterval&);


// dbInterface
#pragma link C++ class FairDbReader<FairDbLogEntry>+;
#pragma link C++ class FairDbWriter<FairDbLogEntry>+;
#pragma link C++ class FairDbReader<FairDbConfigData>+;
#pragma link C++ class FairDbWriter<FairDbConfigData>+;
#pragma link C++ class FairDbReader<FairDbValRecord>+;

#pragma link C++ class FairDb+;
#pragma link C++ class FairDbCache+;
#pragma link C++ class FairDbConnectionPool+;
#pragma link C++ class FairDbConfigData+;
#pragma link C++ class FairDbConfigBuffer+;
#pragma link C++ class FairDbConnection+;
#pragma link C++ class FairDbConnectionManager+;
#pragma link C++ class FairDbProxy+;
#pragma link C++ class FairDbFieldType+;
#pragma link C++ class FairDbResultKey::VRecKey+;
#pragma link C++ class FairDbResultKey+;
#pragma link C++ class FairDbLogEntry+;
#pragma link C++ class FairDbOutTableBuffer+;
#pragma link C++ class FairDbResult+;
#pragma link C++ class FairDbResultCombo+;
#pragma link C++ class FairDbResultNonCombo+;
#pragma link C++ class FairDbResultPool+;
#pragma link C++ class FairDbRollbackTimes+;
#pragma link C++ class FairDbTableBuffer+;
#pragma link C++ class FairDbExtSqlContent+;
#pragma link C++ class FairDbSqlValidityData+;
#pragma link C++ class FairDbString+;
#pragma link C++ class FairDbStreamer+;
#pragma link C++ class FairDbStatement+;
#pragma link C++ class FairDbTableMetaData+;
#pragma link C++ class FairDbTableInterfaceStore+;
#pragma link C++ class FairDbTableInterface+;
#pragma link C++ class FairDbObjTableMap+;
#pragma link C++ class FairDbDataTypeUnion+;
#pragma link C++ class FairDbStopWatch+;
#pragma link C++ class FairDbStopWatchManager+;
#pragma link C++ class FairDbValRecord+;
#pragma link C++ class FairDbValRecordMap+;
#pragma link C++ class FairDbValRecordFactory+;
#pragma link C++ class FairDbException+;
#pragma link C++ class FairDbExceptionLog+;
#pragma link C++ class FairDbConfigurable+;
#pragma link C++ class FairRegistry-;
#pragma link C++ class FairRegistryElement;
#pragma link C++ class FairRegistryElementGeneric<int>-;
#pragma link C++ class FairRegistryElementGeneric<double>-;
#pragma link C++ class FairRegistryElementGeneric<FairRegistry>-;
#pragma link C++ class FairRegistryElementGeneric<char>-;
#pragma link C++ class FairRegistryElementGeneric<const char*>-;
#pragma link C++ function operator<<(ostream&, const FairRegistry&);

// #### SQL object
#pragma link C++ class FairTSQLObject+;
#pragma link C++ enum  FairDBObjectMemberTypes;
#pragma link C++ union FairDBObjectMemberValues;
#pragma link C++ class FairDBObjectMemberValue+;
#endif
