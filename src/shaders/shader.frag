#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec4 fragPosLight;

layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform LightUBO {
    vec3 dir;       float intensity;  // dir = direction *depuis* la lumière (ex: (−1,−1,−1))
    vec3 color;     float ambient;    // ambient = facteur [0..1]
} light;

layout(set = 0, binding = 3) uniform sampler2D shadowMap;

layout(push_constant) uniform PushConstants {
    mat4 model;
    vec2 tiling;
    vec2 offset;
} pushConstants;

void main() {
    vec2 uv = fragTexCoord * pushConstants.tiling + pushConstants.offset;

    vec3 base = texture(texSampler, uv).rgb * fragColor;

    vec3 N = normalize(fragNormal);
    vec3 L = normalize(-light.dir); // on éclaire vers l’objet
    float NdotL = max(dot(N, L), 0.0);

    vec3 diffuse = base * light.color * (light.intensity * NdotL);
    vec3 ambient = base * light.ambient;

    vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5;
    float shadow = 0.0;
    if (projCoords.z <= 1.0) {
        float closest = texture(shadowMap, projCoords.xy).r;
        float bias = max(0.05 * (1.0 - dot(N, L)), 0.005);
        shadow = projCoords.z - bias > closest ? 1.0 : 0.0;
    }

    outColor = vec4(ambient + (1.0 - shadow) * diffuse, 1.0);
}
