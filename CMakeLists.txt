cmake_minimum_required(VERSION 3.16)
project(asciivideoplayer)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOUIC ON)

pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavformat
        libavcodec
        libswresample
        libavutil
        )
pkg_check_modules(QT REQUIRED IMPORTED_TARGET
        Qt5Widgets
        Qt5Core
        Qt5Gui
        )

add_executable(${PROJECT_NAME}
        main.cpp
        ascii_parser.h ascii_parser.cpp my_label.cpp my_label.h ascii_drawer.cpp ascii_drawer.h player.cpp player.h)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)

target_link_libraries(${PROJECT_NAME}
        PkgConfig::LIBAV
        PkgConfig::QT
        )