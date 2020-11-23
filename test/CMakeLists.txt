include(CTest)

# Add gtest/gmock support
include(${cmakeAddonsDir}/addgtestsupport.cmake)

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

set(TESTCTGT testcmdsuzdal)

add_executable(${TESTCTGT}
    bitboardtest.cpp
)

# includes the base project includes
target_include_directories(${TESTCTGT}
    PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Add the dependency to the target under test
target_link_libraries(${TESTCTGT} PRIVATE ${CTGT})

target_compile_options(${TESTCTGT} PRIVATE -Werror)
target_compile_features(${TESTCTGT} PRIVATE cxx_std_11)

target_link_libraries(${TESTCTGT} PRIVATE gtest gmock_main)
add_test(NAME cmdsuzdal_test COMMAND ${TESTCTGT})

