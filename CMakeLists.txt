cmake_minimum_required(VERSION 3.30)
project(MarioKartTopGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
    set(VCPKG_MANIFEST_MODE ON CACHE BOOL "" FORCE)
endif()

set(LIBRARY_DIR "lib")
# add_subdirectory(${LIBRARY_DIR}/OuiGine)
add_subdirectory(${LIBRARY_DIR}/SDL)
add_subdirectory(${LIBRARY_DIR}/SDL_image)
add_subdirectory(${LIBRARY_DIR}/OpenXLSX)

# find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SRC_FILES
    src/Main.cpp
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
# target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenXLSX::OpenXLSX)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Copy assets to the binary directory
set(ASSETS_TO_COPY "Assets")

foreach(ITEM ${ASSETS_TO_COPY})
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "copying ${CMAKE_SOURCE_DIR}/${ITEM} into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}..."
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/${ITEM}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}"
    )
endforeach()
