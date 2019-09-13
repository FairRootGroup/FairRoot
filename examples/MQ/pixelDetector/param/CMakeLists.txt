################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pixel_digi.par ${CMAKE_CURRENT_BINARY_DIR}/pixel_digi.par)

install(FILES pixel_digi.par
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector/param/
)
