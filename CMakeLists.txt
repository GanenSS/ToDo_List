cmake_minimum_required(VERSION 3.5)

project(ToDo_List VERSION 0.1 LANGUAGES CXX)

set(CMAKE_SOURCE_DIR ".")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package (SQLite3)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        src/mainSGS/main.cpp
        src/mainSGS/mainwindow.cpp
        src/widgets/inputdialog.cpp
        src/mainSGS/mainwindow.ui
        src/db/listdb.cpp
)

include_directories(src/widgets)
include_directories(src/db)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ToDo_List
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ToDo_List APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ToDo_List SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ToDo_List
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ToDo_List PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ToDo_List)
endif()
set_target_properties(ToDo_List PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ToDo_List
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ToDo_List)
endif()

if(QSLite3_FOUND)
    include_directories(${SQLITE_INCLUDE_DIRS})
    target_link_libraries(${OUT_TARGET} ${SQLITE3_LIBRARIES})
endif(QSLite3_FOUND)

target_link_libraries(ToDo_List PRIVATE Qt6::Sql)
