################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Configure/Install FairVersion.h
if(FAIRROOT)
  configure_file(${FAIRROOT}/scripts/FairVersion.h.in
    ${CMAKE_BINARY_DIR}/FairVersion.h
    @ONLY
  )
else()
  configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/FairVersion.h.in
    ${CMAKE_BINARY_DIR}/FairVersion.h
    @ONLY
  )
endif()
install(FILES ${CMAKE_BINARY_DIR}/FairVersion.h
  DESTINATION ${FAIRROOT_INSTALL_INCDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
  DESTINATION ${FAIRROOT_INSTALL_BINDIR}
  RENAME FairRootConfig.sh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
  DESTINATION ${FAIRROOT_INSTALL_BINDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
  DESTINATION ${FAIRROOT_INSTALL_BINDIR}
  RENAME FairRootConfig.csh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
  DESTINATION ${FAIRROOT_INSTALL_BINDIR}
)
install(DIRECTORY cmake/checks DESTINATION ${FAIRROOT_INSTALL_DATADIR})
install(DIRECTORY cmake/modules DESTINATION ${FAIRROOT_INSTALL_DATADIR})
install(DIRECTORY cmake/scripts DESTINATION ${FAIRROOT_INSTALL_DATADIR})
configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/fairroot-config.in
  ${CMAKE_BINARY_DIR}/fairroot-config
  @ONLY
)
install(PROGRAMS ${CMAKE_BINARY_DIR}/fairroot-config
  DESTINATION ${FAIRROOT_INSTALL_BINDIR}
)

# Configure/Install CMake package and exported targets
include(CMakePackageConfigHelpers)
set(PACKAGE_INSTALL_DESTINATION
  ${FAIRROOT_INSTALL_LIBDIR}/cmake
)
install(EXPORT ${PROJECT_NAME}Exports
  NAMESPACE FairRoot::
  DESTINATION ${PACKAGE_INSTALL_DESTINATION}
  EXPORT_LINK_INTERFACE_LIBRARIES
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
  ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${PACKAGE_INSTALL_DESTINATION}
  PATH_VARS CMAKE_INSTALL_PREFIX
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${PACKAGE_INSTALL_DESTINATION}
)
