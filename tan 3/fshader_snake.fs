#version 330 core
in vec3 Normal;
in vec3 FragPos;
//in vec3 ourColor;
//in float a;
in vec3 TexCoords;
in vec4 FragPosLightSpaceD;
in vec4 FragPosLightSpaceS;
out vec4 FragColor;

flat in int Mdiffuse;
//flat in int Mspecular;
in float Mshininess;

//uniform samplerCube u_textures[16];

float mshininess;

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    sampler2D shadowMap;
};

//struct PointLight {
//    vec3 position;
//    
//    float constant;
//    float linear;
//    float quadratic;
//    
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    sampler2D shadowMap;
};

#define NR_POINT_LIGHTS 0

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform vec3 viewPos;
uniform DirLight dirLight;
//uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
vec3 color1,color2;

float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 检查当前片段是否在阴影中
    float bias = 0.0;
//    float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005);;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}
void main()
{
//     properties
    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
//    int i=0;
//    int j=0;
//    switch (Mdiffuse) {
//        case 0: i=0; break;
//        case 1: i=1; break;
//        case 2: i=2; break;
//        case 3: i=3; break;
//        case 4: i=4; break;
//        case 5: i=5; break;
//        case 6: i=6; break;
//        case 7: i=7; break;
//        case 8: i=8; break;
//        case 9: i=9; break;
//        case 10: i=10; break;
//        case 11: i=11; break;
//        case 12: i=12; break;
//        case 13: i=13; break;
//        case 14: i=14; break;
//        case 15: i=15; break;
//        default: i=0; // 错误提示色
//    }
//    switch (Mspecular) {
//        case 0: j=0; break;
//        case 1: j=1; break;
//        case 2: j=2; break;
//        case 3: j=3; break;
//        case 4: j=4; break;
//        case 5: j=5; break;
//        case 6: j=6; break;
//        case 7: j=7; break;
//        case 8: j=8; break;
//        case 9: j=9; break;
//        case 10: j=10; break;
//        case 11: j=11; break;
//        case 12: j=12; break;
//        case 13: j=13; break;
//        case 14: j=14; break;
//        case 15: j=15; break;
//        default: j=0; // 错误提示色
//    }
    switch (Mdiffuse) {
        case 0: color1=vec3(1.0,0.48,0.0); break;
        case 1: color1=vec3(0.21,0.27,0.7); break;
        case 2: color1=vec3(0.1,0.27,0.21); break;
        case 3: color1=vec3(0.63,0.78,0.49); break;
        case 4: color1=vec3(0.35,0.37,0.54); break;
        case 5: color1=vec3(0.87,0.56,0.51); break;
        case 6: color1=vec3(0.54,0.35,0.37); break;
        case -1: color1=vec3(0.11,0.68,0.91); break;
        case -2: color1=vec3(0.24,0.72,0.89); break;
        case -3: color1=vec3(0.51,0.81,0.87); break;
        case -4: color1=vec3(0.64,0.85,0.85); break;
        case -5: color1=vec3(0.83,0.90,0.78); break;
        default: color1=vec3(1.0,0.0,0.0); // 错误提示色
        }
//    color1=ourColor;
    color2=vec3(0.0f,0.0f,0.0f);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
    if(spotLight.ambient.x<0)FragColor=vec4(color1,1.0);
//    FragColor = vec4(viewPos,1.0);
//    FragColor = vec4(1-float(u_textures[Mdiffuse])/2,1-float(u_textures[Mdiffuse])/2,1-float(u_textures[Mdiffuse])/2, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Mshininess);
    // combine results
    float shadow = ShadowCalculation(FragPosLightSpaceD,light.shadowMap,light.direction);
    vec3 ambient = light.ambient * color1;
    vec3 diffuse = (1.0 - shadow) * light.diffuse * diff * color1;
    vec3 specular = light.specular * spec * color2;
    return (ambient + diffuse + specular);
}


// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Mshininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    float shadow = ShadowCalculation(FragPosLightSpaceS,light.shadowMap,light.direction);
    vec3 ambient = light.ambient;
    vec3 diffuse = (1.0 - shadow) * light.diffuse * diff * color1;
    vec3 specular = light.specular * spec * color2;
//    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
//    if(ambient==vec3(0.0,0.0,0.0))return diffuse;
        return mix(mix(ambient,diffuse+specular,0.8),color2,0.1);
    //    return vec3(0.0f,0.0f,0.0f);
//    return vec3(1.0 - shadow,1.0 - shadow,1.0 - shadow);
}
