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
struct DirectionalLight
{
    vec3 position;

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
   
    float constant;
    float linear;
    float quadratic;
	
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
uniform DirectionalLight directionalLight;
uniform Fog fog;
uniform PointLight pointLight;

//Methos for calculating Directional and Point light
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection);
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

//Calculate diffuse shading value
float DiffuseShading(vec3 normal, vec3 lightDirection ) 
{ 
    float d = max(dot(normal, lightDirection),0.0);
    return d; 
}
//Calculate Specular shading value
float SpecularShading( vec3 viewDirection, vec3 reflectionDirection) 
{ 
    float s = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);  
    return s;
}

//Main function
void main()
{   
    //normalize Fragment normal
    vec3 normal = normalize(Normal);

    //View direction
    vec3 viewDirection = normalize(viewPosition - FragPosition); 
   
    vec3 result  = CalculateDirectionalLight(directionalLight, normal, viewDirection); 

    result += CalculatePointLight(pointLight, normal, FragPosition, viewDirection);

    //Calculate Fog
    vec3 rayDir = FragPosition - viewPosition;
    float dist = length( rayDir );
    float c = 0.001;
    float b = 0.02;
    

    float distInFog = dist * ((fog.fogHeight - FragPosition.z) / (FragPosition.z - viewPosition.z));
    float fogFactor = (log(distInFog * c) - 1) * b;
    fogFactor = (fog.MaxDist - dist) / (fog.MaxDist - fog.MinDist);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    result = mix(fog.Color, result, fogFactor);

    //Multiply light calculations result with texture
    FragColor =  vec4(result, 1.0);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDirection)
{
   //Light direction
   vec3 lightDirection = normalize(light.position - fragPos);

   // specular shading
   vec3 reflectionDirection = reflect(-lightDirection, normal);


   // attenuation
   float distance = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
   
   // combine results
   vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
   vec3 diffuse = light.diffuse * DiffuseShading(normal, lightDirection) * vec3(texture(material.texture_diffuse1, TexCoords));
   vec3 specular = light.specular * SpecularShading(viewDirection, reflectionDirection) * vec3(texture(material.texture_specular1, TexCoords));   
   ambient *= attenuation;
   diffuse *= attenuation;
   specular *= attenuation;
   return (ambient + diffuse + specular);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    //Calculate Directional Light light direction
    vec3 lightDirection = normalize(-light.direction);

    //Reflection direction
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    //Calculate Ambient lighting
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));

    //Diffuse lighting
    vec3 diffuse = light.diffuse * DiffuseShading(normal, lightDirection) * vec3(texture(material.texture_diffuse1, TexCoords)); 

    //Specular lighting
    vec3 specular = light.specular * SpecularShading(viewDirection, reflectionDirection) * vec3(texture(material.texture_specular1, TexCoords));

    return ambient + diffuse + specular;
}