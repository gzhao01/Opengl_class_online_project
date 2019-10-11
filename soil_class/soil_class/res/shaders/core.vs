#version 330 core //version
layout(location = 0) in vec3 position;  
layout(location = 1) in vec2 texcoordinate;
out vec2 Texcoords;

void main()  
{  
 gl_Position = vec4(position.x,position.y,position.z, 1.0f);  
 Texcoords = vec2(texcoordinate.x, 1-texcoordinate.y);
}