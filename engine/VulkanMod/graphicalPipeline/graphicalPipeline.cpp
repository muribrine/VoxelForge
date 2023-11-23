#include "graphicalPipeline.hpp"

VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device) {

    VkShaderModuleCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create shader module!");

    };

    return shaderModule;

};

VkPipelineShaderStageCreateInfo createShaderStageCreateInfo(VkShaderModule module, std::string type) {

    VkPipelineShaderStageCreateInfo shaderStageInfo{};

    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.module = module;
    shaderStageInfo.pName = "main";

    if ( type == std::string("vert") ) {
        shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    }
    if ( type == std::string("frag") ) {
        shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    }

    return shaderStageInfo;

};