#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 ourPos;
in vec2 texCord;

uniform sampler2D inTexture;
uniform sampler2D inTexture2;
void main () {
 FragColor = mix (texture(inTexture, texCord), texture(inTexture2, texCord), 0.2);
};