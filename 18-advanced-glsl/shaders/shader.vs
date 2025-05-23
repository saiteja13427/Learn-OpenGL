#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    position = aPos;
    normal = aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = 0.00001;
}

