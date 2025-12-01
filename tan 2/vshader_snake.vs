#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec3 aNormal;
//layout (location = 3) in float correct;
layout (location = 3) in int diffuse;
//layout (location = 4) in int specular;
layout (location = 5) in float shininess;
layout (location = 6) in mat4 model;
out vec3 ourColor;
out float a;
out vec3 FragPos;
out vec3 Normal;
out vec3 TexCoords;
out vec4 FragPosLightSpaceD;
out vec4 FragPosLightSpaceS;
flat out int Mdiffuse;
//flat out int Mspecular;
out float Mshininess;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 lightSpaceMatrixD;
uniform mat4 lightSpaceMatrixS;
void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0f);
    ourColor = colour.xyz;
    a = colour.w;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(model) * aNormal;
    TexCoords = -aPos;
    Mdiffuse=diffuse;
//    Mspecular=specular;
    Mshininess=shininess;
    FragPosLightSpaceD = lightSpaceMatrixD * vec4(FragPos, 1.0);
    FragPosLightSpaceS = lightSpaceMatrixS * vec4(FragPos, 1.0);
}
