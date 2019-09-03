#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# MACRO_ADD_UNINSTALL_TARGET
# Remove installed files from the system processed with "make install" or "make install/fast".
# This macro add a target named "make uninstall" to your project.
#
macro(MACRO_ADD_UNINSTALL_TARGET)

    configure_file("${CMAKE_SOURCE_DIR}/cmake/templates/target.uninstall.cmake.in_cmake"
                   "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
                    COPYONLY
    )

    add_custom_target(uninstall
                      "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    )

endmacro()
