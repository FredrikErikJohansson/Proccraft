#version 330										

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;			

out vec4 vColor;
out vec3 Normal;								

uniform mat4 model;							
uniform mat4 projection;	
uniform mat4 view;			

void main()									
{												
	gl_Position = projection * view * model * vec4(pos, 1.0);		
	//vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	vColor = vec4(0.4f, 1.0f, 0.2f, 1.0f);
	
	Normal = mat3(transpose(inverse(model))) * norm;
}											
