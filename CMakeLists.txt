cmake_minimum_required(VERSION 3.30)
project(GamenChillApp VERSION 3.3.0)

#  LIBRARY
# ------------------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    GoGuLib
    GIT_REPOSITORY https://github.com/Mr-GoGu/GoGuLib.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(GoGuLib)

FetchContent_Declare(
    OpenXLSX
    GIT_REPOSITORY https://github.com/troldal/OpenXLSX.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(OpenXLSX)

#  VARIABLES
# ------------------------------------------------------------------------------

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(BIN_DIR "${OUT_DIR}/$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

#  PROJECT
# ------------------------------------------------------------------------------

set(SHARED_SRC
    ${SRC_DIR}/Shared/Data/Dictionary/Background.cpp
    ${SRC_DIR}/Shared/Data/Dictionary/Character.cpp
    ${SRC_DIR}/Shared/Data/Seeding/Player.cpp
    ${SRC_DIR}/Shared/Data/Seeding/Seeding.cpp
    ${SRC_DIR}/Shared/Data/Winner/Player.cpp
    ${SRC_DIR}/Shared/Data/Winner/Winner.cpp
    ${SRC_DIR}/Shared/Data/Assets.cpp
    ${SRC_DIR}/Shared/Data/Config.cpp
    ${SRC_DIR}/Shared/Data/Data.cpp
    ${SRC_DIR}/Shared/Logic/Bracket.cpp
    ${SRC_DIR}/Shared/Logic/ProgressTask.cpp
    ${SRC_DIR}/Shared/Logic/Render.cpp
    ${SRC_DIR}/Shared/Logic/Seeding.cpp
    ${SRC_DIR}/Shared/Logic/Winner.cpp
)

add_subdirectory(${SRC_DIR}/App)
add_subdirectory(${SRC_DIR}/GUI)
add_subdirectory(${SRC_DIR}/Update)
