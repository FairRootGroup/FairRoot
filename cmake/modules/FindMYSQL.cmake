# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIRS - where to find mysql.h, etc.
#  MYSQL_LIBRARIES   - mysqlclient library.
#  MYSQL_FOUND       - True if mysqlclient is found.
#

# <D.Bertini> : 
#    Date: 11.08.2014 -- Changes to favor user local installation


find_path( MYSQL_INCLUDE_DIR "mysql.h"
	PATHS
		"/usr/local/include/mysql"
        "/usr/local/mysql"
        "/usr/local/*/include/" 
		"/usr/include/mysql"
		"/usr/mysql/include/mysql"
         )

find_library( MYSQL_LIBRARIES
	NAMES "mysqlclient" "mysqlclient_r"
	PATHS
		"/usr/local/lib/mysql"
        "/usr/local/mysql/lib"
        "/usr/local/*/lib"   
		"/usr/lib/mysql"
		"/usr/mysql/lib/mysql"
        )  

get_filename_component( MYSQL_LIBRARY_DIR ${MYSQL_LIBRARIES}  PATH ) 

mark_as_advanced( MYSQL_LIBRARIES  MYSQL_INCLUDE_DIR )

if(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
	    set(MYSQL_FOUND TRUE)
	    message(STATUS "Found MySQL: ${MYSQL_INCLUDE_DIR}, ${MYSQL_LIBRARY_DIR}, ${MYSQL_LIBRARIES}")
	    INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})
	  else(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
	    set(MYSQL_FOUND FALSE)
	    message(STATUS "MySQL not found.")
endif(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
	
mark_as_advanced(MYSQL_INCLUDE_DIR MYSQL_LIBRARIES)
	
