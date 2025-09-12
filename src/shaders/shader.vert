#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec4 fragPosLight;   // position en espace lumière (bias VP)

layout(set = 0, binding = 0) uniform GlobalUBO {
    mat4 view;
    mat4 proj;
    mat4 lightSpace;   // DOIT être bias * lightVP côté C++
} ubo;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
} pushConstants;

void main() {
    // position monde
    vec4 worldPos = pushConstants.model * vec4(inPos, 1.0);

    // sorties
    fragColor    = inColor;
    fragTexCoord = inUV;
    fragNormal   = mat3(transpose(inverse(pushConstants.model))) * inNormal;

    // coord pour la shadow map
    fragPosLight = ubo.lightSpace * worldPos;

    // projection caméra
    gl_Position  = ubo.proj * ubo.view * worldPos;
}