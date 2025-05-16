#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec3 normal;  
in vec3 fragPos;  
in vec2 texCords;
  
uniform vec3 viewPos; 
uniform Material material;
uniform Light light;

void main()
{
    float distance = length(fragPos - light.position);
    float attenuation = 1.0/(light.constant + (light.linear * distance) + (light.quadratic * distance * distance));
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCords));
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCords));
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCords)); 

    ambient = ambient * attenuation; 
    diffuse = diffuse * attenuation; 
    specular = specular * attenuation; 

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 

