################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

get_property(ROOT_INCLUDE_PATH GLOBAL PROPERTY ROOT_INCLUDE_PATH)
list(INSERT LD_LIBRARY_PATH 0 ${CMAKE_BINARY_DIR}/lib)
list(REMOVE_DUPLICATES LD_LIBRARY_PATH)
set(VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

if(NOT FAIRROOT_MINIMAL)
  WRITE_CONFIG_FILE(config.sh)
  WRITE_CONFIG_FILE(config.csh)

  SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples)
  SET(ROOT_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
  WRITE_CONFIG_FILE(config.sh_install)
  WRITE_CONFIG_FILE(config.csh_install)

else()
  WRITE_MINIMAL_CONFIG_FILE(config.sh)
endif()
