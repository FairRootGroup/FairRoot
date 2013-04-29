# - Try to find PYTHIA8 instalation
# Once done this will define
#

MESSAGE(STATUS "Looking for PYTHIA8 ...")

FIND_PATH(PYTHIA8_INCLUDE_DIR NAMES Pythia.h PATHS
  ${SIMPATH}/include/pythia8  
  ${SIMPATH}/generators/include/pythia8  
  ${SIMPATH}/generators/pythia8/include  
  NO_DEFAULT_PATH
)

FIND_PATH(PYTHIA8_LIB_DIR  NAMES libpythia8.so PATHS
  ${SIMPATH}/lib
  ${SIMPATH}/generators/lib
  NO_DEFAULT_PATH
)

if (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIB_DIR)
   set(PYTHIA8_FOUND TRUE)
endif (PYTHIA8_INCLUDE_DIR AND PYTHIA8_LIB_DIR)

if (PYTHIA8_FOUND)
  if (NOT PYTHIA8_FOUND_QUIETLY)
    MESSAGE(STATUS "Looking for PYTHIA8... - found ${PYTHIA8_LIB_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${PYTHIA8_LIB_DIR})
  endif (NOT PYTHIA8_FOUND_QUIETLY)
else (PYTHIA8_FOUND)
  if (PYTHIA8_FOUND_REQUIRED)
    message(FATAL_ERROR "Looking for PYTHIA8... - Not found")
  endif (PYTHIA8_FOUND_REQUIRED)
endif (PYTHIA8_FOUND)

