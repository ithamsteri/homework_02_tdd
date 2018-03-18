cmake_minimum_required(VERSION 3.2)

# check environment variable TRAVIS_BUILD_NUMBER
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(ipfilter VERSION 0.0.${VERSION_BUILD})

# set variables for directories with source code
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/tests")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter
    ${SOURCE_PATH}/main.cpp
    ${SOURCE_PATH}/Pool.cpp
)
add_executable(pool_test
    ${TEST_PATH}/Pool.test.cpp
    ${SOURCE_PATH}/Pool.cpp
)

set_target_properties(ip_filter pool_test PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# BOOST_TEST_DYN_LINK - Define this flag to link against
# the Unit Test Framework shared library
set_target_properties(pool_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
  INCLUDE_DIRECTORIES ${SOURCE_PATH}
  LINK_LIBRARIES ${Boost_LIBRARIES}
)

enable_testing()

add_test(PoolTest pool_test)
