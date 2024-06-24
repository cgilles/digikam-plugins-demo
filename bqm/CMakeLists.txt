#
# Copyright (c) 2019-2024, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-bqm)

cmake_minimum_required(VERSION "3.16.0")
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED
             NO_MODULE COMPONENTS
             Core
             Widgets
             Gui
             Sql
)

find_package(DigikamGui
             CONFIG REQUIRED)

set_package_properties(DigikamGui PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam gui library"
)

find_package(DigikamDatabase
             CONFIG REQUIRED)

set_package_properties(DigikamDatabase PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam database library"
)

include(i18nUtils)

include_directories($<TARGET_PROPERTY:Digikam::digikamdatabase,INTERFACE_INCLUDE_DIRECTORIES>)

set(helloworld_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldbqmplugin.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.cpp
                    ${i18n_QRC_SRCS}
                    ${i18n_QM}
)

add_library(Bqm_HelloWorld_Plugin
            MODULE ${helloworld_SRCS})

set_target_properties(Bqm_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(Bqm_HelloWorld_Plugin
                      Digikam::digikamdatabase
                      Digikam::digikamgui

                      Qt${QT_VERSION_MAJOR}::Core
                      Qt${QT_VERSION_MAJOR}::Widgets
                      Qt${QT_VERSION_MAJOR}::Gui
                      Qt${QT_VERSION_MAJOR}::Sql
)

MACRO_ADD_PLUGIN_INSTALL_TARGET(Bqm_HelloWorld_Plugin bqm)

# ---

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
