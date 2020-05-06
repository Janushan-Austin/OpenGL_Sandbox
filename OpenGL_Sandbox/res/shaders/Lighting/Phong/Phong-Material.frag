#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 fNormal;
in vec3 fPos;

uniform vec3 lightPos = vec3(0.0);
uniform vec3 lightColor = vec3(1.0);
uniform float ambientStrength = 0.1;

uniform Material material;

uniform vec3 objectColor = vec3(1.0);

uniform vec3 viewPos  = vec3(0.0);

uniform float specularStrength = 0.5;

out vec4 FragColor;

void main(){
	//calculate ambient lighting
	vec3 ambientLight = lightColor * material.ambient;

	//calculate diffuse lighting
	vec3 normal = normalize(fNormal);
	vec3 lightDir = normalize(lightPos - fPos);

	float lightToNormalTheta = max(dot(lightDir, normal), 0.0);

	vec3 diffuseLight = (material.diffuse * lightToNormalTheta) * lightColor;

	//calculate specular lighting
	vec3 viewDir = normalize(viewPos - fPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float specPow = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specularLight = specPow * material.specular * lightColor;

	vec3 result = ambientLight + diffuseLight + specularLight;

	FragColor = vec4(result, 1.0);
}