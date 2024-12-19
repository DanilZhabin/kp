cmake_minimum_required(VERSION 3.16)

project(untitled2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the location of Qt if it's not in the system path
# set(Qt6_DIR "C:/Qt/6.6.1/mingw_64/lib/cmake/Qt6") # Change this path to where your Qt install is

find_package(Qt6 COMPONENTS Widgets REQUIRED) # Use Qt6 specifically

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        growthdata.cpp
        growthdata.h
)

qt_add_executable(untitled2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)

target_link_libraries(untitled2 PRIVATE Qt6::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(Qt6_VERSION VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.untitled2)
endif()

set_target_properties(untitled2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


include(GNUInstallDirs)
install(TARGETS untitled2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(Qt6_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled2)
endif()
