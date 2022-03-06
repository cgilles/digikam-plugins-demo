### Description:

This repository guest some demo codes to write new external digiKam plugins (Digikam::DPlugin).
It provides 4 "Hello World" plugins as:

- Generic tool.
  [![](data/digikam_generic_helloworld.png "Hello World Generic Plugin")](data/digikam_generic_helloworld.png)

- Image Editor tool.
  [![](data/digikam_editor_helloworld.png "Hello World Editor Plugin")](data/digikam_editor_helloworld.png)

- Batch Queue Manager tool.
  [![](data/digikam_bqm_helloworld.png "Hello World BQM Plugin")](data/digikam_bqm_helloworld.png)

- Raw Import for Image Editor.
  This plugin open RAW file in editor with a simple command line call using dcraw tool.
  [![](data/digikam_rawimport_helloworld.png "Hello World RawImport Plugin")](data/digikam_rawimport_helloworld.png)

### Dependencies:

- CMake           >= 3.16       (https://cmake.org/)            All plugin types
- Qt5             >= 5.6.0      (https://www.qt.io/)            All plugin types
- Qt6             >= 6.2.3      (https://www.qt.io/)            All plugin types
- DigikamCore     >= 7.0.0      (https://www.digikam.org)       Generic, Editor, and RawImport plugins
- DigikamDatabase >= 7.0.0      (https://www.digikam.org)       BQM plugin only
- DigikamGui      >= 7.0.0      (https://www.digikam.org)       BQM plugin only

Notes:

- Plugins do not depend on KF5 framework.
- Plugins can be compiled with Qt5 or Qt6.

### Compilation:

```
# ./bootstrap.sh
# cd build
# make
```

### Install:

```
# cd build
# sudo make install/fast
```

### Uninstall:

```
# cd build
# sudo make uninstall
```
