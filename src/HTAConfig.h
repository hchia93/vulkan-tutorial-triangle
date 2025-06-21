#pragma once
#include <vector>

const uint32_t HTA_WIDTH = 800;
const uint32_t HTA_HEIGHT = 600;

const std::vector<const char*> validationLayers = 
{
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
   const bool bEnableValidationLayers = false;
#else
   const bool bEnableValidationLayers = true;
#endif 