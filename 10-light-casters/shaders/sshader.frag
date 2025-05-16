#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutoff; // Defines how big the spotlight is
    float outerCutoff; //Defines the end of spotlight, spotlight starts to fade away between cutoff and outercutoff to give a realistic feel.

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
uniform Light light;

void main()
{
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);


    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCords));
  	
    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCords));
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCords));  

    vec3 result = ambient + (diffuse + specular) * intensity;
    FragColor = vec4(result, 1.0);


} 

