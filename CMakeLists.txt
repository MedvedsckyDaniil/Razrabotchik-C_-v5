cmake_minimum_required(VERSION 3.10)
project(logging_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(logging_lib
    src/logger.cpp
    src/file_logger.cpp
    src/socket_logger.cpp
    src/logger_factory.cpp
)

target_include_directories(logging_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Консольное приложение
add_executable(logger_app app/main.cpp)
target_link_libraries(logger_app PRIVATE logging_lib)
