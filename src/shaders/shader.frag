#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec4 fragPosLight;              // ⬅️ AJOUT

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform LightUBO {
    vec3 dir;       float intensity;
    vec3 color;     float ambient;
} light;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
} pushConstants;

// ⬅️ AJOUT : la shadow map (tu la fill déjà côté C++ en binding=3)
layout(set = 0, binding = 3) uniform sampler2D shadowMap;

float shadowFactor(vec3 N, vec3 L, vec4 lightClip) {
    vec3 proj = lightClip.xyz / lightClip.w;
    proj = proj * 0.5 + 0.5;            // [-1,1] -> [0,1]

    // Hors shadowmap = éclairé (ton sampler est CLAMP_TO_BORDER + WHITE, ça colle aussi)
    if (proj.x < 0.0 || proj.x > 1.0 || proj.y < 0.0 || proj.y > 1.0 || proj.z > 1.0)
        return 1.0;

    // petit bias pour l’acné
    float bias = max(0.0005 * (1.0 - dot(N, L)), 0.001);

    float closest = texture(shadowMap, proj.xy).r;      // sampler2D (compare OFF)
    return (proj.z - bias) <= closest ? 1.0 : 0.0;      // 1 = éclairé, 0 = ombre
}

void main() {
    vec2 uv = fragTexCoord * pushConstants.tiling + pushConstants.offset;
    vec3 base = texture(texSampler, uv).rgb * fragColor;

    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-light.dir);
    float NdotL = max(dot(N, L), 0.0);

    float S = shadowFactor(N, L, fragPosLight);         // ⬅️ AJOUT

    vec3 diffuse = base * light.color * (light.intensity * NdotL) * S; // ⬅️ AJOUT
    vec3 ambient = base * light.ambient;
    outColor = vec4(ambient + diffuse, 1.0);
}
