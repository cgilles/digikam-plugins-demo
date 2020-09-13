#
# Copyright (c) 2019-2020, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-editor)

cmake_minimum_required(VERSION "3.1.0")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)

find_package(Qt5 "5.6.0" REQUIRED
             NO_MODULE COMPONENTS
             Core
             Widgets
             Gui
)

find_package(DigikamCore
             CONFIG REQUIRED)

set_package_properties(DigikamCore PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam core library"
)

include(i18nUtils)

qt5_add_resources(i18n_QRC_SRCS
                  ${CMAKE_CURRENT_BINARY_DIR}/i18n.qrc
)

include_directories($<TARGET_PROPERTY:Digikam::digikamcore,INTERFACE_INCLUDE_DIRECTORIES>/digikam)

set(helloworld_editor_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldeditorplugin.cpp
                           ${i18n_QRC_SRCS}
                           ${i18n_QM}
)

add_library(Editor_HelloWorld_Plugin
            MODULE ${helloworld_editor_SRCS})

set_target_properties(Editor_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(Editor_HelloWorld_Plugin
                      Digikam::digikamcore

                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
)

MACRO_ADD_PLUGIN_INSTALL_TARGET(Editor_HelloWorld_Plugin editor)

# ---

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
