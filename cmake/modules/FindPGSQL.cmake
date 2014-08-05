# Macro to search for Postgresql installation
	
find_path(POSTGRESQL_INCLUDE_DIR "postgres.h"
          PATHS 
               "/usr/include/server"
    	       "/usr/include/pgsql/server"
    	       "/usr/include/postgresql/server"
               "/usr/include/postgresql/*/server"
               "/usr/local/include/pgsql/server"
 	           "/usr/local/include/postgresql/server"
   	           "/usr/local/include/postgresql/*/server"
               "/usr/local/pgsql/postgresql/server"
   	           "/usr/local/pgsql/postgresql/*/server"
               "/usr/local/*/include/"
               "/usr/local/*/include/postgresql/"
               "/usr/local/*/include/postgresql/server"
	     )
	

find_library(POSTGRESQL_LIBRARIES 
             NAMES "pq" "libpq"  
	         PATHS
	              "/usr/lib/"
	              "/usr/local/lib/"
	              "/usr/lib/postgresql"
	              "/usr/lib64"
	              "/usr/local/lib64"
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
	
