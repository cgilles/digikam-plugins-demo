#
# Copyright (c) 2019-2020, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dplugins-demo)

# Use common cmake macro from cmake/modules/ to install unistall plugins.

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
INCLUDE(MacroInstall)

###

add_subdirectory(bqm)
add_subdirectory(editor)
add_subdirectory(generic)
add_subdirectory(rawimport)

###

MACRO_ADD_UNINSTALL_TARGET()
