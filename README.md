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

- CMake           >= 3.1.0      (https://cmake.org/)            All plugin types
- Qt              >= 5.6.0      (https://www.qt.io/)            All plugin types
- DigikamCore     >= 6.4.0      (https://www.digikam.org)       Generic, Editor, and RawImport plugins
- DigikamDatabase >= 6.4.0      (https://www.digikam.org)       BQM plugin only
- DigikamGui      >= 6.4.0      (https://www.digikam.org)       BQM plugin only

Notes:

- plugins do not depend on KF5 framework.
- Generic, Editor and Bqm plugins can be compiled with digiKam 6.3.0 API. Only RawImport needs 6.4.0.

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
