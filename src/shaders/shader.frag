#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;

layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(set = 0, binding = 2) uniform LightUBO {
    vec3 dir;       float intensity;  // dir = direction *depuis* la lumière (ex: (−1,−1,−1))
    vec3 color;     float ambient;    // ambient = facteur [0..1]
} light;

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
    outColor = vec4(ambient + diffuse, 1.0);
}
