#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aFrag;

out vec3 ourColor;
out vec4 ourPos;
out vec2 texCord;

uniform mat4 transform;

void main ()
{
 gl_Position = transform  * vec4(aPos, 1.0);
 ourColor = aColor;
 ourPos = gl_Position;
 texCord = aFrag;
};