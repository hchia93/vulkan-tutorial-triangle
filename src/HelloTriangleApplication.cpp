#include "HelloTriangleApplication.h"
#include "HTAConfig.h"
#include <stdexcept>
#include <cstring>
#include <map>


void HelloTriangleApplication::Run()
{
    InitWindow();
    InitVulkan();
    MainLoop();
    Cleanup();
}

void HelloTriangleApplication::InitWindow()
{
    glfwInit();

    // GLFW was originally designed to create OpenGL context, the following reroutes it.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Disable now because resize windows needs to be handled. Later.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Last parameter is OpenGL only. 
    m_Window = glfwCreateWindow(HTA_WIDTH, HTA_HEIGHT, "Vulkan", nullptr, nullptr);

}

void HelloTriangleApplication::InitVulkan()
{
    CreateInstance();
    SetupDebugMessenger();
    CreateSurface();

    PickPhysicalDevice();
    CreateLogicalDevice();

}

// stop at "we can now re-use this in the create instance function...
void HelloTriangleApplication::CreateInstance()
{
    if (bEnableValidationLayers && !CheckValidationLayerSupport())
    {
        throw std::runtime_error("validation layer requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";

    // VK_MAKE_VERSION is deprecated, use VK_MAKE_API_VERSION instead.
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0,1,0,0); 
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0,1,0,0); 
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Returning extensions: A built-in function from GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    CheckSupportedInstanceExtensions(glfwExtensions, glfwExtensionCount);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

    if (bEnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance");
    }
}

std::vector<const char*> HelloTriangleApplication::GetRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    
    if (bEnableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void HelloTriangleApplication::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = DebugCallback;
}

void HelloTriangleApplication::SetupDebugMessenger()
{
    if (!bEnableValidationLayers)
    {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    PopulateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void HelloTriangleApplication::CheckSupportedInstanceExtensions(const char** requiredInstanceExtensionNames, uint32_t requiredExtensionCount)
{
    uint32_t extensionCount = 0;
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "Required Extension:\n";
    const char** pName = requiredInstanceExtensionNames;
    for (int i = 0; i < requiredExtensionCount; i++)
    {
        if (pName != nullptr)
        {
            std::cout << *pName << std::endl;
            pName++;
        }
    }
   
    std::cout << std::endl << "Available Extension:" << std::endl;
    if (extensions.size() == 0) std::cout<<"none"<<std::endl;
    for (const auto& extension : extensions)
    {
        for (int i = 0; i < requiredExtensionCount; i++)
        {
            if (pName != nullptr)
            {
                if (extension.extensionName == *pName)
                {
                    std::cout << '\n' << extension.extensionName <<"Required"<<std::endl;
                }
                pName++;
            }
        }

        std::cout << '\n' << extension.extensionName << std::endl;
    }

}

void HelloTriangleApplication::MainLoop()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

    }
}

void HelloTriangleApplication::Cleanup()
{
    vkDestroyDevice(m_Device, nullptr);

    if (bEnableValidationLayers)
    {
        // Comment out if wish to test validation error.
        DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
    }

    // GLFW doesn't offer a special function for destroying a surface
    // But can be done thru original API
    vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr); 

    vkDestroyInstance(m_Instance, nullptr);

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool HelloTriangleApplication::CheckValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers)
    {
        bool layerFound = false;
    
        std::cout << "Available Layers:\n";
        for (const auto& layerProperties : availableLayers)
        {
            std::cout << layerProperties.layerName;
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                std::cout << "[found]" << std::endl;
                break;
            }
            std::cout << std::endl;
        }

        if (!layerFound)
        {
            return false;
        }
    }

    std::cout << std::endl;

    return true;
}

void HelloTriangleApplication::PickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan Support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;
    for (const auto& device : devices)
    {
        int score = RateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    for (std::map<int, VkPhysicalDevice>::reverse_iterator it = candidates.rbegin(); it != candidates.rend(); ++it)
    {
        // Check if the best candidate is suitable at all.
        if (it->first > 0 && IsDeviceSuitable(it->second))
        {
            m_PhysicalDevice = it->second;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

bool HelloTriangleApplication::IsDeviceSuitable(VkPhysicalDevice device)
{
    QueueFamilyIndices indices = FindQueueFamilies(device);
    return indices.graphicFamily.has_value();
}

int HelloTriangleApplication::RateDeviceSuitability(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    int score = 0;
    
    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
    {
        return 0;
    }

    return score;
}

QueueFamilyIndices HelloTriangleApplication::FindQueueFamilies(VkPhysicalDevice device) 
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    QueueFamilyIndices indices;
    // Logic to find queue family indices to populate struct with
    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicFamily = i;
        }
    }
    return indices;
}

void HelloTriangleApplication::CreateLogicalDevice()
{
    QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);
    
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo; 
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;
    if (bEnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_Device, indices.graphicFamily.value(), 0, &m_GraphicsQueue);
}

void HelloTriangleApplication::CreateSurface()
{
    //VkWin32SurfaceCreateInfoKHR createInfo{};
    //createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    //createInfo.hwnd = glfwGetWin32Window(m_Window); // Get Raw HWMD from GLFW window object
    //createInfo.hinstance = GetModuleHandle(nullptr); // Returns HINSTANCE handle of current process
    //
    //if (vkCreateWin32SurfaceKHR(m_Instance, &createInfo, nullptr, &m_Surface) != VK_SUCCESS)
    //{
    //    throw std::runtime_error("failed to create window surface");
    //}

    // Alternate to the commented section above, as GLFW calls take simple parameters.
    if (glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }
}