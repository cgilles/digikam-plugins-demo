#!/bin/bash

# Copyright (c) 2008-2024, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

# Halt and catch errors
set -eE
trap 'PREVIOUS_COMMAND=$THIS_COMMAND; THIS_COMMAND=$BASH_COMMAND' DEBUG
trap 'echo "FAILED COMMAND: $PREVIOUS_COMMAND"' ERR

# Uncomment and adjust lines below to use Clang compiler instead GCC
#export CC=/usr/bin/clang
#export CXX=/usr/bin/clang++

SOURCEDIR=$PWD
export BUILD_WITH_QT6=1

if [[ $BUILD_WITH_QT6 == 1 ]] ; then
    QTPATHS="qtpaths6"
else
    QTPATHS="qtpaths"
fi

# Prior Qt6 first. if failed try Qt5
# Customized install Qt path compiled with https://github.com/cgilles/digikam-install-deps.git

if   [[ -d /opt/qt6 && $BUILD_WITH_QT6 == 1 ]] ; then

    export Qt6_DIR=/opt/qt6

    QTPATHS="/opt/qt6/bin/qtpaths6"

    export CMAKE_BINARY=/opt/qt6/bin/cmake

elif [ -d /opt/qt5 ] ; then

    export Qt5_DIR=/opt/qt5

    QTPATHS="/opt/qt5/bin/qtpaths"

    export CMAKE_BINARY=/opt/qt5/bin/cmake

    export BUILD_WITH_QT6=0

fi

command -v $QTPATHS >/dev/null 2>&1 || { echo >&2 "This script require $QTPATHS CLI tool from Qt project but it's not installed. Aborting."; exit 1; }

if [ "$1" == "" ]; then
    MAKEFILES_TYPE='Unix Makefiles'

    if [[ $BUILD_WITH_QT6 == 1 ]] ; then
        BUILDDIR=$PWD"/build.qt6"
    else
        BUILDDIR=$PWD"/build"
    fi

    MESSAGE="Now run make in $BUILDDIR."

elif [ "$1" == "--ninja" ]; then

    MAKEFILES_TYPE='Ninja'

    if [[ $BUILD_WITH_QT6 == 1 ]] ; then
        BUILDDIR=$PWD"/build.qt6"
    else
        BUILDDIR=$PWD"/build"
    fi

    MESSAGE="Now run ninja in $BUILDDIR."

elif [ "$1" == "--eclipse" ]; then

    MAKEFILES_TYPE='Eclipse CDT4 - Unix Makefiles'
    ADDITIONAL_CMAKE_FLAGS="-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=ON $ADDITIONAL_CMAKE_FLAGS"
    BUILDDIR=$PWD"-debug"
    MESSAGE="
Now import these folders as existing projects into Eclipse without
copying source into the workspace:
$SOURCEDIR
$BUILDDIR"

else

    echo "Syntax: $0 [--eclipse] [--ninja]"
    echo "Run without arguments to create a Unix Makefile project in a build subdir."
    echo "Run with '--eclipse' to create an Eclipse IDE project and build source in a parallel directory."
    echo "Run with '--ninja' to create Ninja Makefile project in a build subdir."
    exit 1

fi

if [[ "$ARCH" = "x86_64" ]] ; then
    LIBPATH="lib64"
elif [[ "$ARCH" = "i686" ]] ; then
    LIBPATH="lib"
fi

QT_INSTALL_PREFIX=`$QTPATHS --install-prefix`
QT_PLUGIN_INSTALL_DIR=`$QTPATHS --plugin-dir`
export PATH=$QT_INSTALL_PREFIX/bin:$PATH

if [ "$CMAKE_BINARY" == "" ]; then
    CMAKE_BINARY="cmake"
fi

if [ "$DIGIKAM_INSTALL_PREFIX" == "" ]; then
    DIGIKAM_INSTALL_PREFIX="/usr"
else
    # bootstrap.local may have preset DIGIKAM_INSTALL_PREFIX.
    QT_PLUGIN_INSTALL_DIR=$DIGIKAM_INSTALL_PREFIX/$LIBPATH/plugins
    export PATH=$DIGIKAM_INSTALL_PREFIX/bin:$PATH
fi

export LD_LIBRARY_PATH=$DIGIKAM_INSTALL_PREFIX/$LIBPATH:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$DIGIKAM_INSTALL_PREFIX/$LIBPATH/pkgconfig:$PKG_CONFIG_PATH

echo "Qt      Install Path : $QT_INSTALL_PREFIX"
echo "digiKam Install Path : $DIGIKAM_INSTALL_PREFIX"
echo "CMake binary         : $CMAKE_BINARY"
echo "Build Directory      : $BUILDDIR"
echo "Build for Qt6        : $BUILD_WITH_QT6"
echo "ECM min version      : $ECM_MIN_VERSION"


mkdir -p $DIGIKAM_INSTALL_PREFIX
mkdir -p $BUILDDIR
cd $BUILDDIR

$CMAKE_BINARY -G "$MAKEFILES_TYPE" . \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_INSTALL_PREFIX=$DIGIKAM_INSTALL_PREFIX/ \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      $ADDITIONAL_CMAKE_FLAGS \
      -DBUILD_TESTING=ON \
      -DBUILD_WITH_QT6=$BUILD_WITH_QT6 \
      $SOURCEDIR && echo "$MESSAGE"
