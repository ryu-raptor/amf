#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;
uniform float alpha;
uniform vec3 colorModulator;

void main() {
  vec4 precolor = texture(textureSampler, UV).rgba;
  precolor.a = precolor.a * alpha;
  precolor.r = precolor.r + colorModulator.r;
  precolor.g = precolor.g + colorModulator.g;
  precolor.b = precolor.b + colorModulator.b;
  color = precolor;
}

