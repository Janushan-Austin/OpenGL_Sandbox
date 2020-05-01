#version 330 core

layout(location =0) in vec3 vPos;
layout(location =1) in vec3 vCol;
layout(location =2) in vec2 vTexCoord;

out vec2 fTexCoord;
out vec4 fCol;

void main(){
	gl_Position = vec4(vPos, 1.0);
	fCol = vec4(vCol, 1.0);
	fTexCoord = vTexCoord;
}