cmake_minimum_required(VERSION 3.12)
project(OGLE_LIBRARY)


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

add_compile_definitions(GLFW_DLL)

add_library(${PROJECT_NAME} src/OGLEApp.cpp src/OGLEWindow.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad::glad)