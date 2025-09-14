cmake_minimum_required(VERSION 3.30)
project(MarioKartTopGenerator)

#  INITIALIZATION
# ------------------------------------------------------------------------------

set(APP_NAME "${PROJECT_NAME}")
set(APP_DIR $<TARGET_FILE_DIR:${APP_NAME}>)
set(UPD_NAME "${PROJECT_NAME}_Updater")

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

if(WIN32)
    enable_language("RC")
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_icon.rc")
    set(UPD_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/upd_icon.rc")
endif()

#  APPLICATION
# ------------------------------------------------------------------------------

add_subdirectory(${LIB_DIR}/OpenXLSX)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(minizip REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)
qt_standard_project_setup()

set(APP_SRC_FILES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Update/Manager.cpp
    ${SRC_DIR}/Update/Request.cpp
    ${SRC_DIR}/Data/Data.cpp
    ${SRC_DIR}/Data/Assets.cpp
    ${SRC_DIR}/Data/Player.cpp
    ${SRC_DIR}/Data/Winner.cpp
    ${SRC_DIR}/Data/Dictionary/Background.cpp
    ${SRC_DIR}/Data/Dictionary/Character.cpp
    ${SRC_DIR}/Logic/Render.cpp
    ${SRC_DIR}/Logic/Winner.cpp
    ${INC_DIR}/UI/Windows/Primary.hpp
    ${SRC_DIR}/UI/Windows/Primary/Core.cpp
    ${SRC_DIR}/UI/Windows/Primary/Winner/Page.cpp
    ${SRC_DIR}/UI/Windows/Primary/Winner/BoxAutoLoad.cpp
    ${SRC_DIR}/UI/Windows/Primary/Winner/BoxInfo.cpp
    ${SRC_DIR}/UI/Windows/Primary/Winner/BoxRank.cpp
    ${SRC_DIR}/UI/Windows/Primary/Bracket/Page.cpp
    ${INC_DIR}/UI/Windows/PlayerSettings.hpp
    ${SRC_DIR}/UI/Windows/PlayerSettings/Info.cpp
    ${SRC_DIR}/UI/Windows/PlayerSettings/Solo.cpp
    ${SRC_DIR}/UI/Windows/PlayerSettings/Duo.cpp
    ${INC_DIR}/UI/Windows/Notification.hpp
    ${SRC_DIR}/UI/Windows/Notification.cpp
    ${SRC_DIR}/UI/Tools/Browser.cpp
    ${INC_DIR}/UI/Tools/Browser.hpp
    ${SRC_DIR}/UI/Tools/GroupBox.cpp
    ${INC_DIR}/UI/Tools/GroupBox.hpp
    ${SRC_DIR}/UI/Tools/Randomizer.cpp
    ${INC_DIR}/UI/Tools/Randomizer.hpp
    ${SRC_DIR}/UI/Tools/Window.cpp
    ${INC_DIR}/UI/Tools/Window.hpp
)

qt_add_resources(APP_RSC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_assets.qrc")

add_executable(${APP_NAME} ${APP_SRC_FILES} ${APP_RSC_FILES} ${APP_ICON_RESOURCE})

target_include_directories(${APP_NAME} PRIVATE include)

target_link_libraries(${APP_NAME} PRIVATE
    OpenXLSX::OpenXLSX
    nlohmann_json::nlohmann_json
    CURL::libcurl
    minizip::minizip
    Qt6::Widgets
    Qt6::Multimedia
)

#  UPDATER
# ------------------------------------------------------------------------------

set(UPD_SRC_FILES
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Update/Main.cpp
    ${SRC_DIR}/Update/Manager.cpp
    ${SRC_DIR}/Update/Request.cpp
)

add_executable(${UPD_NAME} ${UPD_SRC_FILES} ${UPD_ICON_RESOURCE})

target_include_directories(${UPD_NAME} PRIVATE include)

target_link_libraries(${UPD_NAME} PRIVATE
    CURL::libcurl
    minizip::minizip
)

#  POST BUILD
# ------------------------------------------------------------------------------

# set(ASSETS_TO_COPY
#     "Assets"
#     "Template"
# )

# add_custom_command(
#         TARGET ${APP_NAME}
#         POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E make_directory ${PLUGIN_DIR}
#         COMMAND ${CMAKE_COMMAND} -E copy "${_VCPKG_INSTALLED_DIR}/x64-windows/Qt6/plugins/platforms/qminimal.dll" ${PLUGIN_DIR}
#         COMMAND ${CMAKE_COMMAND} -E copy "${_VCPKG_INSTALLED_DIR}/x64-windows/Qt6/plugins/platforms/qoffscreen.dll" ${PLUGIN_DIR}
#         COMMAND ${CMAKE_COMMAND} -E copy "${_VCPKG_INSTALLED_DIR}/x64-windows/Qt6/plugins/platforms/qwindows.dll" ${PLUGIN_DIR}
# )

# foreach(ITEM ${ASSETS_TO_COPY})
#     add_custom_command(
#         TARGET ${APP_NAME}
#         POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E echo "copying ${CMAKE_SOURCE_DIR}/${ITEM} into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}..."
#         COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/${ITEM}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${ITEM}"
#     )
# endforeach()


set(QT_BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/x64-windows")
set(QT_PLUGINS_DIR "Qt6/plugins")
set(QT_DIR "$<IF:$<CONFIG:Debug>,${QT_BASE_DIR}/debug/${QT_PLUGINS_DIR},${QT_BASE_DIR}/${QT_PLUGINS_DIR}>")

add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_DIR}/platforms
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_DIR}/platforms/qwindows$<$<CONFIG:Debug>:d>.dll" ${APP_DIR}/platforms
    COMMAND ${CMAKE_COMMAND} -E make_directory ${APP_DIR}/multimedia
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QT_DIR}/multimedia/windowsmediaplugin$<$<CONFIG:Debug>:d>.dll" ${APP_DIR}/multimedia
)

# # Copy image format plugins (jpeg + png)
# add_custom_command(TARGET ${APP_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory
#             $<TARGET_FILE_DIR:${APP_NAME}>/imageformats
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             "${QT_PLUGINS_DIR}/imageformats/qjpeg.dll"
#             $<TARGET_FILE_DIR:${APP_NAME}>/imageformats
#     # COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     #         "${QT_PLUGINS_DIR}/imageformats/qpng.dll"
#     #         $<TARGET_FILE_DIR:${APP_NAME}>/imageformats
# )
