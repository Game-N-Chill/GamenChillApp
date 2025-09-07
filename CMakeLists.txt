cmake_minimum_required(VERSION 3.30)
project(MarioKartTopGenerator)

#  INITIALIZATION
# ------------------------------------------------------------------------------

set(APP_NAME "${PROJECT_NAME}")
set(APP_DIR $<TARGET_FILE_DIR:${APP_NAME}>)
set(UPD_NAME "${PROJECT_NAME}_Updater")

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

if(WIN32)
    enable_language("RC")
    set(APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_icon.rc")
    set(UPD_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/upd_icon.rc")
endif()

#  APPLICATION
# ------------------------------------------------------------------------------

add_subdirectory(${LIB_DIR}/SDL)
add_subdirectory(${LIB_DIR}/SDL_image)
add_subdirectory(${LIB_DIR}/SDL_ttf)
add_subdirectory(${LIB_DIR}/OpenXLSX)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(minizip REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(APP_SRC_FILES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Generator/Shared.cpp
    ${SRC_DIR}/Generator/Solo.cpp
    ${SRC_DIR}/Generator/Duo.cpp
    ${SRC_DIR}/Commands/Help.cpp
    ${SRC_DIR}/Commands/Version.cpp
    ${SRC_DIR}/Commands/Quit.cpp
    ${SRC_DIR}/Commands/List.cpp
    ${SRC_DIR}/Commands/Title.cpp
    ${SRC_DIR}/Commands/SubTitle.cpp
    ${SRC_DIR}/Commands/Date.cpp
    ${SRC_DIR}/Commands/Count.cpp
    ${SRC_DIR}/Commands/Url.cpp
    ${SRC_DIR}/Commands/Load.cpp
    ${SRC_DIR}/Commands/Player.cpp
    ${SRC_DIR}/Commands/Team.cpp
    ${SRC_DIR}/Commands/Background.cpp
    ${SRC_DIR}/Commands/Skin.cpp
    ${SRC_DIR}/Commands/Print.cpp
    ${SRC_DIR}/Commands/Dir.cpp
    ${SRC_DIR}/Commands/Create.cpp
    ${SRC_DIR}/Render/Canva.cpp
    ${SRC_DIR}/Render/Image.cpp
    ${SRC_DIR}/Render/Object.cpp
    ${SRC_DIR}/Render/Text.cpp
    ${SRC_DIR}/Logic/LineParser.cpp
    ${SRC_DIR}/Logic/Terminal.cpp
    ${SRC_DIR}/Update/Updater.cpp
    ${SRC_DIR}/Update/Request.cpp
)

add_executable(${APP_NAME} ${APP_SRC_FILES} ${APP_ICON_RESOURCE})

target_include_directories(${APP_NAME} PRIVATE include)

target_link_libraries(${APP_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${APP_NAME} PRIVATE SDL3_image::SDL3_image)
target_link_libraries(${APP_NAME} PRIVATE SDL3_ttf::SDL3_ttf)
target_link_libraries(${APP_NAME} PRIVATE OpenXLSX::OpenXLSX)
target_link_libraries(${APP_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${APP_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${APP_NAME} PRIVATE minizip::minizip)
target_link_libraries(${APP_NAME} PRIVATE Qt6::Widgets)

#  UPDATER
# ------------------------------------------------------------------------------

set(UPD_SRC_FILES
    ${SRC_DIR}/Utils.cpp
    ${SRC_DIR}/Update/Main.cpp
    ${SRC_DIR}/Update/Updater.cpp
    ${SRC_DIR}/Update/Request.cpp
)

add_executable(${UPD_NAME} ${UPD_SRC_FILES} ${UPD_ICON_RESOURCE})

target_include_directories(${UPD_NAME} PRIVATE include)

target_link_libraries(${UPD_NAME} PRIVATE CURL::libcurl)
target_link_libraries(${UPD_NAME} PRIVATE minizip::minizip)

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
