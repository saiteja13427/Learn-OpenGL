#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
out vec4 ourPos;
void main ()
{
 gl_Position = vec4(aPos.x + 0.5, aPos.y + 0.5, aPos.z, 1.0);
 ourColor = aColor;
 ourPos = gl_Position;
};