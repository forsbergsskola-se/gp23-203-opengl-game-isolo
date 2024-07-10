#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;

uniform bool useTexture;
uniform mat4 objectMVP;

void main()
{
    gl_Position = objectMVP * vec4(aPos, 1.0);
    FragPos = vec3(objectMVP * vec4(aPos, 1.0));
    
    if (useTexture)
    {
        TexCoord = aTexCoord;
    }
}
