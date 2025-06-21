cmake_minimum_required(VERSION 3.20)
project(vulkan-tutorial-triangle VERSION 1.0.0 LANGUAGES CXX)

# Prevent ALL_BUILD from being the default startup project
set(CMAKE_VS_INCLUDE_ALL_BUILD 0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages using vcpkg
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Create executable
add_executable(vulkan-tutorial-triangle
    src/main.cpp
    src/HelloTriangleApplication.cpp
    src/HelloTriangleApplication.h
    src/HTAConfig.h
)

# Set include directories
target_include_directories(vulkan-tutorial-triangle PRIVATE
    src
)

# Link libraries
target_link_libraries(vulkan-tutorial-triangle
    glfw
    glm::glm
    Vulkan::Vulkan
)

# Set the default startup project in Visual Studio
set(CMAKE_VS_STARTUP_PROJECT vulkan-tutorial-triangle)

# Platform-specific settings
if(WIN32)
    target_link_libraries(vulkan-tutorial-triangle ws2_32)
endif()

# Copy Vulkan validation layers and shaders if they exist
if(EXISTS "${CMAKE_SOURCE_DIR}/shaders")
    add_custom_command(TARGET vulkan-tutorial-triangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:vulkan-tutorial-triangle>/shaders"
    )
endif() 