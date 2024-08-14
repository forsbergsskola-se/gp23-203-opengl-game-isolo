#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform bool useTexture;
uniform mat4 objectMVP;

void main()
{
    gl_Position = objectMVP * vec4(aPos, 1.0);
    FragPos = vec3(objectMVP * vec4(aPos, 1.0));  // Corrected to use the transformed vertex position
    Normal = mat3(transpose(inverse(objectMVP))) * aNormal;  // Corrected to transform the normal correctly

    if (useTexture)
    {
        TexCoord = aTexCoord;  // Always assign texture coordinates if used

    }
}
