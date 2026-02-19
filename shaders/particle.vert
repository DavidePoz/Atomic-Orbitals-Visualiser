#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aVal;

uniform mat4 view;
uniform mat4 projection;

out float particleValue;

void main() {

   gl_Position = projection * view * vec4(aPos, 1.0);
   
   particleValue = aVal;
   
   gl_PointSize = 2.0;

}
