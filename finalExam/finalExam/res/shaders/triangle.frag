#version 330 core  
out vec4 color;  

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 LightPos;
uniform vec3 ViewPos;

uniform vec3 lightColor;

//texture of block
uniform sampler2D texture1;
uniform sampler2D texture2;

struct Material{
	float shiniess;
};

uniform Material material;

uniform float p;

void main()  
{  
	vec4 tex = mix(texture(texture1, TexCoords),texture(texture2, TexCoords),(lightColor.x+1)/2);
	 //ambient
	 float ambientStrength = 0.5f;
	 vec3 ambient = ambientStrength * tex.rgb;
	 //diffuse
	 vec3 lightDir = normalize(LightPos - FragPos);
	 vec3 norm = normalize(Normal);
	 float diff = 0.6f * max(dot(norm,lightDir),0.0f);
	 vec3 diffuse = diff * tex.rgb;

//	 //specular
//	 vec3 viewDir = normalize(ViewPos - FragPos);
//	 vec3 halfAngle = normalize(viewDir + lightDir);
//	 float spec = 3.0f * pow(max(dot(norm, halfAngle),0.0f),material.shiniess);
//	 vec3 specular = spec * texture(texture_specular, TexCoords).rgb;
	   
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * tex.rgb;


	 vec3 result = vec3(ambient + diffuse + specular)*lightColor; 
	 color = vec4(result.x,result.y,result.z, 1.0f);
 } 