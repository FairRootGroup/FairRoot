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

if(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR)
  set(DDS_FOUND TRUE)
  message(STATUS "Looking for DDS ... found at ${DDS_PATH}")
else(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR)
  set(DDS_FOUND FALSE)
  message(STATUS "Looking for DDS ... not found.")
endif(DDS_INCLUDE_DIR AND DDS_LIBRARY_DIR)
