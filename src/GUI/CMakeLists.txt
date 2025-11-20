cmake_minimum_required(VERSION 3.30)
project(GamenChillApp.GUI VERSION 1.0.0)

message(STATUS "Entering GUI source directory")

set(GUI_NAME "GamenChillApp_GUI")

if(WIN32)
    enable_language("RC")
    set(GUI_ICON "${CMAKE_SOURCE_DIR}/resources/app_icon.rc")
endif()

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)
qt_standard_project_setup()

set(GUI_SRC
    Main.cpp
    Windows/Common/Common.cpp
    ${INC_DIR}/GUI/Windows/Common/Notification.hpp
    Windows/Common/Notification.cpp
    ${INC_DIR}/GUI/Windows/Common/ProgressBar.hpp
    Windows/Common/ProgressBar.cpp
    ${INC_DIR}/GUI/Windows/Primary.hpp
    Windows/Primary/Core.cpp
    Windows/Primary/Menu/Bar.cpp
    Windows/Primary/Tabs/Winner/Page.cpp
    Windows/Primary/Tabs/Winner/TabSolo.cpp
    Windows/Primary/Tabs/Winner/TabDuo.cpp
    Windows/Primary/Tabs/Winner/BoxInfo.cpp
    Windows/Primary/Tabs/Winner/BoxLoadExcel.cpp
    Windows/Primary/Tabs/Winner/BoxLoadWeb.cpp
    Windows/Primary/Tabs/Winner/BoxRank.cpp
    Windows/Primary/Tabs/Bracket/Page.cpp
    Windows/Primary/Tabs/Bracket/Callback.cpp
    ${INC_DIR}/GUI/Windows/Secondary/PlayerSettings.hpp
    Windows/Secondary/PlayerSettings/Info.cpp
    Windows/Secondary/PlayerSettings/Solo.cpp
    Windows/Secondary/PlayerSettings/Duo.cpp
    ${INC_DIR}/GUI/Windows/Secondary/PlayerBracket.hpp
    Windows/Secondary/PlayerBracket.cpp
    Tools/Browser.cpp
    ${INC_DIR}/GUI/Tools/Browser.hpp
    Tools/GroupBox.cpp
    ${INC_DIR}/GUI/Tools/GroupBox.hpp
    Tools/Randomizer.cpp
    ${INC_DIR}/GUI/Tools/Randomizer.hpp
    Tools/Window.cpp
    ${INC_DIR}/GUI/Tools/Window.hpp
)

qt_add_resources(GUI_RESOURCES "${CMAKE_SOURCE_DIR}/resources/app_assets.qrc")

add_executable(${GUI_NAME} ${SHARED_SRC} ${GUI_SRC} ${GUI_RESOURCES} ${GUI_ICON})

target_include_directories(${GUI_NAME} PRIVATE ${INC_DIR})

target_link_libraries(${GUI_NAME}
    PRIVATE
        GoGuLib::GoGuLib
        OpenXLSX::OpenXLSX
        nlohmann_json::nlohmann_json
        CURL::libcurl
        Qt6::Widgets
        Qt6::Multimedia
)

if (WIN32)
    target_link_options(${GUI_NAME} PRIVATE $<$<CONFIG:Debug>:/SUBSYSTEM:CONSOLE>)
    target_link_options(${GUI_NAME} PRIVATE $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>)
endif()
