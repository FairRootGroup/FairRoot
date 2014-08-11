# Macro to search for Postgresql installation

#  POSTGRESQL_INCLUDE_DIR - where to find mysql.h, etc.
#  POSTGRESQL_LIBRARY_DIR   - mysqlclient library directory
#  POSTGRESQL_LIBRARIES    - mysqlclient library.
#  POSTGRESQL_FOUND       - True if mysqlclient is found.


# <D.Bertini> : 
#    Date: 05.08.2014 -- Remark: for PgSQL 9.2 on MacOSX the libpq.dylib 
#                        is named libpd.5.dylib. The following script will
#                         not find the corresponding soft link to /Library. 
#                         You need to set the link to libpq.so in /usr/lib.
#                         Issue solved in PgSQL 9.3   
#    Date: 11.08.2014 -- Changes to favor user local installation
	

find_path(POSTGRESQL_INCLUDE_DIR "postgres.h"
          PATHS 
               "/usr/local/include/pgsql/server"
 	           "/usr/local/include/postgresql/server"
   	           "/usr/local/include/postgresql/*/server"
               "/usr/local/pgsql/postgresql/server"
   	           "/usr/local/pgsql/postgresql/*/server"
               "/usr/local/*/include/"
               "/usr/local/*/include/postgresql/"
               "/usr/local/*/include/postgresql/server"
               "/usr/include/server"
    	       "/usr/include/pgsql/server"
    	       "/usr/include/postgresql/server"
               "/usr/include/postgresql/*/server"
	     )
	

find_library(POSTGRESQL_LIBRARIES 
             NAMES "pq" "libpq"  
	         PATHS
	              "/usr/local/lib/"
	              "/usr/local/lib64"
	              "/usr/lib/"
	              "/usr/lib/postgresql"
	              "/usr/lib64"
	              "/usr/lib64/postgresql"
	       )

get_filename_component( POSTGRESQL_LIBRARY_DIR ${POSTGRESQL_LIBRARIES}  PATH ) 


if(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
	    set(POSTGRESQL_FOUND TRUE)
	    message(STATUS "Found PostgreSQL: ${POSTGRESQL_INCLUDE_DIR}, ${POSTGRESQL_LIBRARY_DIR}, ${POSTGRESQL_LIBRARIES}")
	    INCLUDE_DIRECTORIES(${POSTGRESQL_INCLUDE_DIR})
	  else(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
	    set(POSTGRESQL_FOUND FALSE)
	    message(STATUS "PostgreSQL not found.")
endif(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
	
mark_as_advanced(POSTGRESQL_INCLUDE_DIR POSTGRESQL_LIBRARIES)
	
