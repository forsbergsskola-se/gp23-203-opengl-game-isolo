#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;
uniform vec3 ourColor;

uniform vec3 lightColor;
uniform vec3 lightDirection; // Directional light direction
uniform vec3 lightPos; // Positional light position
uniform vec3 viewPos;

uniform float specularStrength;
uniform float shininess;

uniform float emissiveStrength;


void main()
{
    // Ambient lighting
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir;
    if (length(lightPos) < 0.0) 
    {
        lightDir = normalize(lightDirection); // Directional light
    } else 
    {
        lightDir = normalize(lightPos - FragPos); // Positional light
    }
    float diff = max(dot(norm, lightDir), 0.0);  // Compute diffuse intensity
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDir, norm); // Calculate reflection direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Compute specular intensity
    vec3 specular = specularStrength * spec * lightColor;

    //Emissive Lighting
    vec3 emissive = emissiveStrength * ourColor;

    // Final color calculation
    vec3 result;
    if (useTexture)
    {
        vec3 texColor = texture(texture1, TexCoord).rgb;
        result = (ambient + diffuse + specular) * texColor * ourColor + emissive;
    }
    else
    {
        result = (ambient + diffuse + specular) * ourColor + emissive;
    }

    FragColor = vec4(result, 1.0);
}
