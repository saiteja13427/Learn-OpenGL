#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 normal;  
in vec3 fragPos;  
in vec2 texCords;
  
uniform vec3 viewPos; 
uniform Material material;

#define NUM_POINT_LIGHTS 3
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform DirLight dirLight;
uniform SpotLight spotLight;

vec3 calcDirectionLight (DirLight light, vec3 norm, vec3 viewDir) {
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCords));
  	
    // diffuse 
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCords));
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCords)); 

    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 calcPointLight (PointLight light, vec3 norm, vec3 viewDir) {
    float distance = length(fragPos - light.position);
    float attenuation = 1.0/(light.constant + (light.linear * distance) + (light.quadratic * distance * distance));
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCords));
  	
    // diffuse 
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCords));
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCords)); 

    ambient = ambient * attenuation; 
    diffuse = diffuse * attenuation; 
    specular = specular * attenuation; 

    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 calcSpotLight (SpotLight light, vec3 norm, vec3 viewDir){
     // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCords));
  	
    // diffuse 
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff)/epsilon, 0.0, 1.0);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCords));
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCords)); 

    vec3 result = ambient + (diffuse + specular) * intensity;
    return result;
}

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = calcDirectionLight(dirLight, norm, viewDir);

    for(int i=0; i<NUM_POINT_LIGHTS; i++)
        result += calcPointLight(pointLights[i], norm, viewDir);
    
    result += calcSpotLight(spotLight, norm, viewDir);

    FragColor = vec4(result, 1.0f);
} 

