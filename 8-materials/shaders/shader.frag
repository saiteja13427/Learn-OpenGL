#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 normal;  
in vec3 fragPos;  
  
uniform vec3 viewPos; 
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    // // ambient
    // vec3 ambient = light.ambient * material.ambient;
  	
    // // diffuse 
    // vec3 norm = normalize(normal);
    // vec3 lightDir = normalize(light.position - fragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * (material.diffuse * diff);
    
    // // specular
    // vec3 viewDir = normalize(viewPos - fragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * material.specular * spec;  
        
    // vec3 result = (ambient  + diffuse + specular);
    // FragColor = vec4(result, 1.0);
} 

