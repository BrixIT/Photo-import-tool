cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

project(foto_import_tool)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
add_subdirectory(src)