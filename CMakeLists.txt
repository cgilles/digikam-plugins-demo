#
# Copyright (c) 2019-2023, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

cmake_minimum_required(VERSION "3.16.0")

project(dplugins-demo)

# Use common cmake macro from cmake/modules/ to install unistall plugins.

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include(MacroInstall)

include_directories(${CMAKE_SOURCE_DIR}/common)

###

find_package(Qt6 QUIET COMPONENTS Core)

if(NOT Qt6_FOUND)

    find_package(Qt5 REQUIRED COMPONENTS Core)
    set(QT_VERSION_MAJOR 5)

else()

    set(QT_VERSION_MAJOR 6)

endif()

message(STATUS "Suitable Qt${QT_VERSION_MAJOR} detected...")

###

add_subdirectory(bqm)
add_subdirectory(editor)
add_subdirectory(generic)
add_subdirectory(rawimport)

###

MACRO_ADD_UNINSTALL_TARGET()
