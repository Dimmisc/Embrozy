#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Добавляем входной атрибут цвета

out vec3 ourColor; // Выходная переменная для фрагментного шейдера
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor; // Передаем цвет фрагментному шейдеру
}