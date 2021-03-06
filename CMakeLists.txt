cmake_minimum_required(VERSION 3.12)
include(automate-vcpkg.cmake)

vcpkg_bootstrap()
vcpkg_install_packages(glfw3 glad)
project(OGLE)


if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
elseif( COMPILER_SUPPORTS_CXX0X)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
else()
    # MSVC, On by default (if available)
endif()

include_directories(OGLE/src)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_compile_definitions(GLFW_DLL)

add_subdirectory(OGLE)
add_subdirectory(OGLE_EDITOR)

add_dependencies(OGLE_EDITOR OGLE_LIBRARY)