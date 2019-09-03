#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# MACRO_ADD_PLUGIN_INSTALL_TARGET
# Install plugin files on the system processed with "make install" or "make install/fast".
# TARGET_NAME is the name of the plugin target to install (aka "Generic_HelloWorld_Plugin").
# TARGET_TYPE is the plugin type. Possible value: "generic", "editor", or "bqm".
#
macro(MACRO_ADD_PLUGIN_INSTALL_TARGET TARGET_NAME TARGET_TYPE)

    get_target_property(QT_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE} IMPORTED_LOCATION)

    if(NOT QT_QMAKE_EXECUTABLE)
        message(FATAL_ERROR "qmake is not found.")
    endif()

    # execute the command "qmake -query QT_INSTALL_PLUGINS" to get the path of plugins dir.
    execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
                    OUTPUT_VARIABLE QT_PLUGINS_DIR
                    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(NOT QT_PLUGINS_DIR)
        message(FATAL_ERROR "Qt5 plugin directory cannot be detected.")
    endif()

    install(TARGETS ${TARGET_NAME}
            DESTINATION ${QT_PLUGINS_DIR}/digikam/${TARGET_TYPE}
    )

endmacro()


# MACRO_ADD_UNINSTALL_TARGET
# Remove installed all files from the system processed with "make install" or "make install/fast".
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
