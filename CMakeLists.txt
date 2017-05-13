cmake_minimum_required(VERSION 3.2)
project(Chip_Design)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror")
set(CMAKE_CXX_STANDARD 14)

set(MAIN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp)

file(GLOB_RECURSE SOURCE_FILES "src/**.cpp" "src/**.h" "lib/*.cpp" )
file(GLOB_RECURSE TEST_SOURCE_FILES "tests/**.cpp")

list(REMOVE_ITEM SOURCE_FILES ${MAIN_FILES})
list(REMOVE_ITEM TEST_SOURCE_FILES ${MAIN_FILES})

add_executable(task1 ${SOURCE_FILES} src/main.cpp)

#TESTS
find_package(Boost 1.59.0 COMPONENTS unit_test_framework)
if(Boost_FOUND)
    include_directories( ${Boost_INCLUDE_DIR} )
    add_executable(tests ${SOURCE_FILES} ${TEST_SOURCE_FILES} tests/tests.cpp)
    target_link_libraries(tests ${Boost_LIBRARIES})
endif()