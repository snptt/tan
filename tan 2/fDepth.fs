#version 330 core
out vec4 FragColor;
float LinearizeDepth(float x, float near, float far){
    return x;
}
void main()
{
//     gl_FragDepth = gl_FragCoord.z;
//    FragColor = vec4(vec3(gl_FragCoord.z),1.0);
//    float near = 0.1;
//    float far = 100.0;
//    float depthCenter = LinearizeDepth(gl_FragCoord.z, near, far);
//    float depthRight = LinearizeDepth(dFdx(gl_FragCoord.z), near, far);
//    float depthUp = LinearizeDepth(dFdy(gl_FragCoord.z), near, far);
//    float edge = abs(depthRight - depthCenter) + abs(depthUp - depthCenter);
//    FragColor = vec4(edge * 10.0, 0.0, 0.0, 1.0); // 红色高亮边缘
}
