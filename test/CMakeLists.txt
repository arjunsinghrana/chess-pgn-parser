include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(
  test_chess_board
  test_chess_board.cpp
)

target_link_libraries(
  test_chess_board
  GTest::gtest_main
  chessBoard
  chessTurn
  chessMove
  utils
)

include(GoogleTest)
gtest_discover_tests(test_chess_board)
