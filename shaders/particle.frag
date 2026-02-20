#version 330 core

in float particleValue;

out vec4 FragColor;

void main () {
   
   vec3 baseColor = vec3(0.2, 0.7, 1.0);

   float wave = sin(particleValue);
   float intensity = 0.6 + (0.4 * wave);

   FragColor = vec4(baseColor * intensity, 1.0);

}
