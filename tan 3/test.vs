//
//  test.vs
//  op
//
//  Created by BoBo W on 2025/5/25.
//

#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;
out vec2 TexCoords;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = vec4(aPos,1.0f);
    TexCoords = aTexCoord;
}
