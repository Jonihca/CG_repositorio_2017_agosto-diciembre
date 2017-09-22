#version 330

in vec3 InterpolatedColor;
out vec4 FragColor;

void main()
{
    vec2 pixelPositionInWindow= gl_FragCoord.xy;
    vec2 centro = vec2 (200.0f,200.0f);
    vec2 distancia = pixelPositionInWindow-centro;

    FragColor = vec4(InterpolatedColor, 1.0f);

    if (sqrt((distancia.x)*(distancia.x) + (distancia.y)*(distancia.y))<100.0f){
    
   	 discard;
    }
}
