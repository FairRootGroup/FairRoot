 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(NETWORK_INTERFACE eth0)
If(APPLE)
  set(NETWORK_INTERFACE lo0)
EndIf(APPLE)

set(SIM_FILE_LOCATION ${CMAKE_SOURCE_DIR})
set(SIM_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/simulation_split)
set(PIXEL_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin/examples/MQ/pixelDetector)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_BINARY_DIR}/bin)

configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/simulation_split/scripts/dds-simulation-split.xml
		${CMAKE_BINARY_DIR}/bin/examples/MQ/simulation_split/dds-simulation-split.xml )

set(SIM_FILE_LOCATION ${CMAKE_INSTALL_PREFIX}/share/fairbase)
set(SIM_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/simulation_split/bin)
set(PIXEL_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples/MQ/pixelDetector/bin)
set(FAIRROOT_BIN_LOCATION  ${CMAKE_INSTALL_PREFIX}/bin)
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/simulation_split/scripts/dds-simulation-split.xml
		${CMAKE_BINARY_DIR}/examples/MQ/simulation_split/scripts/dds-simulation-split.xml_install )

set(SIM_INSTALL_BIN share/fairbase/examples/MQ/simulation_split/bin)

Install(FILES ${CMAKE_BINARY_DIR}/examples/MQ/simulation_split/scripts/dds-simulation-split.xml_install
        DESTINATION ${SIM_INSTALL_BIN}
        RENAME dds-simulation-split.xml PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
