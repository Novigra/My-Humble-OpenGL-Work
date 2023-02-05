#version 460 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main()
{
	// Ambient light
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse light
	vec3 norm = normalize(Normal); // Normalize as we only care about the direction
	vec3 lightDirection = normalize(lightPos - FragPos);

	float dif = max(dot(norm, lightDirection), 0.0); // Use max so we don't get negative values
	vec3 diffuse = dif * lightColor;

	// Specular light
	float specularStrength = 0.5;

	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result,1.0);
}