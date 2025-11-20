cmake_minimum_required(VERSION 3.30)
project(GamenChillApp.App VERSION 1.0.0)

message(STATUS "Entering App source directory")

set(APP_NAME "GamenChillApp_Console")

if(WIN32)
    enable_language("RC")
    set(APP_ICON "${CMAKE_SOURCE_DIR}/resources/app_icon.rc")
endif()

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)
qt_standard_project_setup()

set(APP_SRC
    Main.cpp
)

qt_add_resources(GUI_RESOURCES "${CMAKE_SOURCE_DIR}/resources/app_assets.qrc")

add_executable(${APP_NAME} ${SHARED_SRC} ${APP_SRC} ${APP_ICON})

target_include_directories(${APP_NAME} PRIVATE ${INC_DIR})

target_link_libraries(${APP_NAME}
    PRIVATE
        GoGuLib::GoGuLib
        OpenXLSX::OpenXLSX
        nlohmann_json::nlohmann_json
        CURL::libcurl
        Qt6::Widgets
        Qt6::Multimedia
)

#  POST BUILD
# ------------------------------------------------------------------------------

set(ASSETS_TO_COPY
    "assets"
    "data"
    "template"
    "themes"
)

foreach(ITEM ${ASSETS_TO_COPY})
    add_custom_command(
        TARGET ${APP_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/resources/${ITEM}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}"
        COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory: ${ITEM}"
    )
endforeach()

set(VCPKG_BASE_DIR "$<IF:$<CONFIG:Debug>,${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/debug,${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows>")
set(VCPKG_BIN_DIR "${VCPKG_BASE_DIR}/bin")
set(VCPKG_QT_DIR "${VCPKG_BASE_DIR}/Qt6/plugins")

add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VCPKG_BIN_DIR}/libcrypto-3-x64.dll" ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VCPKG_BIN_DIR}/libssl-3-x64.dll" ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}/platforms
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VCPKG_QT_DIR}/platforms/qwindows$<$<CONFIG:Debug>:d>.dll" ${BIN_DIR}/platforms
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}/multimedia
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${VCPKG_QT_DIR}/multimedia/windowsmediaplugin$<$<CONFIG:Debug>:d>.dll" ${BIN_DIR}/multimedia
)

message(STATUS "Leaving App source directory")
