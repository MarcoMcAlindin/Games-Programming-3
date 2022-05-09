#version 330

struct Material {
    sampler2D diffuse;
    //sampler2D specular;
    float shininess;
}; 

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 FragPosition;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPosition;
uniform DirectionalLight directionalLight;
uniform Material material;

//sampler2D texture_diffuse;
//sampler2D texture_specular;



vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

void main()
{
	
	vec3 normal = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragPosition);

	vec3 result = CalculateDirectionalLight(directionalLight, normal, viewDirection);
	FragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);

	float diffuseShading = max(dot(normal, lightDirection),0.0);

	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectionDirection),0.0),32.0);

	vec3 ambient = light.ambient * vec3( texture( material.diffuse, TexCoords ) );
    vec3 diffuse = light.diffuse * diffuseShading * vec3( texture( material.diffuse, TexCoords ) );
    vec3 specular = light.specular * specular * vec3( 1, TexCoords );
    
    return ( ambient + diffuse + specular );
}