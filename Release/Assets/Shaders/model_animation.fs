#version 330 core
out vec4 FragColor;

//Struct conatining fog information
struct Fog
{
    float MaxDist;
    float MinDist;
    vec3 Color;
    float density;
    float fogHeight;
};

//Struct Containing Material information
struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
};

//Struct containing Light information
struct Light
{
    vec3 position;

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//Variables taken in from vertex shader
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;

uniform vec3 viewPosition;

//Uniform variables for material, light and fog 
uniform Material material;
uniform Light light;
uniform Fog fog;

//Main function
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
    float s = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
    vec3 specular = light.specular * s * vec3(texture(material.texture_specular1, TexCoords));

    //lighting result
    vec3 result = ambient + diffuse + specular;

    //Calculate Fog
    vec3 rayDir = FragPosition - viewPosition;
    float dist = length( rayDir );
    float c = 0.33;
    float b = 0.33;
    

    float distInFog = dist * ((fog.fogHeight - FragPosition.z) / (FragPosition.z - viewPosition.z));
    float fogFactor = (log(distInFog * c) - 1) * b;
    fogFactor = (fog.MaxDist - dist) / (fog.MaxDist - fog.MinDist);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    result = mix(fog.Color, result, fogFactor);

    //Multiply light calculations result with texture
    FragColor =  vec4(result, 1.0);
}

