# @author Sandro Wenzel
# @brief  cmake setup for module Utilities/MCStepLogger

set(target FairMCStepLogger)

set(sources
  MCStepInterceptor.cxx
  MCStepLoggerImpl.cxx
)

add_library(${target} SHARED ${sources})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_link_libraries(${target} PUBLIC
  FairRoot::Base
  ROOT::Core
  ROOT::Tree
  ROOT::Hist
  ROOT::RIO
  ${VMC_LIB} # TVirtualMC
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
