 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR} 
${CUDA_INCLUDE}
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}

)
 
link_directories( ${LINK_DIRECTORIES})


set(INTERFACE_SRCS
  FairCuda.h
)

set(INTERFACE_HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/FairCuda.h)
set(CUDA_LINKDEF  ${CMAKE_CURRENT_SOURCE_DIR}/cudaLinkDef.h)
set(INTERFACE_DICTIONARY "${CMAKE_CURRENT_BINARY_DIR}/cudaDict.cxx") 
ROOT_GENERATE_DICTIONARY("${INTERFACE_HEADERS}" "${INTERFACE_LINKDEF}" "${INTERFACE_DICTIONARY}" "${INCLUDE_DIRECTORIES}")
SET(INTERFACE_SRCS ${INTERFACE_SRCS} ${INTERFACE_DICTIONARY})
 
ADD_LIBRARY(cudaintrface SHARED
  ${INTERFACE_SRCS}
 )

############### build the library #####################

target_link_libraries(cudaintrface ${ROOT_LIBRARIES} "${CMAKE_BINARY_DIR}/lib/libcuda_imp.a" "${CUDA_TARGET_LINK}" "${CUDA_CUT_TARGET_LINK}"  )

set_target_properties(cudaintrface PROPERTIES ${FAIRROOT_LIBRARY_PROPERTIES})

############### install the library #############
######
install(TARGETS cudaintrface DESTINATION ${CMAKE_BINARY_DIR}/lib)

