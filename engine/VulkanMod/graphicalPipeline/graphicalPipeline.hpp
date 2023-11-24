#include "../vulkanRequires.hpp"

VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
VkPipelineShaderStageCreateInfo createShaderStageCreateInfo(VkShaderModule module, std::string type);
VkPipelineVertexInputStateCreateInfo* makeVertexInputCreateInfo();
VkPipelineInputAssemblyStateCreateInfo* makeInputAssemblyCreateInfo();
VkPipelineViewportStateCreateInfo* makeViewportStateCreateInfo();
VkPipelineRasterizationStateCreateInfo* makeRasterizerCreateInfo();
VkPipelineMultisampleStateCreateInfo* makeMultisamplingCreateInfo();
VkPipelineDynamicStateCreateInfo* makeDynamicStateCreateInfo();