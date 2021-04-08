# @author Sandro Wenzel
# @brief  cmake setup for module Utilities/MCStepLogger

set(target FairMCStepLogger)

set(sources
  MCStepInterceptor.cxx
  MCStepLoggerImpl.cxx
)

add_library(${target} SHARED ${sources})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base

  ROOT::Core
  ROOT::Tree
  ROOT::Hist
  ROOT::RIO
  ${VMCLIB}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
