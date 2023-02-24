#version 460 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

/** Material properties */
struct Material{

sampler2D diffuse;
sampler2D specular;
float shininess;

};

/** Light properties */
struct Light{

vec3 position;
vec3 ambient;
vec3 diffuse;
vec3 specular;

};

uniform Material material;
uniform Light light;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec2 TexCoords;

void main()
{
	// Ambient light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// Diffuse light
	vec3 norm = normalize(Normal); // Normalize as we only care about the direction
	vec3 lightDirection = normalize(lightPos - FragPos);

	float dif = max(dot(norm, lightDirection), 0.0); // Use max so we don't get negative values
	vec3 diffuse = light.diffuse * dif * vec3(texture(material.diffuse, TexCoords));

	// Specular light
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0);
}