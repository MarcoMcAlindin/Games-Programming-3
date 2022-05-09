#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;

uniform sampler2D texture_diffuse1;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float ambientStrength;
uniform float specularStrength;


void main()
{   
    
    //Ambient light
    vec3 ambient = ambientStrength * lightColor; 
    //normalize Fragment normal
    vec3 normal = normalize(Normal);
    //Calculate light Direction
    vec3 lightDirection = normalize(lightPosition - FragPosition);
    //Callculate diffuse value 
    float d = max(dot(normal, lightDirection),0.0);
    vec3 diffuse = d * lightColor; 
    //View direction
    vec3 viewDirection = normalize(viewPosition - FragPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    //Calculate Specular value
    float s = pow(max(dot(viewDirection, reflectionDirection), 0.0), 128);
    vec3 specular = specularStrength * s * lightColor;
    //lighting result
    vec3 result = ambient + diffuse + specular;
    //Multiply light calculations result with texture
    FragColor =  vec4(result, 1.0) * texture(texture_diffuse1, TexCoords);
}