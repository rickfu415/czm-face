# Find GTest package
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    message(STATUS "Google Test not found. Tests will be disabled.")
    return()
endif()

# Create test executable
add_executable(corecode_tests
    core_tests.cpp
)

# Link against GTest and our library
target_link_libraries(corecode_tests
    PRIVATE
        GTest::GTest
        GTest::Main
        corecode
)

# Add test
add_test(NAME corecode_tests COMMAND corecode_tests) 