#
# Copyright (c) 2019, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

project(dpluginsdemo-rawimport)

cmake_minimum_required(VERSION "3.1.0")
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
include(FeatureSummary)

find_package(Qt5 "5.6.0" REQUIRED
             NO_MODULE COMPONENTS
             Core
             Widgets
             Gui
)

# Note : RawImport plugin have been introduced with 6.4.0
find_package(DigikamCore
             CONFIG REQUIRED)

set_package_properties(DigikamCore PROPERTIES
                       URL "http://www.digikam.org"
                       DESCRIPTION "digiKam core library"
)

include_directories($<TARGET_PROPERTY:Digikam::digikamcore,INTERFACE_INCLUDE_DIRECTORIES>/digikam)

set(helloworld_rawimport_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/helloworldrawimportplugin.cpp)

add_library(RawImport_HelloWorld_Plugin
            MODULE ${helloworld_rawimport_SRCS})

set_target_properties(RawImport_HelloWorld_Plugin PROPERTIES PREFIX "")

target_link_libraries(RawImport_HelloWorld_Plugin
                      Digikam::digikamcore

                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
)

MACRO_ADD_PLUGIN_INSTALL_TARGET(RawImport_HelloWorld_Plugin rawimport)

# ---

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
