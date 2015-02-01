cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

project(foto_import_tool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(GLIB REQUIRED gio)
include_directories(${GLIB_INCLUDE_DIRS} ${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR})

set(SOURCE_FILES main.cpp)
add_executable(foto_import_tool ${SOURCE_FILES})
target_link_libraries(foto_import_tool ${GLIB_LIBRARIES} ${GLIB_GIO_LIBRARIES})