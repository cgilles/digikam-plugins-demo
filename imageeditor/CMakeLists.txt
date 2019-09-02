#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(externaldplugins)

cmake_minimum_required(VERSION "3.1.0")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
include(FeatureSummary)

find_package(Qt5 "5.6.0"
             NO_MODULE COMPONENTS
             Core
             Widgets
             Gui
)

find_package(DigikamCore "6.3.0"
             CONFIG REQUIRED)

set_package_properties(DigikamCore PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam core library"
)

include_directories($<TARGET_PROPERTY:Digikam::digikamcore,INTERFACE_INCLUDE_DIRECTORIES>/digikam)

set(helloworld_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldtoolplugin.cpp)

add_library(Editor_HelloWorld_Plugin
            MODULE ${helloworld_SRCS})

set_target_properties(Editor_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(Editor_HelloWorld_Plugin
                      Digikam::digikamcore

                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
)

# --- Install rules ---------------------------------

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

install(TARGETS Editor_HelloWorld_Plugin
        DESTINATION ${QT_PLUGINS_DIR}/digikam/editor
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
