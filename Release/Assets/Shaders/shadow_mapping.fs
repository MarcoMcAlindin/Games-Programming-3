#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
};

struct Light
{
    vec3 position;

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;
in vec4 ShadowMapCoords;

uniform sampler2D shadowMap;
uniform vec3 viewPosition;

uniform Material material;
uniform Light light;

float CalculateShadows(vec4 shadowMapCoords)
{
    //Perspective divide
    vec3 projectionCoords = shadowMapCoords.xyz / shadowMapCoords.w;

    //Transform to be in [0,1] Range
    projectionCoords = projectionCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projectionCoords.xy).r;

    float currentDepth = projectionCoords.z;

    //Normalize normal
    vec3 normal = normalize(Normal);

    //Calculate light Direction phong Light
    vec3 lightDirection = normalize(light.position - FragPosition);

    float b = max(0.05 * (1.0 - dot(normal, lightDirection)),0.005);

    //Check if current fragment is in shadow using PCF technique for anti-ailasing

    float shadow = 0.0;
    vec2 texelSize = 1.0 /textureSize(shadowMap, 0);
    for(int x = -1; x <=1; ++x)
    {
        for(int y = -1; y<= 1; ++y)
        {
            float pcf_Depth = texture(shadowMap, projectionCoords.xy + vec2(x,y) * texelSize).r;
            shadow += currentDepth - b > pcf_Depth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    if(projectionCoords.z > 1.0) shadow = 0.0;

    return shadow;
}

void main()
{   
    //normalize Fragment normal
    vec3 normal = normalize(Normal);

    //View direction
    vec3 viewDirection = normalize(viewPosition - FragPosition);
   
    //Calculate light Direction phong Light
    //vec3 lightDirection = normalize(light.position - FragPosition);

    //Calculate Directional Light light direction
    vec3 lightDirection = normalize(-light.direction);

    //Reflection direction
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    //Ambient light
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords)); 

    //Calculate diffuse value 
    float d = max(dot(normal, lightDirection),0.0);
    vec3 diffuse = light.diffuse * d * vec3(texture(material.texture_diffuse1, TexCoords)); 
   
    //Calculate Specular value
    vec3 halfwayDirection = normalize(lightDirection + viewDirection);
    float s = pow(max(dot(normal, halfwayDirection), 0.0), material.shininess);
    vec3 specular = light.specular * s * vec3(texture(material.texture_specular1, TexCoords));
    //vec3 specular = s * vec3(texture(material.texture_diffuse1, TexCoords));

    //Calculate shadow
    float shadow = CalculateShadows(ShadowMapCoords);
    //lighting result
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));

    //Multiply light calculations result with texture
    FragColor =  vec4(result, 1.0);
}

