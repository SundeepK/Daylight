uniform vec2 lightpos;
uniform vec3 lightColor;
uniform float screenHeight;
uniform float intensity;


uniform sampler2D texture;

void main()
{
	vec2 pixel=gl_FragCoord.xy;
	pixel.y=screenHeight-pixel.y;
	vec2 diff=lightpos-pixel;
	float distance=length(diff);
    vec4 color=vec4(lightColor.x,lightColor.y, lightColor.z, (1/distance)*intensity);
	gl_FragColor = color;
}
