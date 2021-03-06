cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

IF(DEFINED CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
   SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

set(LECTURE lecture03)

project(${LECTURE} VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")


# Lecture Library
add_library(${LECTURE}
        src/exercise02/LogFile.cpp
        src/exercise02/LogFileTransformed.cpp)
target_include_directories(${LECTURE} PUBLIC includes)

# Executeables
add_executable(ProgramTransformation src/exercise02/ProgramTransformation.cpp)
target_link_libraries(ProgramTransformation ${LECTURE})


#########
# TESTS
#########
enable_testing()
find_package(GTest REQUIRED)

set(LTESTS
        test/exercise01/test_exercise01_MyVector.cpp
        test/exercise02/test_exercise02_Strong.cpp
        )

foreach(testfile ${LTESTS})
    get_filename_component(name ${testfile} NAME_WE)
    add_executable(${name} "${testfile}" includes/lecture03/exercise02/LogFileTransformed.h)
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

