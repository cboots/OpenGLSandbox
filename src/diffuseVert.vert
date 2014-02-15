#version 150

//there's no rules about the prefixes but they do help
//keep track of things
uniform mat4 u_modelMatrix;
uniform mat4 u_projMatrix;
uniform vec3 u_lightPos;

in vec3 vs_normal;
in vec3 vs_position;
in vec3 vs_color;

out vec3 fs_normal;
out vec3 fs_color;

void main() { 
    fs_color = vs_color;
    fs_normal = vs_normal;
    gl_Position = vec4(vs_position, 1.0);
}