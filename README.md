# Vulkan Triangle, a tutorial walkthrough / learning project

This repository serves as my **Vulkan** learning project. The primary goal is to complete the tutorial [vulkan-tutorial.com](https://vulkan-tutorial.com/Drawing_a_triangle), understand the concepts, and able to render a legendary triangle at the end of the tutorial.

The original project setup required to setup `glm`, `glfw` and `VulkanSDK` dependencies. 
This will be managed by the `vcpkg.json` along with [DependencyInstaller](https://github.com/hchia93/hchia93/blob/main/DependencyInstaller.bat-EN-README.md) and [SolutionGenerator]().


> **⚠️ Work-In-Progress** :
> This project is currently incomplete as I am still working through the tutorial. The application may crash or not render a triangle yet. This is expected behavior until all the tutorial steps are implemented.


> **⚠️ Windows-Only Project**
> This project is configured for a **Windows-only** environment. The setup scripts and Visual Studio solution generation are not designed for Linux or macOS, as I cannot verified the project generation on those platform at this time. 

## Features

- Basic Vulkan setup and initialization
- Window creation using GLFW
- Triangle rendering with vertex and fragment shaders
- Validation layer support for debugging
- Cross-platform build system using CMake


## Prerequisites

To build and run this project, external dependencies are required. The `DependencyInstaller.bat` script will install them accordingly.

| Dependency             | Version/Details                                     |
| ---------------------- | --------------------------------------------------- |
| **GLFW3**              | Version 3.4 or higher                               |
| **GLM**                | Version 1.0.1#3 (OpenGL Mathematics)               |
| **Vulkan**             | Latest version available in vcpkg                   |

## Project Structure

```
vulkan-tutorial-triangle/
├── CMakeLists.txt         # CMake build configuration
├── vcpkg.json             # Dependency manifest
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

## Configuration
The application can be configured by modifying `src/HTAConfig.h`:

- `HTA_WIDTH` / `HTA_HEIGHT`: Window dimensions
- `bEnableValidationLayers`: Enable/disable Vulkan validation layers

## Instructions

### Step 1: Installs Required Dependencies

Execute the following file to install relevant dependencies:

```cmd
DependencyInstaller.bat
```

### Step 2: Generates the Visual Studio Solution

Next, generate the Visual Studio Solution via the script. This creates the `generated-vs` directory.

```cmd
VisualStudioSolutionGenerator.bat
```

### Step 3: Build and Run

Open the generated solution located at:
- **`generated-vs/vulkan-tutorial-triangle.sln`**

Press **F5** to build and run the application.

> **⚠️ Important First-Time Setup**
> The first time you open the solution, you may need to manually set the startup project.
> 1. In the **Solution Explorer**, **right-click** on `vulkan-tutorial-triangle`.
> 2. Select **"Set as StartUp Project"** from the menu.
>
> You only need to do this once.

The generated solution is for development and debugging purposes only. All configuration is handled by `CMakeLists.txt`.



## Running the Application

After building, run the executable:

```bash
# Windows
./build/Release/vulkan-tutorial-triangle.exe

# Linux/macOS
./build/vulkan-tutorial-triangle
```

You should see a window with a colored triangle rendered using Vulkan.

## Troubleshooting

### Common Issues

1. **Vulkan not found:**
   - Ensure Vulkan SDK is installed and in PATH
   - On Windows, install from: https://vulkan.lunarg.com/sdk/home

2. **GLFW/GLM not found:**
   - Ensure vcpkg is properly set up
   - Check that `CMAKE_TOOLCHAIN_FILE` points to the correct vcpkg installation

3. **Validation layers not working:**
   - Ensure Vulkan SDK validation layers are installed
   - Check that `VK_LAYER_PATH` environment variable is set correctly

### Debug Mode

To build in debug mode with validation layers:

```bash
cmake --build build --config Debug
```

## Learning Resources

- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [Vulkan Specification](https://www.khronos.org/registry/vulkan/)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLM Documentation](https://github.com/g-truc/glm)
