#version 330 core
out vec4 FragColor;

in vec3 FragPos_world; // Позиция фрагмента в мире

// Uniform'ы для освещения (из прошлого примера)
uniform vec3 objectColor;
uniform vec3 skyColor;
uniform vec3 groundColor;
uniform float intensity;

void main()
{
    // Вычисляем два вектора на поверхности треугольника
    vec3 dFdx_pos = dFdx(FragPos_world);
    vec3 dFdy_pos = dFdy(FragPos_world);
    
    // Векторное произведение дает нам нормаль к поверхности
    // normalize() обязателен!
    vec3 norm = normalize(cross(dFdx_pos, dFdy_pos));

    // --- Дальше идет ваш код освещения, использующий эту новую 'norm' ---
    
    vec3 up = vec3(0.0, 1.0, 0.0);
    float blendFactor = dot(norm, up) * 0.5 + 0.5;
    vec3 hemisphereColor = mix(groundColor, skyColor, blendFactor);
    
    vec3 finalColor = objectColor * hemisphereColor * intensity;
    
    FragColor = vec4(finalColor, 1.0);
}