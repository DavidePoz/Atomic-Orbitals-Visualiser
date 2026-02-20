#version 330 core

in float Phase; 
in float Density;

out vec4 FragColor;

uniform int uViewMode;  // 0 = Phase view, 1 = Probability view

void main() {

   vec3 finalColor;

   if (uViewMode == 0) {
      float wave = sin(Phase);
      vec3 posPhaseColor = vec3(0.0, 0.8, 1.0);
      vec3 negPhaseColor = vec3(1.0, 0.2, 0.5);

      vec3 baseColor = (wave > 0.0) ? posPhaseColor : negPhaseColor;
      finalColor = baseColor * abs(wave);
   } else {
      vec3 lowProbColor = vec3(0.0, 0.1, 0.4);
      vec3 highProbColor = vec3(1.0, 0.8, 0.0);

      float heat = sqrt(Density);
      finalColor = mix(lowProbColor, highProbColor, heat);
   }

   FragColor = vec4(finalColor, 0.05);
}
