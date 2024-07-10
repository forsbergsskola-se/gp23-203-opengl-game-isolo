#version 330 core

in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;

uniform vec3 ourColor;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result;
    if (useTexture)
    {
        vec3 texColor = texture(texture1, TexCoord).rgb;
        result = ambient + (texColor * ourColor);
    }
    else
    {
        result = ambient * ourColor;
    }

    FragColor = vec4(result, 1.0);
}
