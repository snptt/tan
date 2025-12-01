#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 ourColor;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float mixx;
void main()
{
FragColor = mix(texture(Texture1,TexCoord),texture(Texture2,TexCoord),mixx);
}
