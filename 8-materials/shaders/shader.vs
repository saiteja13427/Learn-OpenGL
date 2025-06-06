#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main ()
{
 gl_Position = projection * view * model * vec4(aPos, 1.0);
 //Translating fragPos and normal to worldspace using model matrix
 fragPos = vec3(model * vec4(aPos, 1.0));
 normal = mat3(transpose(inverse(model))) * aNormal;
};