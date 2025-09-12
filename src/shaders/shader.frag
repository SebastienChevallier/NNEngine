#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec4 fragPosLight;   // reçu du vertex

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

layout(set = 0, binding = 3) uniform sampler2D shadowMap;

// Résolution de la shadow map (à passer via specialization constant ou uniform)
const float shadowMapResolution = 2048.0;

float ShadowCalculation(vec4 fragPosLight, vec3 N, vec3 L)
{
    vec3 shadowCoord = fragPosLight.xyz / fragPosLight.w;

    // dehors [0,1] → éclairé
    if (shadowCoord.x < 0.0 || shadowCoord.x > 1.0 ||
        shadowCoord.y < 0.0 || shadowCoord.y > 1.0 ||
        shadowCoord.z < 0.0 || shadowCoord.z > 1.0)
        return 1.0;

    // petit bias pour l’acné (dépend de l’angle)
    float bias = max(0.0005 * (1.0 - dot(N, L)), 0.001);

    // PCF 3x3
    float shadow = 0.0;
    float texelSize = 1.0 / shadowMapResolution;

    for (int x=-1; x<=1; ++x) {
        for (int y=-1; y<=1; ++y) {
            vec2 offset = vec2(x, y) * texelSize;
            float pcfDepth = texture(shadowMap, shadowCoord.xy + offset).r;
            shadow += shadowCoord.z - bias <= pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main() {
    // base texture
    vec2 uv = fragTexCoord * pushConstants.tiling + pushConstants.offset;
    vec3 base = texture(texSampler, uv).rgb * fragColor;

    // normal & lumière
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-light.dir);

    // diffuse
    float diff = max(dot(N, L), 0.0);

    // shadow factor
    float shadow = ShadowCalculation(fragPosLight, N, L);

    // éclairage final
    vec3 diffuse = base * light.color * (light.intensity * diff) * shadow;
    vec3 ambient = base * light.color * light.ambient;

    outColor = vec4(ambient + diffuse, 1.0);
}
