#version 330 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec2 UVs;

out vec2 UV;

uniform sampler2D textureSampler;

void main() {
  gl_Position = vec4(vertices, 1);
  UV = UVs;
}

