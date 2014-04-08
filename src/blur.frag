uniform sampler2D texture;
uniform float offset;

void main()
{

	gl_FragColor =  gl_Color * (pixel / 13.0);
}
