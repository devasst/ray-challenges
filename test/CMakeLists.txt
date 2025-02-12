ENABLE_TESTING()

INCLUDE(FetchContent)
FETCHCONTENT_DECLARE(
        googletest
        URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip
)
FETCHCONTENT_MAKEAVAILABLE(googletest)

ADD_EXECUTABLE(hello_test hello_test.cpp)

TARGET_LINK_LIBRARIES(hello_test GTest::gtest_main)

INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(hello_test)