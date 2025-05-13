#version 330 core

in vec3 normal;
in vec3 fragPos;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main () {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambientStrength = 0.2;
    vec3 ambientColor = ambientStrength * lightColor;

    FragColor = vec4((ambientColor + diffuse) * objectColor, 1.0);
};