#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dplugins-demo)

add_subdirectory(bqm)
add_subdirectory(editor)
#add_subdirectory(generic)

# --- Uninstall files ------------------------------

CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/cmake/templates/target.uninstall.cmake.in_cmake"
               "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake" COPYONLY)
ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")
