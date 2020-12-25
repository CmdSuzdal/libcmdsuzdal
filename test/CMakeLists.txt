enable_testing()
include(CTest)

# Add gtest/gmock support
include(addgtestsupport)

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

add_executable(testcmdsuzdal
    bitboardtest.cpp
    armytest.cpp
    fenrecordtest.cpp
    chessboardtest.cpp
)

# includes the base project includes
target_include_directories(testcmdsuzdal
    PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Add the dependency to the target under test
target_link_libraries(testcmdsuzdal PRIVATE cmdsuzdal)

target_compile_options(testcmdsuzdal PRIVATE -Werror)
target_compile_features(testcmdsuzdal PRIVATE cxx_std_17)

target_link_libraries(testcmdsuzdal PRIVATE gtest gmock_main)
add_test(NAME cmdsuzdal_test COMMAND testcmdsuzdal)
