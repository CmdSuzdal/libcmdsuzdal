enable_testing()
include(CTest)

# Add gtest/gmock support
include(addgtestsupport)

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

add_executable(testcmdsuzdal_bbdefines    bbdefinestest.cpp)
add_executable(testcmdsuzdal_bitboard     bitboardtest.cpp)
add_executable(testcmdsuzdal_chessmove    chessmovetest.cpp)
add_executable(testcmdsuzdal_army         armytest.cpp)
add_executable(testcmdsuzdal_fenrecord    fenrecordtest.cpp)
add_executable(testcmdsuzdal_chessboard   chessboardtest.cpp)
add_executable(testcmdsuzdal_chessgame    chessgametest.cpp)
add_executable(testcmdsuzdal_randomengine randomenginetest.cpp)

# includes the base project includes
target_include_directories(testcmdsuzdal_bbdefines    PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_bitboard     PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_chessmove    PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_army         PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_fenrecord    PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_chessboard   PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_chessgame    PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(testcmdsuzdal_randomengine PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Add the dependency to the target under test
target_link_libraries(testcmdsuzdal_bbdefines    PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_bitboard     PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_chessmove    PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_army         PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_fenrecord    PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_chessboard   PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_chessgame    PRIVATE cmdsuzdal)
target_link_libraries(testcmdsuzdal_randomengine PRIVATE cmdsuzdal)

target_compile_options(testcmdsuzdal_bbdefines     PRIVATE -Werror)
target_compile_options(testcmdsuzdal_bitboard      PRIVATE -Werror)
target_compile_options(testcmdsuzdal_chessmove     PRIVATE -Werror)
target_compile_options(testcmdsuzdal_army          PRIVATE -Werror)
target_compile_options(testcmdsuzdal_fenrecord     PRIVATE -Werror)
target_compile_options(testcmdsuzdal_chessboard    PRIVATE -Werror)
target_compile_options(testcmdsuzdal_chessgame     PRIVATE -Werror)
target_compile_options(testcmdsuzdal_randomengine  PRIVATE -Werror)

target_compile_features(testcmdsuzdal_bbdefines    PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_bitboard     PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_chessmove    PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_army         PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_fenrecord    PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_chessboard   PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_chessgame    PRIVATE cxx_std_17)
target_compile_features(testcmdsuzdal_randomengine PRIVATE cxx_std_17)

target_link_libraries(testcmdsuzdal_bbdefines    PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_bitboard     PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_chessmove    PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_army         PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_fenrecord    PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_chessboard   PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_chessgame    PRIVATE gtest gmock_main)
target_link_libraries(testcmdsuzdal_randomengine PRIVATE gtest gmock_main)

add_test(NAME BBDefinesTest    COMMAND testcmdsuzdal_bbdefines   )
add_test(NAME BitBoardTest     COMMAND testcmdsuzdal_bitboard    )
add_test(NAME ChessMoveTest    COMMAND testcmdsuzdal_chessmove   )
add_test(NAME ArmyTest         COMMAND testcmdsuzdal_army        )
add_test(NAME FenRecordTest    COMMAND testcmdsuzdal_fenrecord   )
add_test(NAME ChessBoardTest   COMMAND testcmdsuzdal_chessboard  )
add_test(NAME ChessGameTest    COMMAND testcmdsuzdal_chessgame   )
add_test(NAME RandomEngineTest COMMAND testcmdsuzdal_randomengine)
