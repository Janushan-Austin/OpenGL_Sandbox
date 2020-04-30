#version 330 core

layout(location = 0) in vec3 vPos;

uniform mat4 model, view, projection;

void main(){
	gl_Position = projection * view * model * vec4(vPos, 1.0);
}