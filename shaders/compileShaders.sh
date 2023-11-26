SDK_VERSION="1.3.268.0"

shader_directories=($(find . -type d -exec test -e '{}/shader.vert' \; -print))

echo ""
for shader_folder in "${shader_directories[@]}"; do

    echo "Compiling shaders in $shader_folder..."

    shader_vert="$shader_folder/shader.vert"
    shader_frag="$shader_folder/shader.frag"

    ~/VulkanSDK/$SDK_VERSION/x86_64/bin/glslc "$shader_vert" -o "$shader_folder/vert.spv"
    ~/VulkanSDK/$SDK_VERSION/x86_64/bin/glslc "$shader_frag" -o "$shader_folder/frag.spv"

    echo "Compiled shaders in $shader_folder."
    echo ""

done

echo "Shader compilation complete."