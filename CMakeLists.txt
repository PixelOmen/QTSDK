cmake_minimum_required(VERSION 3.25)
project(QTSDK)


file(GLOB_RECURSE QTSDK_SOURCES
"QTSDK/*.h"
"QTSDK/*.cpp"
)

add_executable(QTSDKEXEC ${QTSDK_SOURCES})
target_include_directories(QTSDKEXEC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QTSDK)


project(scratch)

file(GLOB_RECURSE QTSDK_SOURCES
"scratch/*.h"
"scratch/*.cpp"
)

add_executable(scratchexec ${QTSDK_SOURCES})
target_include_directories(scratchexec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scratch)