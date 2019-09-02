#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-bqm)

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
             Sql
)

find_package(DigikamGui "6.3.0"
             CONFIG REQUIRED)

set_package_properties(DigikamGui PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam gui library"
)

find_package(DigikamDatabase "6.3.0"
             CONFIG REQUIRED)

set_package_properties(DigikamDatabase PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam database library"
)

include_directories($<TARGET_PROPERTY:Digikam::digikamdatabase,INTERFACE_INCLUDE_DIRECTORIES>/digikam)

set(helloworld_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldbqmplugin.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.cpp )

add_library(Bqm_HelloWorld_Plugin
            MODULE ${helloworld_SRCS})

set_target_properties(Bqm_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(Bqm_HelloWorld_Plugin
                      Digikam::digikamdatabase
                      Digikam::digikamgui

                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
                      Qt5::Sql
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

install(TARGETS Bqm_HelloWorld_Plugin
        DESTINATION ${QT_PLUGINS_DIR}/digikam/bqm
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
