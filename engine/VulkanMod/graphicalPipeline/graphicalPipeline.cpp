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

/*VkPipelineVertexInputStateCreateInfo* makeVertexInputCreateInfo() {

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

    return &vertexInputInfo;

};


VkPipelineInputAssemblyStateCreateInfo* makeInputAssemblyCreateInfo() {

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    return &inputAssembly;

};


VkPipelineViewportStateCreateInfo* makeViewportStateCreateInfo() {

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    return &viewportState;

};


VkPipelineRasterizationStateCreateInfo* makeRasterizerCreateInfo() {

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    return &rasterizer;

};


VkPipelineMultisampleStateCreateInfo* makeMultisamplingCreateInfo() {

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    return &multisampling;

};


VkPipelineDynamicStateCreateInfo* makeDynamicStateCreateInfo() {

    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    return &dynamicState;

};*/