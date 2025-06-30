# Vulkan Triangle, a tutorial walkthrough / learning project

This repository serves as my **Vulkan** learning project. The primary goal is to complete the tutorial [vulkan-tutorial.com](https://vulkan-tutorial.com/Drawing_a_triangle), understand the concepts, and able to render a legendary triangle at the end of the tutorial.

The original project setup required to setup `glm`, `glfw` and `VulkanSDK` dependencies. 
This will be managed by the `vcpkg.json` along with [DependencyInstaller](https://github.com/hchia93/hchia93/blob/main/DependencyInstaller.bat-EN-README.md) and [SolutionGenerator](https://github.com/hchia93/hchia93/blob/main/VisualStudioSolutionGenerator.bat-EN-README.md).


> **⚠️ Work-In-Progress** :
> This project is currently incomplete as I am still working through the tutorial. The application may crash or not render a triangle yet. This is expected behavior until all the tutorial steps are implemented.


> **⚠️ Windows-Only Project**
> This project is configured for a **Windows-only** environment.

## Project Structure

```
vulkan-tutorial-triangle/
├── CMakeLists.txt         # CMake build configuration
├── vcpkg.json             # Dependency manifest
├── generate.bat           # Install dependencies and generate solution
├── README.md              # This file
├── src/                   # Source code
│   ├── main.cpp
│   ├── HelloTriangleApplication.cpp
│   ├── HelloTriangleApplication.h
│   └── HTAConfig.h
└── shaders/               # Shader files (if any)
    ├── triangle.vert
    └── triangle.frag
```

## Prerequisites

To build and run this project, external dependencies are required. The `DependencyInstaller.bat` script will install them accordingly.

| Dependency             | Version/Details                                     |
| ---------------------- | --------------------------------------------------- |
| **GLFW3**              | Version 3.4 or higher                               |
| **GLM**                | Version 1.0.1#3 (OpenGL Mathematics)                |
| **Vulkan**             | Latest version available in vcpkg                   |


## Running the Project

### Step 1: Generate Solution

Execute the generator script. This will install dependencies and generate the Visual Studio solution:

```cmd
/generate.bat
```

The solution will be generated in 
```cmd
/generated-vs/
```

### Step 2: Build and Run

Open the generated solution located at:
```cmd
/generated-vs/vulkan-tutorial-triangle.sln
```

> **⚠️ Note:** Ensure the start-up project is `vulkan-tutorial-triangle`


## Learning Resources

- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [Vulkan Specification](https://www.khronos.org/registry/vulkan/)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLM Documentation](https://github.com/g-truc/glm)
