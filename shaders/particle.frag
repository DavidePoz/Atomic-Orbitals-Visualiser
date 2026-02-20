#version 330 core

in float particleValue; // The phase
out vec4 FragColor;

void main() {
    // 1. Calculate the wave (-1.0 to 1.0)
    float wave = sin(particleValue);
    
    // 2. Define our two phase colors
    vec3 posPhaseColor = vec3(0.0, 0.8, 1.0); // Electric Cyan
    vec3 negPhaseColor = vec3(1.0, 0.2, 0.5); // Hot Pink
    
    // 3. Pick the color based on whether the wave is positive or negative
    vec3 baseColor = (wave > 0.0) ? posPhaseColor : negPhaseColor;
    
    // 4. Multiply the color by the absolute value of the wave!
    // At the peaks (|1.0|) it will be bright. At the boundaries (0.0) it will fade to dark.
    vec3 finalColor = baseColor * abs(wave);
    
    // 5. Output with a low alpha for the soft probability cloud
    FragColor = vec4(finalColor, 0.05);
}
