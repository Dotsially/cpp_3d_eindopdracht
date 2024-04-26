#version 460 core

layout (location = 0) in vec2 position;

const vec2 uv_coords[4] = vec2[4](
    vec2(0.0, 0.0), vec2(0.0, 1.0),
    vec2(1.78, 0.0), vec2(1.78, 1.0)
);

layout (location = 0) out vec2 uvCoord;

void main(){
    uvCoord = uv_coords[gl_VertexID % 4];
    gl_Position = vec4(position, 1.0, 1.0);
}