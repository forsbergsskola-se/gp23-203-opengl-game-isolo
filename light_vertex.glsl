#version 330 core

layout(location = 0) in vec3 aPos;     // Vertex position attribute
layout(location = 1) in vec3 aNormal;  // Vertex normal attribute

out vec3 FragPos;   // Fragment position in world space
out vec3 Normal;    // Normal vector in world space

uniform mat4 model; // Model matrix
uniform mat4 view;  // View matrix
uniform mat4 projection; // Projection matrix

void main()
{
    // Transform vertex position to world space
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;
    
    // Transform normal to world space
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Output final vertex position in clip space
    gl_Position = projection * view * worldPos;
}
