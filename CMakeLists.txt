cmake_minimum_required(VERSION 2.8)
project(nuklear_demo)

set(PROGRAM nuklear_demo)
# make sure could include ui.h and ui.c
include_directories(.)

if(WIN32)
add_executable(${PROGRAM} ../nuklear/gdip.c)
target_link_libraries(${PROGRAM}
    gdiplus
    user32
    shlwapi
)
else()
find_package(PkgConfig REQUIRED)
pkg_check_modules(XFT REQUIRED xft)

add_definitions(-DNK_XLIB_USE_XFT)
include_directories(${XFT_INCLUDE_DIRS})

add_executable(${PROGRAM} ../nuklear/xlib_xft.c)
target_link_libraries(${PROGRAM}
    ${XFT_LIBRARIES}
    X11
    m
)
endif()
