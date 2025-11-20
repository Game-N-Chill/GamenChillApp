cmake_minimum_required(VERSION 3.30)
project(GamenChillApp.Updater VERSION 1.0.0)

message(STATUS "Entering Updater source directory")

set(UPD_NAME "GamenChillApp_Updater")

if(WIN32)
    enable_language("RC")
    set(UPD_ICON "${CMAKE_SOURCE_DIR}/resources/upd_icon.rc")
endif()

set(UPD_SRC
    Main.cpp
)

add_executable(${UPD_NAME} ${UPD_SRC} ${UPD_ICON})

target_include_directories(${UPD_NAME} PRIVATE ${INC_DIR})

target_link_libraries(${UPD_NAME}
    PRIVATE
        GoGuLib::GoGuLib
)

message(STATUS "Leaving Updater source directory")
