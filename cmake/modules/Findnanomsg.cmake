message(STATUS "Looking for nanomsg...")

set(BUS_H bus.h)
set(INPROC_H inproc.h)
set(IPC_H ipc.h)
set(NN_H nn.h)
set(PAIR_H pair.h)
set(PIPELINE_H pipeline.h)
set(PROTOCOL_H protocol.h)
set(PUBSUB_H pubsub.h)
set(REQREP_H reqrep.h)
set(SURVEY_H survey.h)
set(TCP_H tcp.h)

if (APPLE)
  set(LIBNANOMSG_SHARED libnanomsg.dylib)
else (APPLE)
  set(LIBNANOMSG_SHARED libnanomsg.so)
endIf (APPLE)

set(LIBNANOMSG_STATIC libnanomsg.a)

find_path(NANOMSG_INCLUDE_DIR NAMES ${BUS_H} ${INPROC_H} ${IPC_H} ${NN_H} ${PAIR_H} ${PIPELINE_H} ${PROTOCOL_H} ${PUBSUB_H} ${REQREP_H} ${SURVEY_H} ${TCP_H}
  PATHS /usr/local/include/nanomsg
  DOC   "Path to nanomsg include header files."
)

find_library(NANOMSG_LIBRARY_SHARED NAMES ${LIBNANOMSG_SHARED}
  PATHS /usr/local/lib
  DOC   "Path to ${LIBNANOMSG_SHARED}."
)

find_library(NANOMSG_LIBRARY_STATIC NAMES ${LIBNANOMSG_STATIC}
  PATHS /usr/local/lib
  DOC   "Path to ${LIBNANOMSG_STATIC}."
)

if(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)
  set(NANOMSG_FOUND true)
else(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)
  set(NANOMSG_FOUND false)
endif(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)

if(NANOMSG_FOUND)
  add_definitions(-DNANOMSG)
  set(NANOMSG_LIBRARIES "${NANOMSG_LIBRARY_STATIC};${NANOMSG_LIBRARY_SHARED}")
  if(NOT NANOMSG_FIND_QUIETLY)
    message(STATUS "Looking for nanomsg... - found ${NANOMSG_LIBRARIES}")
  endif(NOT NANOMSG_FIND_QUIETLY)
else(NANOMSG_FOUND)
  if(NOT NANOMSG_FIND_QUIETLY)
    if(NANOMSG_FIND_REQUIRED)
      message(FATAL_ERROR "Looking for nanomsg... - Not found")
    else(NANOMSG_FIND_REQUIRED)
      message(STATUS "Looking for nanomsg... - Not found")
    endif(NANOMSG_FIND_REQUIRED)
  endif(NOT NANOMSG_FIND_QUIETLY)
endif(NANOMSG_FOUND)

mark_as_advanced(NANOMSG_INCLUDE_DIR NANOMSG_LIBRARIES NANOMSG_LIBRARY_SHARED NANOMSG_LIBRARY_STATIC)
