#version 330 core

in vec3 position;
in vec3 normal;

out vec4 FragColor;

uniform vec3 cameraPos;
uniform samplerCube skyBox;

void main()
{    
    // vec3 I = normalize(position - cameraPos);
    // vec3 R = reflect(I, normalize(normal));
    // FragColor = vec4(texture(skyBox, R).rgb, 1.0);
    FragColor = vec4(gl_FragCoord.x/800, gl_FragCoord.y/600, gl_FragCoord.z , 1.0);
}