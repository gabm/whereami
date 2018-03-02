cmake_minimum_required(VERSION 3.0)
project(whereami VERSION 1.0.0)

find_package(ld-cmake-tools REQUIRED)
include(${LD_CMAKE_TOOLS_USE_FILE})

add_library(${PROJECT_NAME} SHARED src/whereami.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE WAI_FUNCSPEC=__declspec(dllexport)
        PUBLIC WAI_FUNCSPEC=__declspec(dllimport)
        )
endif(MSVC)

cmake_make_installation(
        TARGETS ${PROJECT_NAME}
        NAMESPACE link_dev
        CMAKE_IN cmake/Config.cmake.in
        HEADER_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include/
        HEADER_PATTERNS "*.h")
