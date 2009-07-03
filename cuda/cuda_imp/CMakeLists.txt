
# Add current directory to the nvcc include line.
CUDA_INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CUDA_CUT_INCLUDE}
  ${ROOT_INCLUDE_DIR} 
  ${CUDA_INCLUDE}
)
set(CUDA_SRCS
  
  test_lib.cu
  trackfit.cu
  trackfit_kernel.cu

)

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}

)

CUDA_ADD_LIBRARY(cuda_imp
  ${CUDA_SRCS}
 )

# Something else to link to.
ADD_EXECUTABLE(cuda_example
  main.cc

  )

# Specify the dependency.
TARGET_LINK_LIBRARIES(cuda_example
  cuda_imp
  ${CUDA_TARGET_LINK}
  ${CUDA_CUT_TARGET_LINK}
  ${ROOT_LIBRARIES}
  )

##############################################################################
# Use the CUDA_COMPILE macro.
CUDA_COMPILE(CUDA_FILES )

IF(UNIX AND NOT WIN32)
  FIND_PROGRAM(CMAKE_UNAME uname /bin /usr/bin /usr/local/bin )
  IF(CMAKE_UNAME)
    EXEC_PROGRAM(uname ARGS -m OUTPUT_VARIABLE CMAKE_SYSTEM_PROCESSOR)
    SET(CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR} CACHE INTERNAL
"processor type (i386 and x86_64)")
     IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
      ADD_DEFINITIONS(-fPIC)
    ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  ENDIF(CMAKE_UNAME)
ENDIF(UNIX AND NOT WIN32)
