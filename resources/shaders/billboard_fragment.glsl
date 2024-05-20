#version 460 core

uniform sampler2D tex;

in vec2 uvCoord;

out vec4 fragColor;

void main(){
    vec4 color = texture(tex, uvCoord);
    if(color.a < 0.1){
        discard;
    }

    fragColor = color;
}