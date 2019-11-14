#version 330 core //version
layout(location = 0) in vec3 position;  
layout(location = 1) in vec3 color;
out vec3 newColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float moveRight;
uniform float jump;
uniform float moveLeft;

//uniform mat4 transform;
void main()  
{  
// gl_Position = projection*view*model*vec4(position,1.0f);  
 gl_Position = projection*view*vec4(position.x+moveRight,position.y+jump,position.z, 1.0f);
 newColor = color;
};