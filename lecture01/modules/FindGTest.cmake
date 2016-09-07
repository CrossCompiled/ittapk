option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

include(ExternalProject)

ExternalProject_Add(
        googletest
        URL https://github.com/google/googletest/archive/release-1.8.0.zip
        CMAKE_ARGS "-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} -Dgtest_disable_pthreads=on"
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
)

ExternalProject_Get_Property(googletest source_dir)
ExternalProject_Get_Property(googletest binary_dir)

set(GTEST_INCLUDE_DIR  ${source_dir}/googletest/include)
set(GTEST_LIBRARY      ${binary_dir}/googlemock/gtest/${CMAKE_SHARED_LIBRARY_PREFIX}gtest${CMAKE_SHARED_LIBRARY_SUFFIX})
#set(GTEST_LIBRARY      ${binary_dir}/libgtest.a)
set(GTEST_MAIN_LIBRARY ${binary_dir}/googlemock/gtest/${CMAKE_SHARED_LIBRARY_PREFIX}gtest_main${CMAKE_SHARED_LIBRARY_SUFFIX})
#set(GTEST_MAIN_LIBRARY ${binary_dir}/libgtest_main.a)


set(GMOCK_INCLUDE_DIR  ${source_dir}/googlemock/include)
set(GMOCK_LIBRARY      ${binary_dir}/googlemock/${CMAKE_SHARED_LIBRARY_PREFIX}gmock${CMAKE_SHARED_LIBRARY_SUFFIX})
set(GMOCK_MAIN_LIBRARY ${binary_dir}/googlemock/${CMAKE_SHARED_LIBRARY_PREFIX}gmock_main${CMAKE_SHARED_LIBRARY_SUFFIX})


set(GTEST_FOUND          TRUE)

set(GTEST_LIBRARIES      GTest::GTest)
set(GTEST_MAIN_LIBRARIES GTest::Main)
set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
set(GTEST_INCLUDE_DIRS   ${GTEST_INCLUDE_DIR})

set(GMOCK_LIBRARIES      GMock::GMock)
set(GMOCK_MAIN_LIBRARIES GMock::Main)
set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})
set(GMOCK_INCLUDE_DIRS   ${GMOCK_INCLUDE_DIR})


if(GTEST_FOUND)
    file(MAKE_DIRECTORY ${GTEST_INCLUDE_DIR})
    file(MAKE_DIRECTORY ${GMOCK_INCLUDE_DIR})

    include(CMakeFindDependencyMacro)
    find_dependency(Threads)

    if(NOT TARGET ${GTEST_LIBRARIES})
        add_library(${GTEST_LIBRARIES} UNKNOWN IMPORTED)
        set_target_properties(${GTEST_LIBRARIES} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES     "${GTEST_INCLUDE_DIRS}"
                INTERFACE_LINK_LIBRARIES          "Threads::Threads"
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION                 "${GTEST_LIBRARY}"
                )
        add_dependencies(${GTEST_LIBRARIES} googletest)

    endif()
    if(NOT TARGET ${GTEST_MAIN_LIBRARIES})
        add_library(${GTEST_MAIN_LIBRARIES} UNKNOWN IMPORTED)
        set_target_properties(${GTEST_MAIN_LIBRARIES} PROPERTIES
                INTERFACE_LINK_LIBRARIES          "${GTEST_LIBRARIES}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION                 "${GTEST_MAIN_LIBRARY}"
                )
        add_dependencies(${GTEST_MAIN_LIBRARIES} googletest)
    endif()
    if(NOT TARGET ${GMOCK_LIBRARIES})
        add_library(${GMOCK_LIBRARIES} UNKNOWN IMPORTED)
        set_target_properties(${GMOCK_LIBRARIES} PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES     "${GMOCK_INCLUDE_DIRS}"
                INTERFACE_LINK_LIBRARIES          "${GTEST_LIBRARIES}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION                 "${GMOCK_LIBRARY}"
                )
        add_dependencies(${GMOCK_LIBRARIES} googletest)

    endif()
    if(NOT TARGET ${GMOCK_MAIN_LIBRARIES})
        add_library(${GMOCK_MAIN_LIBRARIES} UNKNOWN IMPORTED)
        set_target_properties(${GMOCK_MAIN_LIBRARIES} PROPERTIES
                INTERFACE_LINK_LIBRARIES          "${GMOCK_LIBRARIES}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION                 "${GMOCK_MAIN_LIBRARY}"
                )
        add_dependencies(${GTEST_MAIN_LIBRARIES} googletest)
    endif()


endif()