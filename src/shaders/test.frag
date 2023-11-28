#version 330 core
out vec4 FragColor;

struct Material {
	vec3 color;
	float shininess;
}; 

struct Light {
	//vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragmentPosition;  
in vec3 normal;  

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.color;

	// diffuse 
	vec3 norm = normalize(normal);
	// vec3 lightDir = normalize(light.position - FragPos);
	vec3 lightDir = normalize(-light.direction);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.color;  

	// specular
	vec3 viewDir = normalize(viewPos - fragmentPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * material.color;  

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
} 
