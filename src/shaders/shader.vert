#version 450

layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 view;
    mat4 proj;
    mat4 lightSpace;
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
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec4 fragPosLight;

void main() { 
    mat4 M = pushConstants.model;

    vec4 transformed = globalUBO.proj * globalUBO.view * M * vec4(inPosition, 1.0);
    gl_Position = transformed;

    mat3 N = transpose(inverse(mat3(M)));
    fragNormal = normalize(N * inNormal);

    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragPosLight = globalUBO.lightSpace * M * vec4(inPosition,1.0);
}
