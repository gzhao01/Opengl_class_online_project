#version 330 core //version
layout(location = 0) in vec3 position;  
//layout(location = 1) in vec3 color;
//layout(location = 2) in vec3 normal;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoordinate;

out vec2 Texcoords;

//out vec3 newColor;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


//uniform mat4 transform;
void main()  
{  
	gl_Position = projection*view*model*vec4(position,1.0f);  

//	newColor = color;
	Texcoords = vec2(texcoordinate.x, 1-texcoordinate.y);
	
	Normal = mat3(transpose(inverse(model)))*normal;
	FragPos = vec3(model*vec4(position,1.0f));
};