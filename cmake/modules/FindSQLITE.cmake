# - Try to find the sqlite library
# Once done this will define
#
#  SQLITE_FOUND - system has sqlite
#  SQLITE_INCLUDE_DIR - the sqlite include directory
#  SQLITE_LIBRARY_DIR
#  SQLITE_LIBRARIES - Link these to use sqlite
#

# <D.Bertini> : 
#    Date: 11.08.2014 -- Changes to favor user local installation



	find_path(SQLITE_INCLUDE_DIR sqlite3.h
              PATHS
              /usr/local/include
              /usr/include
              )
	find_library(SQLITE_LIBRARIES sqlite3 
                NAMES sqlite3
                PATHS
                /usr/local/lib
                /usr/lib
              )
get_filename_component( SQLITE_LIBRARY_DIR ${SQLITE_LIBRARIES}  PATH )

if(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)
	    set(SQLITE_FOUND TRUE)
	    message(STATUS "Found SQLite: ${SQLITE_INCLUDE_DIR}, ${SQLITE_LIBRARY_DIR}, ${SQLITE_LIBRARIES}")
	    INCLUDE_DIRECTORIES(${SQLITE_INCLUDE_DIR})
	  else(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)
	    set(SQLITE_FOUND FALSE)
	    message(STATUS "SQLite not found.")
endif(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)



MARK_AS_ADVANCED(SQLITE_LIBRARIES SQLITE_INCLUDE_DIR)
