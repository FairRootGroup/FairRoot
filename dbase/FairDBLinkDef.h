//2005/06/23 07:14:26 dbertini Exp $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

// Generic
#pragma link C++ namespace     Experiment;
#pragma link C++ enum          Experiment::EExperiment;
#pragma link C++ nestedtypedef Experiment::Experiment_t;

#pragma link C++ namespace     Detector;
#pragma link C++ enum          Detector::EDetector;
#pragma link C++ nestedtypedef Detector::Detector_t;

#pragma link C++ namespace     SimFlag;
#pragma link C++ enum          SimFlag::ESimFlag;
#pragma link C++ nestedtypedef SimFlag::SimFlag_t;

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

#pragma link C++ class ValContext+;
#pragma link C++ function operator==(const ValContext&, const ValContext&);
#pragma link C++ function operator!=(const ValContext&, const ValContext&);
#pragma link C++ function operator< (const ValContext&, const ValContext&);
#pragma link C++ function operator<<(ostream&, const ValContext&);

#pragma link C++ class ValRange+;
#pragma link C++ function operator<<(ostream&, const ValRange&);

#pragma link C++ class ValValidate;

// dbInterface
#pragma link C++ class FairDbResultPtr<FairDbLogEntry>+;
#pragma link C++ class FairDbWriter<FairDbLogEntry>+;
#pragma link C++ class FairDbResultPtr<FairDbConfigSet>+;
#pragma link C++ class FairDbWriter<FairDbConfigSet>+;
#pragma link C++ class FairDbResultPtr<FairDbValidityRec>+;

#pragma link C++ class FairDb+;
#pragma link C++ class FairDbCache+;
#pragma link C++ class FairDbMultConnector+;
#pragma link C++ class FairDbConfigSet+;
#pragma link C++ class FairDbConfigStream+;
#pragma link C++ class FairDbConnection+;
#pragma link C++ class FairDbConnectionMaintainer+;
#pragma link C++ class FairDbProxy+;
#pragma link C++ class FairDbFieldType+;
#pragma link C++ class FairDbResultKey::VRecKey+;
#pragma link C++ class FairDbResultKey+;
#pragma link C++ class FairDbLogEntry+;
#pragma link C++ class FairDbOutRowStream+;
#pragma link C++ class FairDbResult+;
#pragma link C++ class FairDbResultAgg+;
#pragma link C++ class FairDbResultNonAgg+;
#pragma link C++ class FairDbResultSet+;
#pragma link C++ class FairDbRollbackDates+;
#pragma link C++ class FairDbRowStream+;
#pragma link C++ class FairDbSqlContext+;
#pragma link C++ class FairDbSqlValPacket+;
#pragma link C++ class FairDbString+;
#pragma link C++ class FairDbStreamer+;
#pragma link C++ class FairDbStatement+;
#pragma link C++ class FairDbTableMetaData+;
#pragma link C++ class FairDbTableProxyRegistry+;
#pragma link C++ class FairDbTableProxy+;
#pragma link C++ class FairDbTableRow+;
#pragma link C++ class FairDbSimFlagAssociation+;
#pragma link C++ class FairDbTimer+;
#pragma link C++ class FairDbTimerManager+;
#pragma link C++ class FairDbValidityRec+;
#pragma link C++ class FairDbValRecSet+;
#pragma link C++ class FairDbValidityRecBuilder+;
#pragma link C++ class FairDbException+;
#pragma link C++ class FairDbExceptionLog+;
#pragma link C++ class FairDbConfigurable+;
#pragma link C++ class FairRegistry-;
#pragma link C++ class FairRegistryItem;
#pragma link C++ class FairRegistryItemXxx<int>-;
#pragma link C++ class FairRegistryItemXxx<double>-;
#pragma link C++ class FairRegistryItemXxx<FairRegistry>-;
#pragma link C++ class FairRegistryItemXxx<char>-;
#pragma link C++ class FairRegistryItemXxx<const char*>-;
#pragma link C++ function operator<<(ostream&, const FairRegistry&);

// #### SQL object
#pragma link C++ class FairTSQLObject+;
#pragma link C++ enum  FairDBObjectMemberTypes;
#pragma link C++ union FairDBObjectMemberValues;
#pragma link C++ class FairDBObjectMemberValue+;
#endif
