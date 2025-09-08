#version 450
layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 view;
    mat4 proj;
    mat4 lightSpace;
} globalUBO;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
    int debug;
} pushConstants;

layout(location = 0) in vec3 inPosition;

void main() {
    gl_Position = globalUBO.lightSpace * pushConstants.model * vec4(inPosition, 1.0);
}
