#version 330 core

in vec3 fragment_color;
out vec3 color;

void main(){
	// color = vec3(1, 1, 1) - fragment_color;
	color = fragment_color;
}
