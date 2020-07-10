cmake_minimum_required(VERSION 3.0)
project(whereami VERSION 1.0.0)

find_package(ld-cmake-tools REQUIRED)

add_library(${PROJECT_NAME} STATIC src/whereami.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PRIVATE WAI_FUNCSPEC=)

cmake_make_installation(
        TARGETS ${PROJECT_NAME}
        NAMESPACE wai
        CMAKE_IN cmake/Config.cmake.in
        HEADER_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src/
        HEADER_PATTERNS "*.h")
