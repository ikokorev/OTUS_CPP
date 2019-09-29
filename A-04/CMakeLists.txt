cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(print_ip VERSION 0.0.1)
endif()

# Enable testing and adding gtest to project
enable_testing()
add_subdirectory(../googletest googletest)
include_directories(${CMAKE_SOURCE_DIR}/../googletest/include)

add_executable(print_ip Main.cpp)
#add_executable(CustomAllocatorTests CustomAllocatorTests.cpp)
#add_test(CustomAllocatorTests CustomAllocatorTests)

#target_link_libraries(CustomAllocatorTests PUBLIC gtest gtest_main)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    # Those are needed so gtest won't conflict with proj files runtime library mode, when compiling
    # with MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)

# Doxygen setup
find_package(Doxygen)
set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile.in)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target( GenerateDoxygenDocumentation
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating doxygen documentation."
)