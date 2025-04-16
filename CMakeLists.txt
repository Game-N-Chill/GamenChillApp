cmake_minimum_required(VERSION 3.30)
project(MarioKartTopGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

set(LIBRARY_DIR "lib")
set(LIBRARY_DIR_SDL "lib/OuiGine/lib")
# add_subdirectory(${LIBRARY_DIR}/OuiGine)
add_subdirectory(${LIBRARY_DIR_SDL}/SDL)
add_subdirectory(${LIBRARY_DIR_SDL}/SDL_image)
add_subdirectory(${LIBRARY_DIR}/OpenXLSX)

set(SRC_FILES
    src/Main.cpp
)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenXLSX::OpenXLSX)

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
