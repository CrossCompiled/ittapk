cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

project(lecture06_timer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules/")

set(BOOST_ROOT "/usr/local/boost-1.61.0")
find_package(Boost REQUIRED)

set(LECTURE lecture06_timer)
add_library(${LECTURE} STATIC
        src/exercise01/Timer.cpp
        src/exercise01/Events.cpp
        src/exercise02/Timer.cpp
        src/exercise02/Events.cpp
        src/exercise02/Functor.cpp src/exercise02/Functor.h)

target_include_directories(${LECTURE} PUBLIC includes)
target_include_directories(${LECTURE} PUBLIC ${Boost_INCLUDE_DIRS})
set_target_properties(${LECTURE} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

add_executable(exercise01 src/exercise01/Bindfunction.cpp)
target_link_libraries(exercise01 ${LECTURE})
set_target_properties(exercise01 PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

add_executable(exercise02 src/exercise02/Bindfunction.cpp)
target_link_libraries(exercise02 ${LECTURE})
set_target_properties(exercise02 PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

#########
# TESTS
#########
enable_testing()
find_package(GTest REQUIRED)

set(LTESTS
        test/exercise01/test_exercise01_SharedPtr.cpp
        )

foreach(testfile ${LTESTS})
    get_filename_component(name ${testfile} NAME_WE)
    add_executable(${name} "${testfile}")
    target_link_libraries(${name} ${LECTURE})
    target_link_libraries(${name} ${GMOCK_MAIN_LIBRARY})
    set_target_properties(${name} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
	)
    if(MSVC)
        set_target_properties(${name} PROPERTIES
            COMPILE_FLAGS "-MTd"
        )
    else()
        set_target_properties(${name} PROPERTIES
           COMPILE_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage"
           LINK_FLAGS "-fprofile-arcs -ftest-coverage"
        )
    endif()
    add_test(${name} ${name})
endforeach()

