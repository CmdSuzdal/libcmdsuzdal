cmake_minimum_required(VERSION 3.8)

# ***************************************************************
project(cmdsuzdal VERSION 0.0.1)
# ***************************************************************

# This is necessary to use cmake_addons. It is assumed that
# cmake_addons component is placed in the base directory of the
# project inside the cmake_addons directory (e.g. using a
# git submodule)
# Find cmake_addons at: https://github.com/fpiantini/cmake_addons
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_addons)

# ---------------------------------------------------------------
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/bbdefines.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/bitboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/army.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/fenrecord.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/chessboard.h
)

# ---------------------------------------------------------------
# Current Target library target definition and related settings
# A library can be defined STATIC or SHARED
add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE
    src/bitboard.cpp
    src/army.cpp
    src/fenrecord.cpp
    src/chessboard.cpp
)

# ------------------------------------------------------------------
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # added to take into account private headers in src directory
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# ------------------------------------------------------------------
# Installation
install(FILES ${HEADERS} DESTINATION ${cmakeInstallPrefix}/include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}_export DESTINATION ${cmakeInstallPrefix}/lib)
install(EXPORT ${PROJECT_NAME}_export FILE ${PROJECT_NAME}-config.cmake DESTINATION ${cmakeInstallPrefix}/lib)

# ------------------------------------------------------------------
if (ENABLE_COVERAGE_TEST)
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        append_coverage_compiler_flags()
        setup_target_for_coverage_gcovr_html(
          NAME ${PROJECT_NAME}_coverage
          EXECUTABLE ctest
          EXCLUDE ${PROJECT_SOURCE_DIR}/test/*
                  ${CMAKE_CURRENT_BINARY_DIR}/*
        )
    endif()
endif()

enable_testing()
add_subdirectory(test)

