# @author Sandro Wenzel
# @brief  cmake setup for module Utilities/MCStepLogger

set(target FairMCStepLogger)

set(sources
  MCStepInterceptor.cxx
  MCStepLoggerImpl.cxx
)

add_library(${target} SHARED ${sources})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base
  # TODO: clean the following
  Core
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)
