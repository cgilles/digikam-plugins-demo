#
# Copyright (c) 2019-2020, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-bqm)

cmake_minimum_required(VERSION "3.1.0")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

include(FeatureSummary)

find_package(Qt5 "5.6.0" REQUIRED
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

MACRO_ADD_PLUGIN_INSTALL_TARGET(Bqm_HelloWorld_Plugin bqm)

# ---

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
