#version 330										

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;			

out vec3 Normal;
out vec4 Position;		
out vec3 FragPos;	

uniform mat4 model;							
uniform mat4 projection;	
uniform mat4 view;			

void main()									
{												
	gl_Position = projection * view * model * vec4(pos, 1.0f);		
	Normal = mat3(transpose(inverse(model))) * norm;
	Position = vec4(pos, 1.0);
	FragPos = (model * vec4(pos, 1.0f)).xyz;
}											
