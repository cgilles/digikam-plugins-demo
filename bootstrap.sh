#!/bin/bash

# Copyright (c) 2008-2020, Gilles Caulier, <caulier dot gilles at gmail dot com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

rm -rf build
mkdir build
cd build

cmake . \
      -DCMAKE_INSTALL_PREFIX=/usr \
      -DCMAKE_BUILD_TYPE=Debug \
      -G"Unix Makefiles" \
      -Wno-dev \
      ..
