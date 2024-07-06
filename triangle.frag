#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 ourColor;

void main()
{
    if (useTexture)
    {
        FragColor = texture(texture1, TexCoord);
    }
    else
    {
        FragColor = vec4(ourColor, 1.0); 
    }
}
