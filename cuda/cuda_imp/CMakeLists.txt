 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

##############################################################################
# There are two ways to add include directories to the NVCC command
# line:

#set(CUDA_PROPAGATE_HOST_FLAGS OFF)

# The cuda_include_directories adds paths to only cuda compilation.
CUDA_INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}
  /home/NVIDIA_GPU_Computing_SDK4.1/C/common/inc/
  )

 
# The include_directories adds paths to both C/C++ compilation in the native
# compiler and cuda compilation in NVCC.  Note that CUDA_INCLUDE_DIRS is added
# automatically by CUDA_ADD_EXECUTABLE and CUDA_ADD_LIBRARY.

# INCLUDE_DIRECTORIES(
#   ${CUDA_INCLUDE_DIRS}
#   )

##############################################################################
# There are four ways to compile source files with NVCC. 

set(CUDA_SRCS
  test_lib.cu
  trackfit.cu
  trackfit_kernel.cu

)
# Set CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE when you want to add the same .cu
# file to multiple targets.
set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE OFF)

# Use one executable only.
CUDA_ADD_EXECUTABLE(cuda_example
  main.cc
 )

#set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE ON)

#CUDA_ADD_EXECUTABLE(test-conflict
#  "${CMAKE_CURRENT_SOURCE_DIR}/path with spaces/conflict.cpp"
#  "${CMAKE_CURRENT_SOURCE_DIR}/path with spaces/conflict.cu"
#  "${CMAKE_CURRENT_SOURCE_DIR}/path with spaces/no-conflict.cpp"
#  "${CMAKE_CURRENT_SOURCE_DIR}/path with spaces/no-conflict.cu"
#  ${CMAKE_CURRENT_SOURCE_DIR}/conflict-main.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/conflict.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/conflict.cu
#  )
# Or compile the cuda code into a shared library.

# Anything other than -D or /D is not passed along to nvcc.
add_definitions(-DMULTIPLIER=2)

# You can set BUILD_SHARED_LIBS or you can pass STATIC, SHARED, or MODULE to
# CUDA_ADD_LIBRARY.  Remember that BUILD_SHARED_LIBS is only respected by
# CUDA_ADD_LIBRARY.  If you use CUDA_COMPILE or CUDA_WRAP_SRCS you must specify
# SHARED or STATIC as a parameter.
set(BUILD_SHARED_LIBS ON)
set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE ON)
list(APPEND CUDA_NVCC_FLAGS -DBLAH="he he" -DTEST1="this is a test")
#include_directories("path with spaces")
#add_executable(test_with_spaces test_with_spaces.cpp)
CUDA_ADD_LIBRARY(cuda_imp 
  ${CUDA_SRCS}
#  external_dependency.h
   SHARED
  # STATIC
  #OPTIONS -DSTUFF="blah blah"
  #RELEASE --use_fast_math -DNDEBUG
  #DEBUG -g -DDEBUG
  )

# Then link the shared library to another executable.
#ADD_EXECUTABLE(lib_example
#  main_for_lib.cc
#  )

# Specify the dependency.
TARGET_LINK_LIBRARIES(cuda_example
   cuda_imp
  ${CUDA_TARGET_LINK}
  ${CUDA_CUT_TARGET_LINK}
  ${ROOT_LIBRARIES}
  )

# Using the CUDA_COMPILE macro
#set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE OFF)
#set(source_files test_bin.cu)
#CUDA_COMPILE(CUDA_FILES test_bin.cu)

#ADD_EXECUTABLE(cuda_compile_example
#  ${CUDA_FILES}
#  ${source_files}
#  main.cc
#  external_dependency.h
#  )
#TARGET_LINK_LIBRARIES(cuda_compile_example
# ${CUDA_LIBRARIES}
# )

#set(CUDA_ATTACH_VS_BUILD_RULE_TO_CUDA_FILE ON)

# Generating PTX files.
#set(CUDA_GENERATED_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
#CUDA_COMPILE_PTX(ptx_files test_ptx.cu)
#add_executable(test_ptx
#  main-ptx.cpp
#  ${ptx_files}
#  test_ptx.cu
#  )
#target_link_libraries(test_ptx
#  ${CUDA_CUDA_LIBRARY}
#  )

# Add a special target to clean nvcc generated files.
CUDA_BUILD_CLEAN_TARGET()

