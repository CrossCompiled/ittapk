cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

project(lecture06_variant VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules/")

set(LECTURE lecture06_variant)
add_library(${LECTURE} INTERFACE)
target_include_directories(${LECTURE} INTERFACE includes)


#########
# TESTS
#########
enable_testing()
find_package(GTest REQUIRED)


set(LTESTS
        test/exercise01/test_exercise01_VariantStream.cpp
        test/exercise02/test_exercise02_Visitors.cpp
        )

foreach(testfile ${LTESTS})
    get_filename_component(name ${testfile} NAME_WE)
    add_executable(${name} "${testfile}" includes/lecture06_variant/exercise01/Variance.h includes/lecture06_variant/exercise02/Visitor.h)
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

