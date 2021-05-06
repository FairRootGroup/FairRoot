# @author Sandro Wenzel
# @brief  cmake setup for module Utilities/MCStepLogger

set(target FairMCStepLogger)

set(sources
  MCStepInterceptor.cxx
  MCStepLoggerImpl.cxx
)

add_library(${target} SHARED ${sources})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base

  ROOT::Core
  ROOT::Tree
  ROOT::Hist
  ROOT::RIO
  ${VMCLIB}

  ${CMAKE_DL_LIBS}
)

fairroot_install_exported(TARGETS ${target})
