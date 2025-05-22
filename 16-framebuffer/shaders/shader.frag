#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

//Linearize the non linear depth buffer value by reverting projection matrix application on depth buffer
float near = 0.01;
float far = 100;

float linearizeDepthBuffer(float depth){
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far)/ (far + near - z * (far - near));
}

void main()
{    
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}