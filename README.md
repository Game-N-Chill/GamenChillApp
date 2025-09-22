# GamenChillApp

GamenChillApp is an application for bracket render generation used by deerstalker association for their "Rififi sur le Circuit" tournaments.
The application is a terminal with it's own set a commands

## Installation

### Depedencies

- [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- [nasm](https://www.nasm.us/)
- [pearl](https://www.perl.org/get.html)

### CMake installation

```bash
git submodule update --init --recursive
cmake --preset windows-release
cmake --build build
```

### Third-Party Libraries

This project uses the following libraries:

- [Qt](https://github.com/qt) — licensed under the LGPL v3 license
- [OpenXLSX](https://github.com/troldal/OpenXLSX) — licensed under the BSD 3-Clause License
- [nlohmann-json](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT) — licensed under the MIT License
- [libcurl](https://github.com/curl/curl/blob/master/LICENSES/curl.txt) — licensed under the MIT License
- [minizip](https://github.com/madler/zlib/blob/master/LICENSE) — licensed under the MIT License
