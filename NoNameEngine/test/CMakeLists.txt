add_executable(UnitTests test_main.cpp)
target_link_libraries(UnitTests PRIVATE NoNameEngine)

enable_testing()
add_test(NAME UnitTests COMMAND UnitTests)