#version 330 core
in vec3 Normal;
in vec3 FragPos;
in float a;
in vec2 TexCoords;
in vec4 FragPosLightSpaceD;
in vec4 FragPosLightSpaceS;
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

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
uniform Material material;
uniform vec4 ourColor;

vec3 color;
vec3 color2;
uniform float offset;
uniform float offset2;
float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap, vec3 lightDir, int i)
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
    
    float shadow;
    if(i>0){
//        float bias = max(0.0005 * (1.0-dot(normalize(Normal), normalize(lightDir))), 0.00005);
        shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    }else{
        shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }
        }
        shadow /= 9.0;
    }
    return shadow;
}
vec2 texForS;
vec3 flit;
void main()
{
    // properties
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);
    
    
    flit = vec3(0.1+cos(offset2*50+offset*10)*0.05);
    texForS = vec2((TexCoords.x+5.0)/10+offset2*10,(TexCoords.y+5.0)/10);
    vec2 texForS2 = vec2(((TexCoords.x+5.0)/10+offset2*15),(TexCoords.y+5.0)/10);
    vec3 sh = vec3(1.0,1.0,1.0)-mix(vec3(texture(material.specular, texForS).xyz),vec3(texture(material.specular, texForS2).xyz),abs(offset2-0.5)/2+0.5)*flit*(-sin(acos(mod(offset2,0.2)*10-1)*2+radians(90))+1)/2;
//    color2=mix(vec3(texture(material.diffuse, vec2(TexCoords.x+offset*5.0,TexCoords.y+offset))),sh*flit,0.2);
    color2 = vec3(texture(material.diffuse, vec2(TexCoords.x+offset*5.0,TexCoords.y+offset)))*sh;
//    color2 = vec3(texture(material.diffuse, vec2(TexCoords.x+offset*5.0,TexCoords.y+offset)));
    color=ourColor.xyz;
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
    
    
        FragColor = vec4(result, ourColor.w);
//    FragColor = vec4((-sin(acos(mod(offset2,0.2)*10-1)*2+radians(90))+1)/2,0.0,0.0,1.0);
    if(spotLight.ambient.x<0.0){
        float shadow = ShadowCalculation(FragPosLightSpaceS,spotLight.shadowMap,spotLight.direction,1);
        FragColor = vec4((1.0 - shadow)*color*sh, ourColor.w);
//        FragColor = vec4((1.0 - shadow)*color, ourColor.w);
//        FragColor = vec4(vec3(shadow), ourColor.w);
    }
//    FragColor = vec4(result,ourColor.w);
    
//    FragColor = vec4(FragPosLightSpaceD.xyz/FragPosLightSpaceD.w, a);
//    FragColor = vec4(vec3(gl_FragCoord.z,gl_FragCoord.z*gl_FragCoord.z,gl_FragCoord.z*gl_FragCoord.z),a);
}
// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    float shadow = ShadowCalculation(FragPosLightSpaceD,light.shadowMap,light.direction,0);
    vec3 ambient = light.ambient * color;
    vec3 diffuse = (1.0 - shadow) * light.diffuse * diff * color;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texForS)) *flit;
    return (ambient+diffuse+specular);
//    return vec3(shadow,shadow,shadow);
//    return vec3(0.0f,0.0f,0.0f);
}

// calculates the color when using a point light.
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    float shadow = ShadowCalculation(FragPosLightSpaceS,light.shadowMap,light.direction,0);
    vec3 ambient = light.ambient;
    vec3 diffuse = (1.0 - shadow) * light.diffuse * diff * color;
    vec3 specular = light.specular * spec * color2;
//    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    if(ambient==vec3(0.0,0.0,0.0))return diffuse;
        return mix(mix(ambient,diffuse+specular,0.8),color2,0.1);
    //    return vec3(0.0f,0.0f,0.0f);
//    return vec3(1.0 - shadow,1.0 - shadow,1.0 - shadow);
}
