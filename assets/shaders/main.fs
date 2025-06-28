#version 330 core

out vec4 FragColor;

in vec3 ourColor; // Входная переменная из вершинного шейдера (интерполированная)

void main() {
    FragColor = vec4(ourColor, 1.0f);
}