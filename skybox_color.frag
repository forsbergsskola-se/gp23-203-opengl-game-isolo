#version 330 core

in vec3 TexCoords;
out vec4 FragColor;

uniform vec3 skyboxColors[6];

void main() {
    vec3 absCoords = abs(TexCoords);
    vec3 color;

    if (absCoords.x > absCoords.y && absCoords.x > absCoords.z) {
        color = TexCoords.x > 0.0 ? skyboxColors[0] : skyboxColors[1];
    } else if (absCoords.y > absCoords.x && absCoords.y > absCoords.z) {
        color = TexCoords.y > 0.0 ? skyboxColors[2] : skyboxColors[3];
    } else {
        color = TexCoords.z > 0.0 ? skyboxColors[4] : skyboxColors[5];
    }

    FragColor = vec4(color, 1.0);
}
