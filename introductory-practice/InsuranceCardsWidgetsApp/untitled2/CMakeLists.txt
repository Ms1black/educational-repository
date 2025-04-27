cmake_minimum_required(VERSION 3.5)

project(untitled2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Qt 5 или 6
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)


set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ChartDialog.cpp
    ChartDialog.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ChartDialog.ui
    )
else()
    if(ANDROID)
        add_library(untitled2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(untitled2
            ${PROJECT_SOURCES}
            ${CMAKE_CURRENT_SOURCE_DIR}/ChartDialog.ui
        )
    endif()
endif()

target_link_libraries(untitled2 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
)

