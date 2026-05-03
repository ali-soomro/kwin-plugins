find_package(Qt6 CONFIG REQUIRED COMPONENTS Core Gui)
find_package(KF6CoreAddons REQUIRED)
find_package(KF6WindowSystem REQUIRED)

# Get qmake path
find_program(QT_QMAKE_EXECUTABLE NAMES qmake6 qmake)
if(NOT QT_QMAKE_EXECUTABLE)
    message(FATAL_ERROR "qmake is not found.")
endif()

execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_PLUGINS
    OUTPUT_VARIABLE QT_PLUGINS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(QT_PLUGINS_DIR)
    message(STATUS "Qt6 plugin directory: ${QT_PLUGINS_DIR}")
else()
    message(FATAL_ERROR "Qt6 plugin directory cannot be detected.")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(decoration)
# roundedwindow uses removed KWin 6 APIs (KWin::connection(), data.shader); skipping
# add_subdirectory(roundedwindow)
