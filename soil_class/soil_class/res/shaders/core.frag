#version 330 core  
out vec4 color;  
in vec2 Texcoords;
uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float change;
void main()  
{  
		color = texture(texture1,Texcoords);
//		color = mix(texture(texture1,Texcoords),texture(texture2,Texcoords),change);
 } 