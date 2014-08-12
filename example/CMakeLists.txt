 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
add_subdirectory (passive)
add_subdirectory (mcstack)

add_subdirectory (Tutorial1)
add_subdirectory (Tutorial2)
add_subdirectory (Tutorial3)
add_subdirectory (Tutorial4)
add_subdirectory (Tutorial5)
add_subdirectory (rutherford)
add_subdirectory (flp2epn)

if(SQLITE_FOUND AND POSTGRESQL_FOUND AND MYSQL_FOUND)
  add_subdirectory (Tutorial6)
else(SQLITE_FOUND AND POSTGRESQL_FOUND AND MYSQL_FOUND)
  Message(STATUS "Tutorial 6 will not be build MySQL PGSQL and SQLITE where not found") 
endif(SQLITE_FOUND AND POSTGRESQL_FOUND AND MYSQL_FOUND)

