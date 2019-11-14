#version 330 core  
out vec4 color;  
in vec3 newColor;
void main()  
{  
 color = vec4(newColor.x,newColor.y,newColor.z,1.0f);
} 