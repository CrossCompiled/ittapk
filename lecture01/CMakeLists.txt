cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(lecture01 VERSION 0.1 LANGUAGES CXX C)

#set(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

SET(COVER_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

SET(COVER_C_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")

SET(COVER_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
#set(CMAKE_CXX_FLAGS " -std=gnu++11")

set(LECTURE lecture01)
add_library(${LECTURE} INTERFACE)
target_include_directories(${LECTURE} INTERFACE includes)

#########
# TESTS
#########
enable_testing()
find_package(GTest REQUIRED)

set(LTESTS
        test/exercise01/test_exercise01_SharedPtr.cpp
        test/exercise02/test_exercise02_SharedPtrUnsafe.cpp
        test/exercise02/test_exercise02_Comparison.cpp
        )

foreach(testfile ${LTESTS})
    get_filename_component(name ${testfile} NAME_WE)
    add_executable(${name} "${testfile}")
    target_link_libraries(${name} ${LECTURE})
    target_link_libraries(${name} ${GMOCK_MAIN_LIBRARIES})
    set_target_properties(${name} PROPERTIES
            COMPILE_FLAGS ${COVER_CXX_FLAGS}
            LINK_FLAGS ${COVER_EXE_LINKER_FLAGS}
            )
    add_test(${name} ${name})
endforeach()

