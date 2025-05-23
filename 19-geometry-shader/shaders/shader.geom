#version 330 core

layout (points) in;
layout (points, max_vertices=2) out;

in VS_OUT {
    vec3 pointColor;
} gs_in[];

out vec3 fColor;

void main(){
    fColor = gs_in[0].pointColor;
    gl_Position = gl_in[0].gl_Position + vec4(-0.2, -0.2, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.2, -0.2, 0.0, 0.0);
    EmitVertex();

   

    EndPrimitive();
}