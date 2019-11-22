#version 330 core  
out vec4 color;  

//in vec3 newColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 LightPos;
uniform vec3 ViewPos;
uniform float p;

uniform vec3 lightColor;

in vec2 Texcoords;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()  
{  
//	//written in class
//	 color = vec4(newColor.x,newColor.y,newColor.z,1.0f);
//	 
//	 //ambient
//	 float Ia = 0.8f;
//	 vec3 ambient = 0.4f * Ia * color.rgb*lightColor;
//	 //diffuse
//	 vec3 lightDir = normalize(LightPos - FragPos);
//	 vec3 norm = normalize(Normal);
//	 float diff = 0.6f * max(dot(norm,lightDir),0.0f);
//	 vec3 diffuse = diff * color.rgb*lightColor;
//	 //specular
//	 vec3 viewDir = normalize(ViewPos - FragPos);
//	 vec3 halfAngle = normalize(viewDir + lightDir);
//	 float spec = 3.0f * pow(max(dot(norm, halfAngle),0.0f),p);
//	 vec3 specular = spec * color.rgb*lightColor;
//
//	 color = vec4(ambient + diffuse + specular, 1.0f);
	
	//learn opengl
	    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
	vec4 tex1 = texture(texture1,Texcoords);
	vec4 tex2 = texture(texture2,Texcoords);
	vec4 newColor = mix(tex1,tex2,(lightColor.x+1)/2);
    vec3 result = (ambient + diffuse + specular) * newColor.rgb;
    color = vec4(result, 1.0);
 } 