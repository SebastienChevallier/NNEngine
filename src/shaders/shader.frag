#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
} pushConstants;

void main() {
    vec2 uv = fragTexCoord * pushConstants.tiling + pushConstants.offset;
    vec4 texColor = texture(texSampler, uv);
    outColor = texColor * vec4(fragColor, 1.0);
}
