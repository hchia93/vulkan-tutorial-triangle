#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <vector>
#include <iostream>
#include <optional>



// Ensure this is static function or function outside of class
static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}
//
// Ensure this is static function or function outside of class
static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

// 3.4 Queue Family Related
struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicFamily;
    std::optional<uint32_t> presentFamily;
    
    bool IsComplete()
    {
        return graphicFamily.has_value() && presentFamily.has_value();
    }
};


class HelloTriangleApplication
{
public:
    void Run();

private:
    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void Cleanup();

    void CreateInstance();
    void CheckSupportedInstanceExtensions(const char** requiredInstanceExtensionNames, uint32_t requiredExtensionCount);

    std::vector<const char*> GetRequiredExtensions();

    GLFWwindow* m_Window;
    VkInstance m_Instance;
  
    // 3.1.3 Validation Layer
    bool CheckValidationLayerSupport();
    void SetupDebugMessenger();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    /*
     *  VkBool32 indicates if the Vulkan call should be aborted. If the callback returns true, the call is aborted with VK_ERROR_VALIDATION_FAILED_TEXT
     */
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    // 3.1.4 Physical Device Related
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    int RateDeviceSuitability(VkPhysicalDevice device);
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

    // 3.1.4 Queue Family Related
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    // 3.1.5 Logical Device & Queue
    void CreateLogicalDevice();
    VkDevice m_Device;

    // Implicitly clean up when device is destroyed.
    VkQueue m_GraphicsQueue;

    // 3.2 
    void CreateSurface();
    VkSurfaceKHR m_Surface;

};