#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aPhase;

uniform mat4 view;
uniform mat4 projection;
uniform float uTime;

out float particleValue;

void main() {

   gl_Position = projection * view * vec4(aPos, 1.0);
   
   particleValue = aPhase + (uTime * 2.0);
   
   gl_PointSize = 2.0;

}
