#version 330 core

in float particleValue;

out vec4 FragColor;

void main () {
   
   vec3 baseColor = vec3(0.2, 0.7, 1.0);

   float intensity = clamp(particleValue, 0.0, 1.0);

   FragColor = vec4(baseColor * intensity, 1.0);

}
