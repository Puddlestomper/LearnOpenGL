#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColour;

uniform vec3 objectColour;

uniform vec3 lightColour;
uniform vec3 lightPos;

uniform vec3 viewPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColour;

	vec3 result = (ambient + diffuse + specular) * objectColour;

	FragColour = vec4(result, 1.0);
}