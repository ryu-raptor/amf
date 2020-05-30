#version 140

in vec3 vertices;
in vec2 UVs;

out vec2 UV;

uniform sampler2D textureSampler;
uniform mat4 MVP;
uniform float alpha;

void main() {
  gl_Position = MVP * vec4(vertices, 1);
  UV = UVs;
}

