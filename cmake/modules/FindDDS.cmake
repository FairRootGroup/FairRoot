################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

MESSAGE(STATUS "Looking for DDS...")

find_path(DDS_INCLUDE_DIR NAMES dds_intercom.h PATHS
  ${DDS_PATH}/include
  ${SIMPATH}/DDS/include
  NO_DEFAULT_PATH
)

find_path(DDS_LIBRARY_DIR NAMES libdds_intercom_lib.dylib libdds_intercom_lib.so
  PATHS ${DDS_PATH}/lib
  PATHS ${SIMPATH}/DDS/lib
  NO_DEFAULT_PATH
)

find_library(DDS_INTERCOM_LIBRARY_SHARED NAMES libdds_intercom_lib.dylib libdds_intercom_lib.so
  PATHS ${DDS_PATH}/lib
  PATHS ${SIMPATH}/DDS/lib
  NO_DEFAULT_PATH
  DOC "Path to libdds_intercom_lib.dylib libdds_intercom_lib.so."
)

find_library(DDS_PROTOCOL_LIBRARY_SHARED NAMES libdds_protocol_lib.dylib libdds_protocol_lib.so
  PATHS ${DDS_PATH}/lib
  PATHS ${SIMPATH}/DDS/lib
  NO_DEFAULT_PATH
  DOC "Path to libdds_protocol_lib.dylib libdds_protocol_lib.so."
)

find_library(DDS_USER_DEFAULTS_LIBRARY_SHARED NAMES libdds-user-defaults.dylib libdds-user-defaults.so
  PATHS ${DDS_PATH}/lib
  PATHS ${SIMPATH}/DDS/lib
  NO_DEFAULT_PATH
  DOC "Path to libdds-user-defaults.dylib libdds-user-defaults.so."
)

if(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR AND DDS_INTERCOM_LIBRARY_SHARED AND DDS_PROTOCOL_LIBRARY_SHARED AND DDS_USER_DEFAULTS_LIBRARY_SHARED)
  set(DDS_FOUND TRUE)
  message(STATUS "Looking for DDS ... found ${DDS_INTERCOM_LIBRARY_SHARED};${DDS_PROTOCOL_LIBRARY_SHARED};${DDS_USER_DEFAULTS_LIBRARY_SHARED}")
else(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR AND DDS_INTERCOM_LIBRARY_SHARED AND DDS_PROTOCOL_LIBRARY_SHARED AND DDS_USER_DEFAULTS_LIBRARY_SHARED)
  set(DDS_FOUND FALSE)
  message(STATUS "Looking for DDS ... not found.")
endif(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR AND DDS_INTERCOM_LIBRARY_SHARED AND DDS_PROTOCOL_LIBRARY_SHARED AND DDS_USER_DEFAULTS_LIBRARY_SHARED)
