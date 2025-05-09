#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aFrag;

out vec3 ourColor;
out vec4 ourPos;
out vec2 texCord;

void main ()
{
 gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
 ourColor = aColor;
 ourPos = gl_Position;
 texCord = aFrag;
};