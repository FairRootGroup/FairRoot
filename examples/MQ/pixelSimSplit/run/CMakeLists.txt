################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(DDS_FOUND)
  set(dds_location ${DDS_INSTALL_PREFIX})
endif()

set(example_library_extension so)
if(APPLE)
  set(example_library_extension dylib)
endif()

set(splitmc_bin_location ${CMAKE_CURRENT_BINARY_DIR})
set(splitmc_file_location ${CMAKE_CURRENT_BINARY_DIR})
set(pixel_bin_dir ${CMAKE_BINARY_DIR}/examples/MQ/pixelDetector/run)
set(fairroot_bin_dir ${CMAKE_BINARY_DIR}/bin)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/splitMC-topology.xml ${CMAKE_CURRENT_BINARY_DIR}/splitMC-topology.xml)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/test-splitMC.sh.in   ${CMAKE_CURRENT_BINARY_DIR}/test-splitMC.sh)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/test-splitMQ.sh.in   ${CMAKE_CURRENT_BINARY_DIR}/test-splitMQ.sh)

set(exe_dependencies
  FairRoot::ExSimMQ
  FairRoot::FairMQ
  Boost::program_options
)

add_executable(pixel-sim-chunk-merger runMQChunkMerger.cxx)
target_link_libraries(pixel-sim-chunk-merger PRIVATE ${exe_dependencies})

add_executable(pixel-sim-gen runMQGen.cxx)
target_link_libraries(pixel-sim-gen PRIVATE
  ${exe_dependencies}
  FairRoot::Base # FairModule, FairPrimaryGenerator
  FairRoot::Gen # FairBoxGenerator
  Core # TSystem
  MathCore # TRandom
)
target_link_directories(pixel-sim-gen PRIVATE ${ROOT_LIBRARY_DIR})

add_executable(pixel-sim-transport runMQTrans.cxx)
target_link_libraries(pixel-sim-transport PRIVATE
  ${exe_dependencies}
  FairRoot::Base # FairModule, FairPrimaryGenerator
  FairRoot::ParBase # FairParAsciiFileIo
  FairRoot::ExPassive # FairCave
  FairRoot::ExPixel
  Core # TSystem
  MathCore # TRandom
)
target_link_directories(pixel-sim-transport PRIVATE ${ROOT_LIBRARY_DIR})

install(TARGETS pixel-sim-chunk-merger pixel-sim-gen pixel-sim-transport
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/MQ/pixelSimSplit/bin
)

set(maxTestTime 90)

# add_test(pixelSplitDDS ${CMAKE_CURRENT_BINARY_DIR}/test-splitMC.sh)
# set_tests_properties(pixelSplitDDS PROPERTIES
#   TIMEOUT ${maxTestTime}
#   PASS_REGULAR_EXPRESSION "Shell script finished successfully"
# )

add_test(ex_MQ_pixel_split ${CMAKE_CURRENT_BINARY_DIR}/test-splitMQ.sh)
set_tests_properties(ex_MQ_pixel_split PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Shell script finished successfully"
)
