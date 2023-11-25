#include "vulkanInterface.hpp"

GLFWwindow* VulkanInterface::createWindow(const char* windowTitle, uint32_t windowWidth, uint32_t windowHeight) {

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    return glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

};


void VulkanInterface::createInstance(const char* title) {

    VkApplicationInfo appInfo = makeInstanceAppInfo(title);
    VkInstanceCreateInfo createInfo = makeInstanceCreateInfo(appInfo);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create instance!");
    };

};


void VulkanInterface::createWindowSurface(GLFWwindow* window) {

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
    
}


void VulkanInterface::pickPhysicalDevice() {

    physicalDevice = VK_NULL_HANDLE;
    std::vector<VkPhysicalDevice> devices = getPhysicalDevices(instance);
    std::vector<VkPhysicalDevice> candidates;

    for (const auto& device : devices) {

        if (deviceIsSuitable(device, surface)) { candidates.push_back(device); }

    }

    physicalDevice = selectBestPhysicalDevice(candidates);

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    std::cout << "Selected PhysicalDevice: " << deviceProperties.deviceName << "\n";

};


void VulkanInterface::createLogicalDevice() {

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies) {

        VkDeviceQueueCreateInfo queueCreateInfo{};

        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        queueCreateInfos.push_back(queueCreateInfo);

    };

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
    createInfo.enabledLayerCount = 0;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create logical device!");

    };

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);

};


void VulkanInterface::createSwapChain(GLFWwindow* window) {

    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    swapChainExtent = chooseSwapExtent(swapChainSupport.capabilities, window);

    uint32_t imageCount = selectImageCount(swapChainSupport);


    VkSwapchainCreateInfoKHR createInfo = makeSwapChainCreateInfo(
        surface,
        imageCount,
        swapChainExtent,
        surfaceFormat,
        physicalDevice,
        swapChainSupport,
        presentMode
    );


    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create swap chain!");

    };

    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;

};


void VulkanInterface::createImageViews() {

    swapChainImageViews.resize(swapChainImages.size());

    for (size_t i = 0; i < swapChainImages.size(); i++) {

        VkImageViewCreateInfo createInfo = makeImageViewCreateInfo(i, swapChainImageFormat, swapChainImages);

        if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {

            throw std::runtime_error("Failed to create image view!");
            
        };

    };

};

void VulkanInterface::createRenderPass() {

    VkAttachmentDescription colorAttachment{};

    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};

    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;


    VkRenderPassCreateInfo renderPassInfo{};

    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        
        throw std::runtime_error("Failed to create render pass!");

    };

};


void VulkanInterface::createGraphicsPipeline() {

    auto vertShaderCode = readFile("./shaders/vert.spv");
    auto fragShaderCode = readFile("./shaders/frag.spv");


    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, device);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = createShaderStageCreateInfo(vertShaderModule, std::string("vert"));
    VkPipelineShaderStageCreateInfo fragShaderStageInfo = createShaderStageCreateInfo(fragShaderModule, std::string("frag"));
    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create pipeline layout!");

    };

    VkPipelineVertexInputStateCreateInfo *vertexInputInfo = makeVertexInputCreateInfo();
    VkPipelineInputAssemblyStateCreateInfo *inputAssembly = makeInputAssemblyCreateInfo();
    VkPipelineViewportStateCreateInfo *viewportState = makeViewportStateCreateInfo();
    VkPipelineRasterizationStateCreateInfo *rasterizer = makeRasterizerCreateInfo();
    VkPipelineMultisampleStateCreateInfo *multisampling = makeMultisamplingCreateInfo();
    VkPipelineDynamicStateCreateInfo *dynamicState = makeDynamicStateCreateInfo();

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f; colorBlending.blendConstants[3] = 0.0f;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;

    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = vertexInputInfo;
    pipelineInfo.pInputAssemblyState = inputAssembly;
    pipelineInfo.pViewportState = viewportState;
    pipelineInfo.pRasterizationState = rasterizer;
    pipelineInfo.pMultisampleState = multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = dynamicState;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.renderPass = renderPass;

    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            
        throw std::runtime_error("Failed to create graphics pipeline!");

    };


    vkDestroyShaderModule(device, fragShaderModule, nullptr);
    vkDestroyShaderModule(device, vertShaderModule, nullptr);

};


void VulkanInterface::createFramebuffers() {

    swapChainFramebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++) {

        VkImageView attachments[] = {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};

        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {

            throw std::runtime_error("Failed to create framebuffer!");

        };
    };

};

void VulkanInterface::createCommandPool() {

    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice, surface);

    VkCommandPoolCreateInfo poolInfo{};

    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {

        throw std::runtime_error("Failed to create command pool!");

    };

};


void VulkanInterface::createCommandBuffer() {

    VkCommandBufferAllocateInfo allocInfo{};

    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {

        throw std::runtime_error("Failed to allocate command buffers!");

    };

};


void VulkanInterface::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {

        throw std::runtime_error("Failed to begin recording command buffer!");

    };

    VkRenderPassBeginInfo renderPassInfo{};

    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    VkViewport viewport{};

    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapChainExtent.width);
    viewport.height = static_cast<float>(swapChainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};

    scissor.offset = {0, 0};
    scissor.extent = swapChainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);


    vkCmdDraw(commandBuffer, 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {

        throw std::runtime_error("Failed to record command buffer!");

    };
    
};


void VulkanInterface::cleanUpVkResources() {

    vkDestroyCommandPool(device, commandPool, nullptr);

    for (auto framebuffer : swapChainFramebuffers) {

        vkDestroyFramebuffer(device, framebuffer, nullptr);

    }

    vkDestroyPipeline(device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyRenderPass(device, renderPass, nullptr);

    for (auto imageView : swapChainImageViews) {

        vkDestroyImageView(device, imageView, nullptr);

    };

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

};