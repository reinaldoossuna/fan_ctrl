cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(third-party/yaml-cpp)
include_directories(include)

add_executable(
    fan-control
    main.cpp
    src/config.cpp
)

target_link_libraries(
    fan-control
    PRIVATE
    yaml-cpp
)
