cmake_minimum_required(VERSION 3.14)
project(CommitSuicide VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(
        DEBUG
)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)

add_executable(CommitSuicide src/main.cpp)

target_include_directories(
        CommitSuicide
        PUBLIC
        /src
        /vendor/spdlog/include
        /vendor/GLFW/include
        /vendor/GLAD/include
        /vendor/imgui/imgui
        )

# TODO: make this cross paltfrom.
file(COPY res DESTINATION ${CMAKE_BINARY_DIR}) # for windows ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
