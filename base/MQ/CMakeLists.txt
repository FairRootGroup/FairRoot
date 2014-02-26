set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/base/MQ
  ${CMAKE_SOURCE_DIR}/fairmq
  ${Boost_INCLUDE_DIR}
  ${ROOT_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})

set(SRCS
  "FairMQSampler.cxx"
  "FairMQSamplerTask.cxx"
  "FairMQProcessor.cxx"
  "FairMQProcessorTask.cxx"
)

set(DEPENDENCIES
  ${CMAKE_THREAD_LIBS_INIT}
  Base ParBase FairTools GeoBase boost_thread boost_timer boost_system FairMQ
)


set(LIBRARY_NAME FairMQSampler)

GENERATE_LIBRARY()

