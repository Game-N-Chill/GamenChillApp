# Depedencies
```
Visual Studio
nasm
pearl
```

# Build
## Debug
```
git submodule update --init --recursive
cmake --preset windows-debug
cmake --build build
```

## Release
```
git submodule update --init --recursive
cmake --preset windows-release
cmake --build build
```
