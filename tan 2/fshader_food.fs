#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 ourColor;
in float a;
in vec4 FragPosLightSpaceD;
in vec4 FragPosLightSpaceS;
out vec4 FragColor;

float mshininess=1.0;

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
vec3 color1,color2;
void main()
{
    color1=ourColor;
    color2=vec3(0.0f,0.0f,0.0f);
    // properties
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);
        // == =====================================================
        // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
        // For each phase, a calculate function is defined that calculates the corresponding color
        // per lamp. In the main() function we take all the calculated colors and sum them up for
        // this fragment's final color.
        // == =====================================================
        // phase 1: directional lighting
        vec3 result = CalcDirLight(dirLight, norm, viewDir);
        // phase 2: point lights
//        for(int i = 0; i < NR_POINT_LIGHTS; i++)
//            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
        // phase 3: spot light
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
        
        FragColor = vec4(result,1.0);
}
// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
    // combine results
    float shadow = ShadowCalculation(FragPosLightSpaceD,light.shadowMap,light.direction);
//    float shadow = 0.0f;
    vec3 ambient = light.ambient * ourColor;
    vec3 diffuse = (1.0 - shadow) * light.diffuse * diff * ourColor;
    vec3 specular = light.specular * spec * ourColor;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(test, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(test, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(u_textures[Mspecular], TexCoords));
//    ambient *= attenuation;
//    diffuse *= attenuation;
//    specular *= attenuation;
//    return (ambient + diffuse + specular);
//}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
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
        return mix(mix(ambient,diffuse+specular,0.8),color2,0.1);
    //    return vec3(0.0f,0.0f,0.0f);
//    return vec3(1.0 - shadow,1.0 - shadow,1.0 - shadow);
}
