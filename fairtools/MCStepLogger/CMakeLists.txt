# @author Sandro Wenzel
# @brief  cmake setup for module Utilities/MCStepLogger

set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
)

Set(SYSTEM_INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
)

Include_Directories( ${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)

Link_Directories(${LINK_DIRECTORIES})

set(HEADERS
)

set(NO_DICT_SRCS
    MCStepInterceptor.cxx
    MCStepLoggerImpl.cxx
   )

set(LIBRARY_NAME FairMCStepLogger)
Set(DEPENDENCIES Core Base)

GENERATE_LIBRARY()
