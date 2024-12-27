#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;   

out vec4 v_Color;  
out vec3 v_Position; 

uniform mat4 u_ViewProjection;

void main() {
    v_Color = a_Color;
    v_Position = a_Position; 
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0); 
}

#shader fragment
#version 330 core

in vec4 v_Color;
out vec4 FragColor;

void main() {
    FragColor = v_Color;
}
