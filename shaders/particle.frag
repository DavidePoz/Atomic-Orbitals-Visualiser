#version 330 core

in float particleValue;

out vec4 FragColor;

void main () {
   
   float wave = sin(particleValue);
    
   float mixVal = (wave + 1.0) * 0.5;

   vec3 posPhaseColor = vec3(0.0, 0.8, 1.0); 
   vec3 negPhaseColor = vec3(1.0, 0.2, 0.5); 

   vec3 finalColor = mix(negPhaseColor, posPhaseColor, mixVal);
    
   FragColor = vec4(finalColor, 1.0);
}
