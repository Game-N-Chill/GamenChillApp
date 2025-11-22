# GamenChillApp

GamenChillApp is an application for bracket render generation used by Game'n Chill association for their "Rififi sur le Circuit" tournaments.
The application has a GUI with lots of customization for Top 8 image generation or solo excel bracket generation
The application also has a console mode used for those who are sure their bracket si correctly setup and want to gain time
The application alse has an updater to run if you want to update the application

## Installation

### Depedencies required

- C++ compiler (Windows: [Visual Studio](https://visualstudio.microsoft.com/downloads/), Unix: [GCC](https://gcc.gnu.org/releases.html)/[Clang](https://releases.llvm.org/download.html))
- [CMake](https://cmake.org/download/)
- [Nasm](https://www.nasm.us/)
- [Pearl](https://www.perl.org/get.html)

### CMake installation

```bash
cmake --preset release
cmake --build build
```

### Third-Party Libraries

This project uses the following libraries:

- [Qt](https://github.com/qt) — licensed under the LGPL v3 license
- [OpenXLSX](https://github.com/troldal/OpenXLSX) — licensed under the BSD 3-Clause License
- [nlohmann-json](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT) — licensed under the MIT License
- [libcurl](https://github.com/curl/curl/blob/master/LICENSES/curl.txt) — licensed under the MIT License
- [minizip](https://github.com/madler/zlib/blob/master/LICENSE) — licensed under the MIT License
- [argparser](https://github.com/p-ranav/argparse/blob/master/LICENSE) — licensed under the MIT License


## Usage

### Console

```
Usage: GamenChillApp [--help] [--version] [--output VAR] [[--excel VAR]|[--url VAR]]

Optional arguments:
  -h, --help     shows help message and exits
  -v, --version  prints version information and exits
  -o, --output   Set the given output as the directory to where the content will be generated
  -e, --excel    Load excel path and create the solo Top 8 image
  -u, --url      Load and download content given by the url and create the duo Top 8 image
```
