add_library(Logger SHARED
    Logger.cxx
    Logger.h
)

target_include_directories(Logger
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/logger>
    $<INSTALL_INTERFACE:include>
)

add_executable(loggerTest loggerTest.cxx)
target_link_libraries(loggerTest Logger pthread)

install(
    TARGETS Logger loggerTest
    EXPORT FairMQ
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    FILES Logger.h
    DESTINATION include
)