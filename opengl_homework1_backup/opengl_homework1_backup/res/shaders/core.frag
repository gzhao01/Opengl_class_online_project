#version 330 core  
out vec4 color;  
in vec4 outColor;  
//uniform vec4 uniformColor;
void main()  
{  
	color = vec4(outColor.r,outColor.g,outColor.b,outColor.a);  
	
//	color = uniformColor;
 } 