#version 460 core

/** Material properties */
struct Material{

float shininess;

};

/** Directional light properties */
struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

/** Pointlight properties */
struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

/** Spotlight properties */
struct SpotLight
{
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
};

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights;
uniform SpotLight spotLight;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection);

//FragColor = texture(texture_diffuse1, TexCoords);
void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDirection = normalize(viewPos - FragPos);

	vec3 result = vec3(0.0);
	result += CalculateDirectionalLight(dirLight, normal, viewDirection);

	result += CalculatePointLight(pointLights, normal, FragPos, viewDirection);

	result += CalculateSpotLight(spotLight, normal, FragPos, viewDirection);

    FragColor = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);

	// Diffuse
	float dif = max(dot(normal, lightDirection), 0.0); // Use max so we don't get negative values
	
	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	// Calculations
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * dif * vec3(texture(texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - FragPos);

	// Diffuse
	float dif = max(dot(normal, lightDirection), 0.0); // Use max so we don't get negative values

	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	// Attenuation
	float dis = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));

	// Calculations
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * dif * vec3(texture(texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 FragPos, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - FragPos);

	// Diffuse
	float dif = max(dot(normal, lightDirection), 0.0); // Use max so we don't get negative values

	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	// Attenuation
	float dis = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));

	// Calculate Intensity
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Calculations
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * dif * vec3(texture(texture_diffuse1, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}