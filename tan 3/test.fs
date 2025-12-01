//
//  test.fs
//  op
//
//  Created by BoBo W on 2025/5/25.
//

#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D depthMap;

void main()
{
    float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(depthValue), 1.0);
//    FragColor = vec4(1.0,1.0,0.0,1.0);
}
