# MarioKartTopGenerator

MarioKartTopGenerator is an application for bracket render generation used by deerstalker association for their "Rififi sur le Circuit" tournaments.
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

## Commands list
```
help                                                                            Display this message
quit                                                                            Exit the program
list                                                                            Display all names for characters and tracks

title       <str>                                                               Change title
subtitle    <str>                                                               Change subtitre
date        <str>                                                               Change date (DD/MM/YYYY format)
count       <value>                                                             Change player count
url         <str>                                                               Change discord invitation link

load        <path/to/file>                                                      Load file for auto loading (.xlsx for solo|.json for duo)
player      <rank> <character> <name>                                           Change player information (solo only)
team        <rank> <name> <character_1> <player_1> <character_2> <player_2>     Change team information (duo only)
background  [name]                                                              Change background
skin        <solo|duo> [name] [rank]                                            Change skin for first or ranked player if precised (usefull for MIIs)
print       <solo|duo>                                                          Display all information of the render

dir         <path/to/dir>                                                       Change destination directory
create      <solo|duo>                                                          Generate render
```
