cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(IPFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(IPFilter VERSION 0.0.1)
endif()

add_executable(ip_filter Main.cpp)
add_library(IPList IPList.cpp)
add_library(IPPool IPPool.cpp)

# Enable testing and adding gtest to project
enable_testing()
add_subdirectory(../googletest googletest)
include_directories(${CMAKE_SOURCE_DIR}/../googletest/include)

target_link_libraries(IPPool IPList gtest gtest_main)
target_link_libraries(ip_filter PUBLIC IPPool gtest gtest_main)

set_target_properties(ip_filter IPList IPPool PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    # Those are needed so gtest won't conflict with proj files runtime library mode, when compiling
    # with MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    target_compile_options(ip_filter PRIVATE
        /WX
    )
    target_compile_options(IPList PRIVATE
        /WX
    )
    target_compile_options(IPPool PRIVATE
        /WX
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IPList PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IPPool PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)