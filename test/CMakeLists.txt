cmake_minimum_required(VERSION 3.9.0)

add_executable(gzCrypt_tests test.cpp)
target_link_libraries(gzCrypt_tests PUBLIC gzCrypt)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(gzCrypt_tests PUBLIC GTest::main)

find_package(GMock CONFIG REQUIRED)
target_link_libraries(gzCrypt_tests PUBLIC GMock::gmock)

include(GoogleTest)
gtest_discover_tests(gzCrypt_tests
    TEST_LIST test_targets)
