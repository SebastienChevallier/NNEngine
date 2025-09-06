#include "Material.h"

NNE::Component::Render::Material::Material()
    : texturePath(""), tiling(1.0f, 1.0f), offset(0.0f, 0.0f),
      vertexShaderPath("vert.spv"), fragmentShaderPath("frag.spv"),
      textureImage(VK_NULL_HANDLE), textureImageMemory(VK_NULL_HANDLE),
      textureImageView(VK_NULL_HANDLE), textureSampler(VK_NULL_HANDLE) {}

NNE::Component::Render::Material::~Material() = default;
