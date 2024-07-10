#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 skyView;
uniform mat4 skyProjection;

void main()
{
    TexCoords = aPos;
    mat4 viewNoTranslate = mat4(mat3(skyView)); 
    gl_Position = skyProjection * viewNoTranslate * vec4(aPos, 1.0);
}
