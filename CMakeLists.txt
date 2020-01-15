cmake_minimum_required(VERSION 3.1)
project(YamlExample)

add_subdirectory(third-party/yaml-cpp)

add_executable(
    yaml-example
    main.cpp
)

target_link_libraries(
    yaml-example
    PRIVATE
    yaml-cpp
)
