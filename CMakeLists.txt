cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(QTSDK)

file(GLOB_RECURSE QTSDK_SOURCES
"QTSDK/*.h"
"QTSDK/*.cpp"
)

add_executable(QTSDKEXEC ${QTSDK_SOURCES})

target_include_directories(QTSDKEXEC PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/QTSDK
${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/CIncludes
${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/RIncludes
${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/ComponentIncludes
)

target_link_libraries(QTSDKEXEC ${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/Libraries/CVClient.lib)
target_link_libraries(QTSDKEXEC ${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/Libraries/QTMLClient.lib)
target_link_libraries(QTSDKEXEC ${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/Libraries/QTSClient.lib)
target_link_libraries(QTSDKEXEC ${CMAKE_CURRENT_SOURCE_DIR}/QTSDK/Libraries/QTVR.lib)


project(scratch)

file(GLOB_RECURSE scratch_sources
"scratch/*.cpp"
"scratch/*.c"
)

add_executable(scratchexec ${scratch_sources})
target_include_directories(scratchexec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scratch)
target_include_directories(scratchexec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scratch/includes)