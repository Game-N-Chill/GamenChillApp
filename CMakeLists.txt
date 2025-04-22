cmake_minimum_required(VERSION 3.30)
project(MarioKartTopGenerator)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

add_subdirectory(${LIB_DIR}/SDL)
add_subdirectory(${LIB_DIR}/SDL_image)
add_subdirectory(${LIB_DIR}/SDL_ttf)
add_subdirectory(${LIB_DIR}/OpenXLSX)

find_package(nlohmann_json REQUIRED)
find_package(argparse REQUIRED)

set(SRC_FILES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Generator/Generator.cpp
    ${SRC_DIR}/Generator/Player.cpp
    ${SRC_DIR}/Commands/Count.cpp
    ${SRC_DIR}/Commands/Create.cpp
    ${SRC_DIR}/Commands/Date.cpp
    ${SRC_DIR}/Commands/Dir.cpp
    ${SRC_DIR}/Commands/Help.cpp
    ${SRC_DIR}/Commands/Load.cpp
    ${SRC_DIR}/Commands/Player.cpp
    ${SRC_DIR}/Commands/Print.cpp
    ${SRC_DIR}/Commands/Quit.cpp
    ${SRC_DIR}/Commands/Random.cpp
    ${SRC_DIR}/Commands/SubTitle.cpp
    ${SRC_DIR}/Commands/Title.cpp
    ${SRC_DIR}/Commands/Url.cpp
    ${SRC_DIR}/Render/Canva.cpp
    ${SRC_DIR}/Render/Image.cpp
    ${SRC_DIR}/Render/Object.cpp
    ${SRC_DIR}/Render/Text.cpp
    ${SRC_DIR}/Logic/LineParser.cpp
    ${SRC_DIR}/Logic/Terminal.cpp
)

if(WIN32)
    enable_language("RC")
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_icon.rc")
endif()

add_executable(${PROJECT_NAME} ${SRC_FILES} ${APP_ICON_RESOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenXLSX::OpenXLSX)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE argparse::argparse)

# Copy assets to the binary directory
set(TO_COPY
    "Assets"
    "Template"
)

foreach(ITEM ${TO_COPY})
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "copying ${CMAKE_SOURCE_DIR}/${ITEM} into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/${ITEM}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}"
    )
endforeach()
