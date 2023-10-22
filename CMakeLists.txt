cmake_minimum_required(VERSION 3.5)

project(globalHometask2_1_qt_v VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (LINUX)
    set(CMAKE_PREFIX_PATH "/home/oracl/Qt/6.6.0/gcc_64/lib/cmake") # your path for cmake
endif (LINUX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(globalHometask2_1_qt_v
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        headers/conf.h src/conf.cpp
        headers/player.h src/player.cpp
        headers/enemy.h
        headers/bot.h src/bot.cpp
        headers/ship_wig.h src/ship_wig.cpp
        headers/ship_structs.h
        headers/game.h src/game.cpp
        headers/other.h
        src/other.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET globalHometask2_1_qt_v APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(globalHometask2_1_qt_v SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(globalHometask2_1_qt_v
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(globalHometask2_1_qt_v PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.globalHometask2_1_qt_v)
endif()
set_target_properties(globalHometask2_1_qt_v PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS globalHometask2_1_qt_v
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(globalHometask2_1_qt_v)
endif()
