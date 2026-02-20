#version 330 core

in float Phase; 
in float Density;

out vec4 FragColor;

uniform int uViewMode;  // 0 = Phase view, 1 = Probability view

void main() {

   vec3 finalColor;

   if (uViewMode == 0) {
      float wave = cos(Phase);
      vec3 posPhaseColor = vec3(0.0, 0.8, 1.0);
      vec3 negPhaseColor = vec3(1.0, 0.2, 0.5);

      vec3 baseColor = (wave >= 0.0) ? posPhaseColor : negPhaseColor;
      finalColor = baseColor * abs(wave);
   } else {
      vec3 col1 = vec3(0.2, 0.0, 0.4);   // Deep Violet
      vec3 col2 = vec3(0.8, 0.0, 0.6);   // Bright Magenta
      vec3 col3 = vec3(1.0, 0.5, 0.0);   // Vibrant Orange
      vec3 col4 = vec3(1.0, 1.0, 0.8);   // Hot Yellow/White
        
      float heat = pow(max(Density, 0.0), 0.2); 
        
      if (heat < 0.33) {
         finalColor = mix(col1, col2, heat * 3.0);
      } 
      else if (heat < 0.66) {
         finalColor = mix(col2, col3, (heat - 0.33) * 3.0);
      } 
      else {
         finalColor = mix(col3, col4, (heat - 0.66) * 3.0);
      }
   }

   FragColor = vec4(finalColor, 0.05);
}
