cmake_minimum_required(VERSION 2.8)

project(uMemcached)

add_subdirectory(client)
ADD_SUBDIRECTORY(proto)

set (BOOST_INCLUDEDIR /usr/include/boost )
set (BOOST_LIBRARYDIR /usr/lib/x86_64-linux-gnu/)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.58.0 COMPONENTS system REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(NOT Boost_FOUND)
  message("Boost Not Found.")
endif()

if(NOT PROTOBUF_FOUND)
  message("Protobuf Not Found.")
endif()

if(PROTOBUF_FOUND)
  message("Protobuf Found.")
  message(${PROTOBUF_INCLUDE_DIRS})
  message(${PROTOBUF_LIBRARIES})
  message(${PROTOBUF_LIBRARY})
  message(${PROTOBUF_LIBRARIES})
endif()

file(GLOB uMemcached_sources *.cpp *.h)
add_compile_options(-std=c++11)

add_executable(uMemcached ${uMemcached_sources})
#add_executable(uMemcached main.cpp)
#add_executable(uMemcached ${uMemcached_sources} proto/uMemcached.pb.cc proto/uMemcached.pb.h)
#target_link_libraries(uMemcached proto ${Boost_LIBRARIES} /usr/lib/x86_64-linux-gnu/libprotobuf.so)
target_link_libraries(uMemcached proto ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})
