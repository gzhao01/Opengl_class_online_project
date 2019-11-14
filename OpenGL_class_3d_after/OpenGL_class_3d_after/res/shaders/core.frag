#version 330 core  
out vec4 color;  

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec3 LightPos;
uniform vec3 ViewPos;

struct Material{
	float shiniess;
};

uniform Material material;

uniform float p;

void main()  
{  
	 //ambient
	 vec3 ambient = 0.8f * texture(texture_diffuse1, TexCoords).rgb;
	 //diffuse
	 vec3 lightDir = normalize(LightPos - FragPos);
	 vec3 norm = normalize(Normal);
	 float diff = 0.6f * max(dot(norm,lightDir),0.0f);
	 vec3 diffuse = diff * texture(texture_diffuse1, TexCoords).rgb;
	 //specular
	 vec3 viewDir = normalize(ViewPos - FragPos);
	 vec3 halfAngle = normalize(viewDir + lightDir);
	 float spec = 3.0f * pow(max(dot(norm, halfAngle),0.0f),material.shiniess);
	 vec3 specular = spec * texture(texture_specular1, TexCoords).rgb;

	 color = vec4(ambient + diffuse + specular, 1.0f);
 } 