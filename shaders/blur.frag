uniform sampler2D texture;
uniform float offset;

void main()
{
	vec2 offx = vec2(offset, 0.0);
	vec2 offy = vec2(0.0, offset);


	gl_FragColor =  gl_Color;
}
