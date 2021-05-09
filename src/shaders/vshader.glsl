#version 330 core
layout (location = 0) in vec3 myPos;

out vec4 vertexColor;

void main(){
    gl_Position = vec4(myPos, 1.0);
    vert2exColor = vec4(1.0, 0.0, 0.0, 1.0);
}
