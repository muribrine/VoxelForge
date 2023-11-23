#include "../vulkanRequires.hpp"

VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
VkPipelineShaderStageCreateInfo createShaderStageCreateInfo(VkShaderModule module, std::string type);