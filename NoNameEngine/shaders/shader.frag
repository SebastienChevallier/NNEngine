#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 1) uniform sampler2D texSampler;

void main() {
    // Appliquer la texture
    vec4 texColor = texture(texSampler, fragTexCoord);

    // Mélanger la texture avec la couleur du vertex
    outColor = texColor * vec4(fragColor, 1.0);
}