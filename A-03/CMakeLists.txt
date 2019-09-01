cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(Allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(Allocator VERSION 0.0.1)
endif()

# Enable testing and adding gtest to project
enable_testing()
add_subdirectory(../googletest googletest)
include_directories(${CMAKE_SOURCE_DIR}/../googletest/include)

add_executable(allocator Main.cpp)
add_executable(CustomAllocatorTests CustomAllocatorTests.cpp)
add_test(CustomAllocatorTests CustomAllocatorTests)

target_link_libraries(CustomAllocatorTests PUBLIC gtest gtest_main)
target_link_libraries(allocator PUBLIC gtest gtest_main)

set_target_properties(allocator CustomAllocatorTests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    # Those are needed so gtest won't conflict with proj files runtime library mode, when compiling
    # with MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    target_compile_options(allocator PRIVATE
        /WX
    )
    target_compile_options(CustomAllocatorTests PRIVATE
        /WX
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(CustomAllocatorTests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)