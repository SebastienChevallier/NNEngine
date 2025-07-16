add_executable(NoNameEngine_tests test_main.cpp)

# Link the engine library
# The engine target is NoNameEngine defined in parent directory

target_link_libraries(NoNameEngine_tests PRIVATE NoNameEngine)

add_test(NAME NoNameEngineTests COMMAND NoNameEngine_tests)
