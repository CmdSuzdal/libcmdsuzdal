cmake_minimum_required(VERSION 3.8)

# ***************************************************************
set(CTGT cmdsuzdal)
project(${CTGT} VERSION 0.0.1)
# ***************************************************************

# This is necessary to use cmake_addons. It is assumed that
# cmake_addons component is placed in the base directory of the
# project inside the cmake_addons directory (e.g. using a
# git submodule)
# Find cmake_addons at: https://github.com/fpiantini/cmake_addons
set(cmakeAddonsDir "${CMAKE_CURRENT_SOURCE_DIR}/cmake_addons")

# ---------------------------------------------------------------
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${CTGT}/bbdefines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${CTGT}/bitboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${CTGT}/fenrecord.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${CTGT}/army.h
)

# ---------------------------------------------------------------
# Current Target library target definition and related settings
# A library can be defined STATIC or SHARED
add_library(${CTGT} SHARED)

target_sources(${CTGT} PRIVATE
    src/bitboard.cpp
    src/fenrecord.cpp
    src/army.cpp
)

# ------------------------------------------------------------------
target_include_directories(${CTGT}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # added to take into account private headers in src directory
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${CTGT} PRIVATE -Werror)
target_compile_features(${CTGT} PRIVATE cxx_std_17)

# ------------------------------------------------------------------
# Installation
install(FILES ${HEADERS} DESTINATION ${cmakeInstallPrefix}/include/${CTGT})
install(TARGETS ${CTGT} EXPORT ${CTGT}_export DESTINATION ${cmakeInstallPrefix}/lib)
install(EXPORT ${CTGT}_export FILE ${CTGT}-config.cmake DESTINATION ${cmakeInstallPrefix}/lib)

# ------------------------------------------------------------------
enable_testing()
add_subdirectory(test)

