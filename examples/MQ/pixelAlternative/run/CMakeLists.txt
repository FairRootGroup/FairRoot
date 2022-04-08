################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(pixel_file_dir ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector)
set(pixel_bin_dir ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run)
set(pixel_alt_bin_location ${CMAKE_CURRENT_BINARY_DIR})
set(fairroot_bin_dir ${CMAKE_BINARY_DIR}/bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/startFairMQPixAlt.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixAlt.sh @ONLY)

set(pixel_file_dir ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector)
set(pixel_bin_dir ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelDetector/bin)
set(pixel_alt_bin_location ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelAlternative/bin)
set(fairroot_bin_dir ${CMAKE_INSTALL_PREFIX}/bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/startFairMQPixAlt.sh.in ${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixAlt.sh_install @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixAlt.sh_install DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelAlternative/bin RENAME startFairMQPixAlt.sh)

set(exe_dependencies
  FairRoot::ExPixelAlt
  FairRoot::FairMQ
  Boost::program_options
)

add_executable(pixalt-sampler-bin runPixAltSamplerBin.cxx)
target_link_libraries(pixalt-sampler-bin PRIVATE ${exe_dependencies})

add_executable(pixalt-sink-bin runPixAltFileSinkBin.cxx)
target_link_libraries(pixalt-sink-bin PRIVATE ${exe_dependencies})

add_executable(pixalt-processor-bin runPixAltTaskProcessorBin.cxx)
target_link_libraries(pixalt-processor-bin PRIVATE ${exe_dependencies})

install(TARGETS pixalt-sampler-bin pixalt-sink-bin pixalt-processor-bin
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelAlternative/bin
)

set(maxTestTime 30)

add_test(ex_MQ_pixel_alt_static ${CMAKE_CURRENT_BINARY_DIR}/startFairMQPixAlt.sh --work-dir ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector --max-index 10000 --aggregate 100 --processors 5 --command static --force-kill true)
set_tests_properties(ex_MQ_pixel_alt_static PROPERTIES
  DEPENDS ex_MQ_pixel_static
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Shell script finished successfully"
)
