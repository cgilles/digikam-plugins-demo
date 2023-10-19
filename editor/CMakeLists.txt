#
# Copyright (c) 2019-2023, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-editor)

cmake_minimum_required(VERSION "3.16.0")
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED
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

include_directories($<TARGET_PROPERTY:Digikam::digikamcore,INTERFACE_INCLUDE_DIRECTORIES>)

set(helloworld_editor_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldeditorplugin.cpp
                           ${i18n_QRC_SRCS}
                           ${i18n_QM}
)

add_library(Editor_HelloWorld_Plugin
            MODULE ${helloworld_editor_SRCS})

set_target_properties(Editor_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(Editor_HelloWorld_Plugin
                      Digikam::digikamcore

                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Gui
)

MACRO_ADD_PLUGIN_INSTALL_TARGET(Editor_HelloWorld_Plugin editor)

# ---

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
