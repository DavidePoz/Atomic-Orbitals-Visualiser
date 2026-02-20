#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aPhase;
layout (location = 2) in float aDensity;

uniform mat4 view;
uniform mat4 projection;
uniform float uTime;

out float Phase;
out float Density;

void main() {
   gl_Position = projection * view * vec4(aPos, 1.0);
   Phase  = aPhase;
   Density = aDensity;

   gl_PointSize = 2.0;
}
