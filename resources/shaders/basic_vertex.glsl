#version 460 core

layout (location = 0) in uint packedPosition;

layout (location = 0) uniform mat4 projectionView;
layout (location = 1) uniform vec2 worldPosition[64];

const vec2 uv_coords[4] = vec2[4](
    vec2(0.0, 0.0), vec2(0.0, 1.0),
    vec2(1.0, 1.0), vec2(1.0, 0.0)
);

layout (location = 0) out vec2 uvCoord;

void main(){
    vec3 vertexPosition = 
        vec3((packedPosition & 63), 
            ((packedPosition >> 6) & 63), 
            ((packedPosition >> 12) & 63));

    uvCoord = uv_coords[gl_VertexID % 4];
    gl_Position = projectionView * vec4(vertexPosition + vec3(worldPosition[gl_DrawID].x, 0, worldPosition[gl_DrawID].y), 1.0);
}