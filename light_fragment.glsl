#version 330 core

in vec3 FragPos;   // Fragment position in world space
in vec3 Normal;    // Normal vector in world space

out vec4 FragColor; // Final fragment color

// Light properties
uniform vec3 lightPos;    // Position of the light source
uniform vec3 lightColor;  // Color of the light

void main()
{
    // Calculate ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Calculate diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Calculate specular light (Phong reflection model)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos); // View direction is from fragment to camera (inverse of camera direction)
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Final color is ambient + diffuse + specular
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
