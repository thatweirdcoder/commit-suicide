cmake_minimum_required(VERSION 3.14)
project(CommitSuicide VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)


add_executable(CommitSuicide
        src/main.cpp)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/GLAD)
add_subdirectory(vendor/glm)


target_include_directories(
        CommitSuicide
        PUBLIC
        vendor/GLFW/include
        vendor/GLAD/include
)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_subdirectory(vendor/spdlog)
    target_include_directories(
            CommitSuicide
            PUBLIC
            vendor/spdlog/include
    )
    add_compile_definitions(
            DEBUG
    )
endif ()

# TODO: make this cross paltfrom.
file(COPY res DESTINATION ${CMAKE_BINARY_DIR}) # for windows ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
