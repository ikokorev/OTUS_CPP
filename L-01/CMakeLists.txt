cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(HelloWorld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(HelloWorld VERSION 0.0.1)
endif()

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)

configure_file(ProjectVersion.h.in ProjectVersion.h)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(HelloWorld Main.cpp)
add_library(ProjectVersionManager ProjectVersionManager.cpp)
add_executable(BTestProjectVersion BTestProjectVersion.cpp)
add_executable(GTestProjectVersion GTestProjectVersion.cpp)

set_target_properties(HelloWorld ProjectVersionManager BTestProjectVersion GTestProjectVersion PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ProjectVersionManager PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(GTestProjectVersion PRIVATE "${CMAKE_BINARY_DIR}")

target_link_libraries(HelloWorld PRIVATE ProjectVersionManager)
target_link_libraries(BTestProjectVersion PRIVATE "${Boost_LIBRARIES}")
target_link_libraries(GTestProjectVersion PRIVATE gtest_main)

set_target_properties(BTestProjectVersion PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES ${CMAKE_BINARY_DIR}
)

if (MSVC)
    target_compile_options(HelloWorld PRIVATE
        /W4
    )
    target_compile_options(ProjectVersionManager PRIVATE
        /W4
    )
    target_compile_options(BTestProjectVersion PRIVATE
        /W4
    )
    target_compile_options(GTestProjectVersion PRIVATE
        /W4
    )
else ()
    target_compile_options(HelloWorld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ProjectVersionManager PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(BTestProjectVersion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(GTestProjectVersion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS HelloWorld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)

enable_testing()

add_test(BTestProjectVersion BTestProjectVersion)
add_test(GTestProjectVersion GTestProjectVersion)
