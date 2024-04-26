#version 460 core

uniform sampler2D tex;

layout (location = 0) in vec2 uvCoord;
out vec4 fragColor;

void main(){
    vec4 color = texture(tex, uvCoord);
    fragColor = color;
}