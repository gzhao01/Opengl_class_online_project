#version 330 core  
out vec4 color;  
in vec3 outColor;  
void main()  
{  
	color = vec4(outColor.x,outColor.y,outColor.z,1.0f);  
 } 