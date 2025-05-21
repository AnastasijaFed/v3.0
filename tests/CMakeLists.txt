# Create the executable for the original tests
add_executable(student_tests student_test.cpp)

# Link your test executable with GoogleTest and your studentlib
target_link_libraries(student_tests PRIVATE studentlib gtest gtest_main)

# Register the test with CTest (this runs the tests in student_tests)
add_test(NAME StudentTests COMMAND student_tests)

# Create the executable for the Rule of Five tests
add_executable(student_rule_of_five_tests StudentClassRuleOfFiveTests.cpp)

# Link the Rule of Five test executable with GoogleTest and your studentlib
target_link_libraries(student_rule_of_five_tests PRIVATE studentlib gtest gtest_main)

# Register the test with CTest (this runs the tests in student_rule_of_five_tests)
add_test(NAME StudentRuleOfFiveTests COMMAND student_rule_of_five_tests)

add_executable(vector_test test_vector.cpp)
target_link_libraries(vector_test PRIVATE studentlib gtest gtest_main)
add_test(NAME VectorTest COMMAND vector_test)