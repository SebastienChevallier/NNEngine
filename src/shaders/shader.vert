#version 450

layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 view;
    mat4 proj;
} globalUBO;

//layout(set = 0, binding = 1) uniform ObjectUBO {
//    mat4 model;
//} objectUBO; // Ce buffer est dynamique

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
} pushConstants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {    
    vec4 transformed = globalUBO.proj * globalUBO.view * pushConstants.model * vec4(inPosition, 1.0);
    gl_Position = transformed;

    fragColor = inColor;
    fragTexCoord = inTexCoord;
}
