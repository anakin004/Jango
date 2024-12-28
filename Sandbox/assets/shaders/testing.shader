#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;   


out vec3 v_Position; 

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;
uniform vec4 u_Color;

void main() {
    v_Position = a_Position; 
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0); 
}

#shader fragment
#version 330 core

in vec4 v_Color;
out vec4 FragColor;

uniform vec4 u_Color;

void main() {
    FragColor = u_Color;
}
